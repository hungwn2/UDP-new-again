#pragma once
#include <string>

class Client {
public:
    Client(const std::string& serverIP, int port);
    void send(const std::string& message);

private:
    std::string m_serverIP;
    int m_port;
};
