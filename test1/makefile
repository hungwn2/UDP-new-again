CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread -Iclient/include -Iserver/include

CLIENT_SRCS = client/src/client.cc client/client_main.cc
SERVER_SRCS = server/src/server.cc server/src/threadpool.cc server/src/udpClientConnection.cc server/server_main.cc

CLIENT_BIN = client_app
SERVER_BIN = server_app

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SERVER_BIN): $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)
