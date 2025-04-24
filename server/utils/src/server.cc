// server.h
#pragma once
#include <arpa/inet.h>
#include <string>
#include <unordered_map>
#include <pthread.h>


struct clientId{
    std::string ip;
    uint16_t port;

    booloperator<(const ClientID& other) const{
        return std::tie(ip, port)<std::tie(other.ip, other.port);
    }
}
class Server {
public:
    using messageCallback = void (*)(Server*, const std::string&, struct sockaddr_in&);
    
    Server(int port):m_port=port{
        m_isListenign=true;
        m_socket=socket(AF_INET, SOCK_DGRAM, 0);
        if(m_socket<0) error("Opening socket");
        struct sockaddr_in server;
        m_serverAddr=server;
        serverAddr.sin_family=AF_INET;
        serverAddr.sin_addr.s_addr=INADDR_ANY:
        serverAddr.sin_port=htons(m_port);
        if (bind(m_socketm (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0){
            error("failed to bind");
        }

        std::cout << "[UDP] Server started on port " << m_port << std::endl;
    }
    ~Server(){
        stop();
        close(m_socket);
    }

    
    void start(int port, messageCallback callback){
        m_messageCallback=callback;
        std::thread receiverThread(&Server:receiverProcedure, this);
        receiverThread.detach();
    }
    void stop(){
        m_islistening=false;
    }
    void broadcastMessage(const std::string& message);
    void sendMessage(const std::string& message, struct sockaddr_in& clientAddr){
        std:lock_guard <std::mutex> lock(m_mutex);
        if (m_knownClients.find(id.p+":"+std::to_string(id.port)));
    }

private:
    void receiverProcedure(){
        struct sockaddr_in clientAddr;
        socklen_t clientlen=sizeof(clientAddr);
        while(m_islitening){
            int n=recvfrom(m_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientLen);
            if(n<0) std::cerr<<"error receiving message"<<std::endl;
            char ip[INET_ADDDRSTLEN];
            inet_ntop(AF_INET< &clientAdrr.sin_addr, ip, INET_ADDRSTRLEN);
            std::string clientIP(ip);
            
            ClientID newCLient={clientIP, port};
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_knownClients.find(ClientID)==m_knownCLients.end()){
                m_knownClients[clientId]=clientAddr;
                if (m_connectCallback){
                    m_connectCallback(this, newClient, port);
                }
            }
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

   
};
