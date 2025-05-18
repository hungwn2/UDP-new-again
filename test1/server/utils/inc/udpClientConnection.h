#pragma once

#include <string>
#include <atomic>
#include <pthread.h>
#include <arpa/inet.h>

class server;

class clientConnection{
    public:
        struct sockaddr_in m_clientAddress;
        std
        ClientConnection(Server *server=nullptr);
        ~ClientConnection();
        void sendMessage(int socketFd, const std::string& message) const;
        void setClientAddress(sockaddr_in addr);
        std::string getClientAddress() const;
        std::string getClientName();
        void setName(const std::string &name);


    private:
        struct sockaddr_in m_clientAddress{};
        std::string m_clientName;
        Server* server;

};