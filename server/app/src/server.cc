#include "server.h"

#include <arpa/inet.h> // for htonl, htons
#include <netinet/in.h>// for sockaddr_in, INADDR_ANY, in_addr
#include <sys/epoll.h> // for epoll_event, epoll_ctl, EPOLLIN, EPOLL_CTL_ADD
#include <sys/socket.h>// for AF_INET, accept, bind, listen, socket, SOCK_...
#include <unistd.h>    // for close, read, write

#include <chrono>// for high_resolution_clock
#include <cstdint>
#include <expected>       // for expected
#include <iostream>       // for operator<<, basic_ostream, cout
#include <source_location>// for source_location
#include <thread>         // for thread

#include "server-exception.h"// for ServerException
#include "thread-pool.h"     // for ThreadPool

namespace dro


std::expected <bool, serve
Server::Server(uint16_t port, uint32_t max_events, uint32_t max_clients, uint32_t buffer_size, char tcp_udp)
    : port_(port), max_events_(max_events), max_clients_(max_clients), buffer_size_(buffer_size), tcp_udp_(tcp_udp)
{
}
