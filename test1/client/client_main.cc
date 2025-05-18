#include "client.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Client client("127.0.0.1", 8888); // Connect to local UDP server on port 8888

    client.setMessageCallback([](Client* c, std::string& msg) {
        std::cout << "[RECEIVED FROM SERVER]: " << msg << std::endl;
    });

    // Send some messages
    client.sendMessage("Hello, Server!");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    client.sendMessage("broadcast");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Keep the client alive
    std::cout << "Client running. Press Ctrl+C to exit.\n";
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
