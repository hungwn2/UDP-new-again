#pragma once
#include <netinet/in.h>
#include <string>


class ClientConnection{
    public:
    ClientConnection();
    ~ClientConnection();

    bool receiveMessage(int serverSocket);
    void sendMessage(int serverSocket, const std::string &msg);
    std::string getClientIP() const;

    private:
    sockaddr_in m_clientAddr;
    std::string m_clientIP;
    std::string m_message;
};