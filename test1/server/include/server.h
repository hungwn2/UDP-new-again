#pragma once

#include <string>
#include <map>
#include <functional>
#include <pthread.h>
#include <netinet/in.h>
#include "udpClientConnection.h"

class ClientConnection;

class Server {
public:
    using messageCallback = std::function<void(Server* srv, ClientConnection* client, std::string&)>;

    Server(int port);
    ~Server();

    void listenClients(int port, messageCallback cb);
    void sendMessage(ClientConnection* client, const std::string& message);
    void broadcastMessage(const std::string& message);

private:
    static constexpr size_t MAX_CLIENT_READ_SIZE = 1024;
    static constexpr size_t MAX_SERVER_EPOLL_EVENTS = 10;

    int m_listeningSocket;
    int m_epollFd;
    int m_listenPort;
    sockaddr_in m_serverAddress;
    epoll_event m_epollEvents[MAX_SERVER_EPOLL_EVENTS];
    pthread_t m_epollThreadId;

    bool m_serverListening;
    std::map<std::string, ClientConnection*> m_connections;

    pthread_mutex_t m_mutex;
    messageCallback m_messageCallback;

    void epollClientsProcedure();
};
