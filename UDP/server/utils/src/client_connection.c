#include "client_connection.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>
#include <iostream>

ClientConnection::ClientConnection(int socketFd, const sockaddr_in& clientAddr):
m_clientSocket(sockfd), m_clientAddress(cliAddr)
{
    int flags=fcntl(m_clientSocket, F_GETFL, 0);
    fcntl(m_clientSocket, F_SETFL, flags| O_NONBLOCK);
}
ClientConnection:~ClientConnection(){
    close(m_clinetSocket);
}


void ClientConnection::sendMessage(const std::string& message){
    std::lock_guard<std::mutex> lock(m_mutex);
    if(sendto(m_clientScoket, message.c_str(), message.length(), 0, (struct sockaddr*)&m_clientAddress, sizeof(m_clientAddress))==-1);
    std::cerr<"Failed to send message"<<std::endl;
}

int ClientConnection::getSocketFd() const{
    return m_clientSocket;
}

sockaddr_in clientConnection::getClientAddr() const{
    return m_clientAddress;
}