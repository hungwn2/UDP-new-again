#include "client_connection.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

ClientConnection::ClientConnection() = default;
ClientConnection::~ClientConnection() = default;

bool ClientConnection::receiveMessage(int serverSocket) {
    char buffer[1024] = {0};
    socklen_t len = sizeof(m_clientAddr);

    ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                 (struct sockaddr*)&m_clientAddr, &len);
    if (bytesRead < 0) {
        perror("recvfrom");
        return false;
    }

    buffer[bytesRead] = '\0';
    m_message = std::string(buffer);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &m_clientAddr.sin_addr, ip, sizeof(ip));
    m_clientIP = std::string(ip);

    std::cout << "Received from " << m_clientIP << ": " << m_message << std::endl;
    return true;
}

void ClientConnection::sendMessage(int serverSocket, const std::string& msg) {
    sendto(serverSocket, msg.c_str(), msg.length(), 0,
           (struct sockaddr*)&m_clientAddr, sizeof(m_clientAddr));
}

std::string ClientConnection::getClientIP() const {
    return m_clientIP;
}
