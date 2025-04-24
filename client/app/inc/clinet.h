#ifndef DRO_CLIENT_H
#define DRO_CLIENT_H

#include <expected>// for expected
#include <string>  // for basic_string
#include <cstdint> // for uint16_t

#include <netinet/in.h>// for sockaddr_in

#include "client-exception.h"// for ClientException

class Client{
    private:
    using messageCallback=std::function<void(Client *client, std::string &).;
    using connectCallback=std::function<void(Client *client)>;
    static constexpr size_t MAX_BUFFER_SIZE=256;
    pthread_t m_receiverThread;
    pthead_t m_processMessageThread;
    messageCallback m_messageCallback;
    connectCallback m_connectCallback;
    std::atomic<bool> m_isCOnnected(false);
    std::queue<std::string> m_messageQueue;
    int m_cliebtSocket;
    std::string m_host;
    int m_port;
    struct sockaddr_in m_serverAddress;

    public:
    Client()=default;
    Clent(const std::string &host, int port, messaegCallback messageCallback, connectCallback connectCallback);
    ~Client();
    void receviverProceudre();
    void processMessagesProcedure();
    void connectServer();
    void disconnectServer();
    bool isConnected() const;
    void sendMessage(const std::string &message, int sockfd);
    void recvMessaeg(const )
}