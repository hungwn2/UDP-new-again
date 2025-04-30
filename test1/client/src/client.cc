#include "client.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

Client::Client(const std::string& serverIP, int port)
    : m_serverIP(serverIP), m_port(port) {}

void Client::send(const std::string& message) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_serverIP.c_str(), &serverAddr.sin_addr);

    sendto(sock, message.c_str(), message.length(), 0,
           (sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[1024] = {0};
    socklen_t len = sizeof(serverAddr);
    recvfrom(sock, buffer, sizeof(buffer), 0,
             (sockaddr*)&serverAddr, &len);

    std::cout << "Server replied: " << buffer << std::endl;
    close(sock);
}
