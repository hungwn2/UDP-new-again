#include "server.h"
#include <iostream>

int main() {
    Server server(8888);
    server.listenClients(8888, [](Server* srv, ClientConnection* client, std::string& msg) {
        std::cout << "Received from " << client->getClientAddress() << ": " << msg << std::endl;

        std::string bcastMsg = "Broadcast: " + msg;
        srv->broadcastMessage(bcastMsg);

        std::string reply = "Reply: " + msg;
        srv->sendMessage(client, reply);
    });

    while (true);  // Keep server alive
}
