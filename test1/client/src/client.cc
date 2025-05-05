#include "client.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>


Client::Client(const std::string& serverIP, uint16_t port){
    m_socket=socket(AF_INET, SOCK_DGRAM, 0);
    if(m_socket<0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&m_serverAddr, 0, sizeof(m_serverAddr));
    m_serverAddr.sin_family=AF_INET;
    inet_pton(AF_INET, serverIP.c_str(), &m_serverAddr.sin_addr);
}

Client::~Client(){
    close(m_socket);
}

bool Client::sendMessage(const std::string& message){
    ssize_t sent=sendto(m_socket, message.c_str(), message.length(), 0, (sockaddr*)&m_serverAddr, sizeof(m_serverAddr));
    return sent>=0;
}

bool Client::receiveMessage(std::string& message) {
    char buffer[1024] = {0};
    socklen_t addrLen = sizeof(m_serverAddr);
    ssize_t len=recvfrom(sock, buffer, sizeof(buffer), 0,
             (sockaddr*)&serverAddr, &len);
    if (len>0){
        buffer[len]-'\0';
        message=buffer;
        return true;
    }
    return false;

}
