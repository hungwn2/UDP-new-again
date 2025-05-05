#pragma once
#include <string>
#include <netinet/in.h>

namespace udphandle{
    bool resolveHostName(const std::string& hostname, struct in_addr* outAddr);
}