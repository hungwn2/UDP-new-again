#include <atomic>
#include <string>

#include <arpa/inet.h>
#include <pthread.h>


class Server;

class clientConnection{
    private:
        sockaddr_in clientAddr;
        std::string m_clientName;
        int m_clientSocket;
        bool m_isConnected;
        mutable std::mutex m_mutex;


    public:
        ClientConnection(int sockfd, const sockaddr_in cliaddr, socklen_t addrLen);
        ~ClientConnection();
        std::string getClientAddress() const;
        void sendMessaeg(const std::string& message);
        void setClientName(const std::string& name);
        bool isConnected() const;
        int getSocketFd() const;
        sockaddr_in getClientAddr() const;
};