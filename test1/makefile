# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iserver/include -Iclient/include -Iutils/inc

# Source files
SRCS = \
    main.cc \
    server/src/server.cc \
    client/src/client.cc \
    utils/src/ntp_server.cc \
    utils/src/udpClientConnection.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Output binary name
TARGET = main

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
