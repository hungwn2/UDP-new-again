#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "client_connection.h"

class Server{
    public:
    Server(int port);
    void run();
    void stop();
    private:
    int m_socketFd;
    bool m_running;
    std::mutex m_mutex;
    std::vector<std::thread> m_threads;
    void listenLoop();
};