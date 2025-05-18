#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "client_connection.h"
#include <chrono>
#include <arpa/inet.h>
#include <unistd.h>
#include "network_time_protocol.h"


class Server{

    private:
    static constexpr int NTP_Port=123;

    using messageCallback=std::function<void(Server *srv, ClientConnection *src, std::string &)>;
    pthread_t m_mutex;
    std::atomic<bool> m_serverListening;
    int m_listenPort;
    int m_listeningSocket;
    static const constexpr unsigned int MAX_CLIENT READ_SIZE=256U;
    i
    struct scokaddr_in m_serverAddress;
    
    public:
    Server();
    void run();
    void stop();
    void listenNewClientsProceudre();
    private:
    int m_socketFd;
    std::atomic<bool> m_running;
    std::vector<std::thread> m_threads;
    void listenLoop();
};