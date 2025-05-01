#include "client_connection.h"
#include <cstring>
#include <unistd.h> // For close()

ClientConnection::ClientConnection(int sockfd, const sockaddr_in cliaddr, socklen_t addrLen):
socketFd(sockfd), clientAddr(cliAddr), addressLen(addrLen){}
ClientConnection:~ClientConnection(){
    close(socketFd);
}
~ClientConnection();
bool sendMessage(const std::string&message){
    ssize_t n=send(socketfd, message.c_str())
}
std::string getClientAdress() const;
}