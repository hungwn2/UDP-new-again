#include "server.h"
#include "client_connection.h"
#include <iostream>

int main() {
    Server server;

    server.listenClients(8888, [](Server* srv, ClientConnection* client, std::string& msg) {
        std::string clientId = client->getClientAddress();
        std::cout << "[RECEIVED from " << clientId << "]: " << msg << std::endl;

        if (msg == "broadcast") {
            std::string bcastMsg = "[Broadcast] Hello to all clients!";
            srv->broadcastMessage(bcastMsg);
        } else {
            std::string reply = "Echo: " + msg;
            srv->sendMessage(client, reply);
        }
    });

    std::cout << "Server running on port 8888. Press Ctrl+C to stop.\n";

    // Keep the server alive
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
