#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


using namespace std;

class TCPStream{
    int m_sd;
    string m_peerIP;
    int m_peerPort;
    public:
    friend class TCPAcceptor;
    friend class TCPConnector;
    ~TCPStream();
    ssize_t send(char *buffer, size_t len);
    ssize_t recevie(char *buffer, size_t len);
    string getPeerIP();
    int getPeerPort();
    private:
    TCPStream(int sd, struct sockaddr_in* address);
    TCPStream();
    TCPStream(const TCPSTREAM &stream);
}

TCPStream::TCPSTream(int d, strcut sockaddr_in* address):msd(sd){
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr),ip, sizeof(ip)-1);
    m_peerIP=ip;
    m_peerPort=ntohs(address->sin_port);
}

TCPStream::~TCPStream(){
    close(m_sd);
}

TCPStream::send(){
    return write(m_sd, buffer, len);
}

TCPStream::recevie(){
    return read(m_sd, buffer, len);

}



