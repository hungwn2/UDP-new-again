
#include "serverException.h"
#include <expected>
#include <stdint>
#include <netinet/in.h>
#include "thread-pool.h"


class Server{
    public:
        Server()=default;
        


}

void Server::handle_client(int listeningSocket)
char *client_ip=inet_ntoa(client_addr.sin_addr);
printf