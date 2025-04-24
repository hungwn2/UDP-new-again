#include <atomic>
#include <string>

#include <arpa/inet.h>
#include <pthread.h>


class Server;

class clientConnection{
    private:
        sockaddr_in clientAddr;
        socklen_t addressLen;
        int socketFd;

    public:
        ClientConnection(int sockfd, const sockaddr_in cliaddr, socklen_t addrLen);
        ~ClientConnection();
        bool sendMessage(const std::string&message);
        std::string getClientAdress() const;
}