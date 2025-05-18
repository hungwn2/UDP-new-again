#include "server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

Server::Server(int port) : m_running(true) {
    m_socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socketFd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(m_socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(m_socketFd);
        exit(EXIT_FAILURE);
    }
}

void Server::run() {
    std::cout << "Server running..." << std::endl;
    listenLoop();
}

void Server::listenLoop() {
    while (m_running) {
        ClientConnection client;
        char buffer[1024];
        sockaddr_in clientAddr{};
        socklen_t addrLen=sizeof(clientAddr);
        ssize_t bytesReceived=recvfrom(
            m_socketFd,
            buffer,
            sizeof(buffer),
            0
            (struct sockaddr*)&clientAddr,
            &addrLen
        );
        if (bytesReceived>0){
            client.setClientAddrress(clientAddr);
            std::string message(buffer, bytesReceived);
            std::cout<<"received: "<<message<<" from "<<client.getClientAddress()<<std::endl;
            std::string reply="ACK from server";
            client.sendMessage(m_socketFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);
            i
        }
    }
}

void Server::stop() {
    m_running = false;
    close(m_socketFd);
}
