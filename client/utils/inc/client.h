#pragma once
#include <string>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <arpa/inet.h>

class Client {
public:
    using messageCallback = void (*)(Client*, const std::string&);
    
    Client(const std::string& host, int port, messageCallback callback);
    ~Client();
    
    void start();
    void stop();
    void sendMessage(const std::string& message);
    bool isRunning() const;

private:
    void receiverProcedure();
    static void* receiverWrapper(void* param);

    std::string m_host;
    int m_port;
    int m_socket;
    bool m_running;
    struct sockaddr_in m_serverAddr;
    messageCallback m_messageCallback;
    pthread_t m_receiverThread;
};
