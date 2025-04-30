#include "client.h"

int main() {
    Client client("127.0.0.1", 8080);
    client.send("Hello from client");
    return 0;
}
