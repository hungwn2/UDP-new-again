#pragma once
#include <string>
#include <atomic>
#include <string>
#include <arpa/inet.h>
#inclue <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

class Client {
public:
    using messageCallbackk=std::function<void(Client *client, std::string &)>;
    std::atomic<bool> m_isConnected{false};
    std::queue<std::string> m_messageQueue;
    int m_clientSocket;
    std::string m_host;
    static constexpr size_t MAX_BUFFER;
    pthread_mutex_t m_mutex;
    sem_t m_messageSemaphore;
    pthread_t m_receiverThreadId;
    pthread_t m_processMessageThreadId;
    
    Client(const std::string& serverIP, uint16_t port);
    ~Client();


    bool sendMessage(const std::string& message);
    bool receiveMessage(std::string& message);
private:
    int m_socket;
    struct sockaddr_in m_serverAddr;
};
