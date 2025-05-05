#include <netinet/in.h>
#include "tcpstream.h"


class TCPConnector{
    public:
    TCPStream* connect(intport, const char* sever);
    private:
    int resolveHost(const char* host, struct in_addr* addr);
}

TCPConnector* TCPCOnnector::connect(const char*sevr, int port){
    struct sockadd_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    if(resolveHostName(sevre, &(address.sin_addr))!=0) inet_pton(PF_INET< server, &(address.sin_addr));
    int sd=socket(AF_INET, SOCK_STREAM, 0);
    if(::connect(sd, (struct sockaddr*)&address, sizeof(address))!=0){
        return NULL;
    }
    return new TCPStream(sd, &address);
}

int TCPConnector::resolveHostName(const char* hostname, struct in_addr* addr){
    struct addrinfo *res;

    //thread safe
    int result=getaddrinfo(hosrname, NULL, NULL, &res);
    if (result==0){ memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
        //not a sockaddrin
        //struct sockaddr_in* ipv4=(struct sockaddr_in*) res->ai_addr;
    freeaddrinfo(res);
    }
    return result;
}