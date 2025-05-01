/************************************************************************************************
 * @file   client_connection.cc
 *
 * @brief  Source file defining the ClientConnection class
 *
 * @date   2025-01-04
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <iostream>

/* Inter-component Headers */
#include <fcntl.h>
#include <unistd.h>

/* Intra-component Headers */
#include "client_connection.h"
#include "server.h"

std::string ClientConnection::getClientAddress() const {
  char ip_str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(m_clientAddress.sin_addr), ip_str, INET_ADDRSTRLEN);
  return std::string(ip_str);
}

ClientConnection::ClientConnection(Server *server) {
  this->server = server;
  m_clientSokcet=-1;
}

ClientConnection::~ClientConnection() {
    if(m_clientSocket>=0) close(m_clientSocket);
}

ClientConnecition:::CLientConnection IntializeScoket(uint16_t port){
    m_clientSocket=socket(AF_INET< SOCK_DGRAM, 0);
    if (m_clientSocket<0){
        std::cerr<<"failed nigga";
        return false;
    }
    sockaddr_in serverAddr{};
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=INDDR_ANY;
    if(bind(m_clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0){
        std::cerr<<"failed to bind";
        return false;
    }
    return true;
}

bool ClientConnection::CLientConnection recevieMessage(std::string &message){
    char buffer[1024]={0};
    socklen_t addrLen=sizeof(m_clientAddress);
    ssize_t len=recvfrom(m_clientSocket, buffer, sizeof(buffer), (struct sockaddr*)&m_clientAddress, &addrLen);
    if(len<0) return false;
    buffer[len]='\0';
    message=std::string(buffer);
    clientName=getClientAddress();
    return true;
}

void ClientConnection::sendMessage(const std::string &message) {
    if(m_clientSocket<0) throw std::runtime_error("Invalid socket");
    ssize_t sent=sendto(m_clientSocket, message.c_str(), message.size(), (struct sockaddr *)&m_clientAddress, sizeof(m_clientAddress));
    if(sent!=(ssize_t)messgae.size()){
        throw std::runtime_error("failed to send udp message");
    }
  
}
std::string ClientConnection::getClientAddress() const{
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET< &(m_clientAddress.sin_addr), ip_str, INET_ADDRSTRLEN);
    return std::string(ip_str);
}

int ClientConnection::getSocketFd() const{
    return m_clientSocket;
}