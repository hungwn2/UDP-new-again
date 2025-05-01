#pragma once
#include <string.h>
#include <functional.h>
#include <arpa/inet.h>

class UDPHandle {
public:
    using MessageCallback = std::function<void(const std::string&, const struct sockaddr_in&)>;

    UDPHandle();
    ~UDPHandle();

    bool bind(int port);
    bool bindAny(); 

    void setDestination(const std::string& ip, int port);
    
    bool send(const std::string& message);
    bool sendTo(const std::string& message, const std::string& ip, int port);
    bool broadcast(const std::string& message, int port);
    
    bool startReceiving(MessageCallback callback);
    void stopReceiving();

    bool setReuseAddr(bool enable);
    bool setBroadcast(bool enable);
    bool setReceiveBufferSize(int size);
    bool setNonBlocking(bool enable);
    
    int getPort() const;
    std::string getIP() const;
    bool isReceiving() const;
    int getSocket() const { return m_socket; }

private:
    static void* receiveThread(void* arg);
    void receiveLoop();
    bool createSocket();

    int m_socket;
    struct sockaddr_in m_localAddr;
    struct sockaddr_in m_destAddr;
    bool m_isReceiving;
    pthread_t m_receiveThread;
    MessageCallback m_callback;
    //constant and compile time
    static constexpr int BUFFER_SIZE = 65536;
};

