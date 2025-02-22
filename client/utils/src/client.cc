#include "client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

Client::Client(const std::string& host, int port, messageCallback callback) 
    : m_host(host), m_port(port), m_socket(-1), m_running(false), m_messageCallback(callback) {
}

Client::~Client() {
    stop();
}

void Client::start() {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socket < 0) {
        throw std::runtime_error("Failed to create UDP socket");
    }

    memset(&m_serverAddr, 0, sizeof(m_serverAddr));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(m_port);

    if (inet_pton(AF_INET, m_host.c_str(), &m_serverAddr.sin_addr) <= 0) {
        close(m_socket);
        throw std::runtime_error("Invalid address");
    }

    m_running = true;

    if (pthread_create(&m_receiverThread, nullptr, receiverWrapper, this)) {
        close(m_socket);
        throw std::runtime_error("Failed to create receiver thread");
    }
}

void Client::receiverProcedure() {
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t serverAddrLen = sizeof(serverAddr);

    while (m_running) {
        ssize_t bytesRead = recvfrom(m_socket, buffer, sizeof(buffer) - 1, 0,
                                   (struct sockaddr*)&serverAddr, &serverAddrLen);
        
        if (bytesRead < 0) {
            continue;
        }

        buffer[bytesRead] = '\0';
        std::string message(buffer);

        if (m_messageCallback) {
            m_messageCallback(this, message);
        }
    }
}

void* Client::receiverWrapper(void* param) {
    Client* client = static_cast<Client*>(param);
    try {
        client->receiverProcedure();
    } catch (const std::exception& e) {
        std::cerr << "Receiver thread error: " << e.what() << std::endl;
    }
    return nullptr;
}

void Client::sendMessage(const std::string& message) {
    sendto(m_socket, message.c_str(), message.length(), 0,
           (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr));
}

void Client::stop() {
    m_running = false;
    close(m_socket);
}

bool Client::isRunning() const {
    return m_running;
}