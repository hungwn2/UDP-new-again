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
    using messageCallback = std::function<void(const char* data, int len, Server *srv, std::string &ip, uint16_t port)>;
    using connectCallback = std::function<void(Server *srv, char* buffer, std::string& ip, uint16_t port)>;
    void error (const std::string&msg){
        perror(msg);
        exit(1);
    }
    int m_socket;
    char buffer[1024];
    int m_port;
    bool m_isListening;
    struct sockaddr_in m_serverAddr;
    messageCallback m_messageCallback;
    connectCallback m_connectCallback;
    std::unordered_map<std::string, struct sockaddr_in> m_knownClients;
    std::mutex m_mutex;
};
