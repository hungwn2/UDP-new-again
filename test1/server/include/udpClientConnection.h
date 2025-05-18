#pragma once

#include <string>
#include <netinet/in.h>

class Server;

class ClientConnection {
public:
    ClientConnection(Server* server = nullptr);
    ~ClientConnection();

    void sendMessage(int socketFd, const std::string& message) const;
    void setClientAddress(sockaddr_in addr);
    std::string getClientAddress() const;
    std::string getClientName() const;
    void setName(const std::string& name);

private:
    sockaddr_in m_clientAddress{};
    std::string m_clientName;
    Server* m_server;
};
