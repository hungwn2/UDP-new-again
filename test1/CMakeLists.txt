cmake_minimum_required(VERSION 3.10)
project(test1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -pthread")

include_directories(
    client/include
    server/include
)

# === Client Build ===
add_executable(client_app
    client/client_main.cc
    client/src/client.cc
)

# === Server Build ===
add_executable(server_app
    server/server_main.cc
    server/src/server.cc
    server/src/threadpool.cc
    server/src/udpClientConnection.cc
)
