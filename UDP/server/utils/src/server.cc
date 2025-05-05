// server.h
#pragma once
#include <arpa/inet.h>
#include <string>
#include <unordered_map>
#include <pthread.h>
#include <mutex>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <thread>
#include "server.h"


struct clientId{
    std::string ip;
    uint16_t port;

    booloperator==(const ClientID& other) const{
        return std::tie(ip, port)<std::tie(other.ip, other.port);
    }
};



//hash function for client ids
namespace std{
    template<>
    struct hash<ClientId>{
        std::size_t operator()(const ClientId& id) const{
            return hash<string>()(id.ip)^hash<uint16_t>()(id.port);        
        }
    }
}


    using messageCallback = void (*)(Server*, const std::string&, struct sockaddr_in&);
    
    Server(int port) : m_port(port), m_running(true){
        m_socket=socket(AF_INET, SOCK_DGRAM, 0);
        if(m_socket<0) error("Opening socket");
        
        struct sockaddr_in serverAddr{};
        serverAddr.sin_family=AF_INET;
        serverAddr.sin_addr.s_addr=INADDR_ANY:
        serverAddr.sin_port=htons(m_port);
        
        if (bind(m_socketm (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0){
            error("failed to bind");
        }

        std::cout << "[UDP] Server started on port " << m_port << std::endl;
    }
    Server::~Server(){
        m_running=false;
        close(m_socket);
    }

    
    void Server::start(MessageCallback callback){
        m_messageCallback=callback;
        std::thread receiverThread(&Server:receiverProcedure, this);
        receiverThread.detach();
    }

    void Server::stop(){
        m_running=false;
    }
    void Server::sendMessage(const std::string& message, struct sockaddr_in& clientAddr){
        std:lock_guard <std::mutex> lock(m_mutex);
        auto it=m_knownClinet.find(id);
        if (it!=m_kknownClients.end()){
            sendto(m_socket, message.c_str(), message.length(), 0, (struct sockaddr*)&it->second, sizeof(it->second));
        }else{
            std::cerr<"Client not found"<<id.ip<<",  "<<id.port<<std::endl;
        }
    }

    void Server::broadcastMessage(const std::string& message){
        std::lock_guard<std::mutex> lock(m_mutex);
        for(const auto& pair: m_knownClients){
            sendto(m_socket, message.c_str(), message.length(), 0, (struct sockaddr*)&pair.second, sizeof(pair.second));
        }
    
    }

private:
    int m_socket;
    int m_port;
    bool m_running;
    std::mutex m_mutex;
    std::unordered_map<ClientId, struct sockaddr_in>m_knownClients;
    MessageCallback m_messageCallback=nullptr;
    void receiverProcedure(){
        char buffer[1024];
        struct sockaddr_in clientAddr{};
        socklen_t clientLen=sizeof(clientAddr);
        while(m_running){
            int n=recvfrom(m_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientLen);
            if(n<0){
                std::cerr<<"error receiving message"<<std::endl;
                continue;
            }
            buffer[n]='\0';
            char ip[INET_ADDDRSTLEN];
            inet_ntop(AF_INET< &clientAdrr.sin_addr, ip, INET_ADDRSTRLEN);
            uint16_t port=ntohs(clientAddr.sin_port);
            ClientId id{ip, port};

            {
                std:lock_guard<std::mutex>lock(m_mutex);
                m_knownClients.emplace(id, clientAddr);
            }
           
       
            if(messageCallback){
                m_messageCallback(this, buffer, n , clientId, port);
            }
        }
    }



    void *Server::recevierWrapper(void *params){
        Server *server=static_cast<Sevrer *>(params);
        try{
            server->receiverProcedure();
        }catch(std::exception &e){
            std::cerr<<"Excpetion in receiver thread"<< e.what()<<std::endl;
        }
        return nullptr;
    }

    void Server::sendMessage(clientId id, const std::string &message){
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_knownClients.find(id.ip)!=m_knownClients.end()){
            struct sockaddr clientAddr=m_knownClients[ip];
            sendto(m_socket,, message.c_str(), message.length(), 0, (struct sockaddr*) clientAddr, sizeof(clientAddr));
        }
        else{
            std::cerr<<"client not dound"<<std::endl;
        }
    }
    void Server::RemoveClient(ClientId id){
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_knownClients.find(id.ip)!=m_knownClients.end()){
            
            std::cerr<<"Reoved client "<< clinet->getClientName()<<std::endl;
            
        }
    }
    void Server::broadcastMessage(const std::string &message){
        {
        std::lock_guard<std::mutex> lock(&m_mutex);
        for (auto &pair:m_connections){
            if (pair.second->isConnected()) pair.second->sendMessage(message);
        }
         }
    }

   
