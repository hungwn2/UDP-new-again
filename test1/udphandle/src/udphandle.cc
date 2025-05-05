#include "udphandle.h"
#include <netdb.h>
#include <cstring>

namespace udphandle{
    bool resolveHostName(const std::tring& hostname, strucy in_addr* outAddr){
        if(getaddrinfo(hostname.c_str(), nullptr, & hints, &res)==0 && res!=nullptr){
            *outAddr=((struct sockaddr_in*)res->ai_addr)->sin_addr;
            freeaddrinfo(res);
            return true;
        }
        return false;
    }
}
