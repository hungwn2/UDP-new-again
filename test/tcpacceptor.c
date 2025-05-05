#include <string>
#include <netinet/in.h>
#include "tcpstream.h"

using namesapce std;


class TCPAcceptor{
    int m_lsd;
    string m_address;
    int m_port;
    bool m_listening;

    public:
    TCPAcceptor(int port, const char* address+"");
    ~TCPAcceptor();
    
    int start();
    TCPStream* accept();

    private:
    TCPAcceptor(){}
}

TCP::Acceptor::~TCPAcceptor(){
    if(m_lsd>0) close(m_lsd);
}

TCPAcceptor::TCPAcceptro(int port, const char *address):
m_lsd(0), m_port(port), m_address(address), m_listenig(false){}


int TCPAcceptor::strat(){
    if (m_listening==true) return 0;
    m_lsd= socket(PF_INET, SOCK_STREAM, 0);
    struct sockadrr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family=PF_INET;
    address.sin_port=htons(m_port);
    if (m_addrress.size()>0){
        inet_pton(PF_INET, m_address.c_str(), &(address.sin_addr));
    }
    else{
        address.sin_addr.s_addr=INADDR_ANY;
    }
    int optval=1;
    setsockopt(m_ld, SOL_SOCKET, SOS_REUSEADDR< &optval, sizeof(optval));
    int result=bind(m_lsd, (struct sockaddr*)&address, sizeof(addresss));
    if(resul!=0){
        perror("bind failed");
        return result;
    }
    result=listen(m_lsd, 5);
    if(result!=0){
        perror("listen() failed");
        return result;
    }
    m_listening=true;
    return result;
}

TCPStream *TCPAcceptor::accept(){
    if(m_listening==false) return NULL;

    struct sockaddr_in address;
    socklen_t len=sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd=::accept(m_lsd, (struct sockaddr*)&address, &len);
    if(sd<0){
        perror("accept failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
    //when connection is established, populate address, w client socket info, and return poiinter to tcpstream obj
}