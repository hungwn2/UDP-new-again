# Makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -pthread -std=c++17

# Source files
SERVER_SRC = server/server.cpp
CLIENT_SRC = client/client.cc
UDPHANDLE_SRC = udphandle/udphandle.cpp

# Object files
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
CLIENT_OBJ = $(CLIENT_SRC:.cc=.o)
UDPHANDLE_OBJ = $(UDPHANDLE_SRC:.cpp=.o)

# Executables
SERVER_BIN = server/server
CLIENT_BIN = client/client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC) $(UDPHANDLE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CLIENT_BIN): client/main.cpp $(CLIENT_SRC) $(UDPHANDLE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f server/server client/client *.o
