#include "client.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>


Clent(const std::string &host, int port, messaegCallback messageCallback, connectCallback connectCallback);
~Client();
void receviverProceudre();
void processMessagesProcedure(){
    while (m_isCOnnected){
        std::unique_lock<stdLLmutex> lock(m_mutex);
        m
    }
}
void connectServer(){
    if (socket())
}
void disconnectServer();
bool isConnected() const;
void sendMessage(const std::string &message, int sockfd){

    socklen_t serverlen=sizeof(m_serverAddress);
    if (sendto(sockfd, message.c_str(), message.size()+1, 0,(sockaddr*)&m_serverAddress,serverlen)==-1){
        std::coiut<<"failed to send message\n"
        return 1;
    }
    return 0;
}
void recvMessaeg(int sockfd, char buf[]){
    socklen_t serverlen=sizeof(m_serverAddress);
    return recvfrom(sockfd, buf, buffer_size_, 0, (sockaddr *)&m_serveraddr, &serverlen);
}