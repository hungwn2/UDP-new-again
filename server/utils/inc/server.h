// server.h
#pragma once
#include <arpa/inet.h>
#include <string>
#include <unordered_map>
#include <pthread.h>

class Server {
public:
    using messageCallback = void (*)(Server*, const std::string&, struct sockaddr_in&);
    
    Server();
    ~Server();
    
    void start(int port, messageCallback callback);
    void stop();
    void broadcastMessage(const std::string& message);
    void sendMessage(const std::string& message, struct sockaddr_in& clientAddr);

private:
    void receiverProcedure();
    static void* receiverWrapper(void* param);

    int m_socket;
    bool m_running;
    struct sockaddr_in m_serverAddr;
    messageCallback m_messageCallback;
    pthread_t m_receiverThread;
    std::unordered_map<std::string, struct sockaddr_in> m_knownClients;
    pthread_mutex_t m_mutex;
};
