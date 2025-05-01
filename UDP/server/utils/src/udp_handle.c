#include <iostream>
#include "udp_handle.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <thread>

UDPHandle::UDPHandle() : m_socket(-1), m_isReceiving(false) {
    createSocket();
}

UDPHandle::~UDPHandle() {
    stopReceiving();
    if (m_socket >= 0) {
        close(m_socket);
    }
}

bool UDPHandle::createSocket() {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socket < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool UDPHandle::bind(int port) {
    memset(&m_localAddr, 0, sizeof(m_localAddr));
    m_localAddr.sin_family = AF_INET;
    m_localAddr.sin_addr.s_addr = INADDR_ANY;
    m_localAddr.sin_port = htons(port);

    if (::bind(m_socket, (struct sockaddr*)&m_localAddr, sizeof(m_localAddr)) < 0) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool UDPHandle::bindAny() {
    memset(&m_localAddr, 0, sizeof(m_localAddr));
    m_localAddr.sin_family = AF_INET;
    m_localAddr.sin_addr.s_addr = INADDR_ANY;
    m_localAddr.sin_port = 0;  // Let system choose port

    if (::bind(m_socket, (struct sockaddr*)&m_localAddr, sizeof(m_localAddr)) < 0) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        return false;
    }

    // Get assigned port
    socklen_t len = sizeof(m_localAddr);
    getsockname(m_socket, (struct sockaddr*)&m_localAddr, &len);
    
    return true;
}

void UDPHandle::setDestination(const std::string& ip, int port) {
    memset(&m_destAddr, 0, sizeof(m_destAddr));
    m_destAddr.sin_family = AF_INET;
    m_destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &m_destAddr.sin_addr);
}

bool UDPHandle::send(const std::string& message) {
    ssize_t sent = sendto(m_socket, message.c_str(), message.length(), 0,
                         (struct sockaddr*)&m_destAddr, sizeof(m_destAddr));
    return sent == static_cast<ssize_t>(message.length());
}

bool UDPHandle::sendTo(const std::string& message, const std::string& ip, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    ssize_t sent = sendto(m_socket, message.c_str(), message.length(), 0,
                         (struct sockaddr*)&addr, sizeof(addr));
    return sent == static_cast<ssize_t>(message.length());
}

bool UDPHandle::broadcast(const std::string& message, int port) {
    setBroadcast(true);
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_BROADCAST;

    ssize_t sent = sendto(m_socket, message.c_str(), message.length(), 0,
                         (struct sockaddr*)&addr, sizeof(addr));
    return sent == static_cast<ssize_t>(message.length());
}

void UDPHandle::receiveLoop() {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);

    while (m_isReceiving) {
        ssize_t received = recvfrom(m_socket, buffer, BUFFER_SIZE - 1, 0,
                                  (struct sockaddr*)&senderAddr, &senderLen);
        
        if (received > 0 && m_callback) {
            buffer[received] = '\0';
            m_callback(std::string(buffer), senderAddr);
        }
    }
}

void* UDPHandle::receiveThread(void* arg) {
    UDPHandle* handle = static_cast<UDPHandle*>(arg);
    handle->receiveLoop();
    return nullptr;
}

bool UDPHandle::startReceiving(MessageCallback callback) {
    if (m_isReceiving) return false;
    
    m_callback = callback;
    m_isReceiving = true;
    
    if (pthread_create(&m_receiveThread, nullptr, receiveThread, this) != 0) {
        m_isReceiving = false;
        return false;
    }
    return true;
}

void UDPHandle::stopReceiving() {
    m_isReceiving = false;
    pthread_join(m_receiveThread, nullptr);
}

bool UDPHandle::setReuseAddr(bool enable) {
    int opt = enable ? 1 : 0;
    return setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) >= 0;
}

bool UDPHandle::setBroadcast(bool enable) {
    int opt = enable ? 1 : 0;
    return setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) >= 0;
}

bool UDPHandle::setReceiveBufferSize(int size) {
    return setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) >= 0;
}

bool UDPHandle::setNonBlocking(bool enable) {
    int flags = fcntl(m_socket, F_GETFL, 0);
    if (flags < 0) return false;
    
    flags = enable ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    return fcntl(m_socket, F_SETFL, flags) >= 0;
}

int UDPHandle::getPort() const {
    return ntohs(m_localAddr.sin_port);
}

std::string UDPHandle::getIP() const {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(m_localAddr.sin_addr), ip, INET_ADDRSTRLEN);
    return std::string(ip);
}

bool UDPHandle::isReceiving() const {
    return m_isReceiving;
}