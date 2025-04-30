# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SERVER_DIR = server
CLIENT_DIR = client
BUILD_DIR = build

# Sources
SERVER_SOURCES = $(wildcard $(SERVER_DIR)/src/*.cc) $(SERVER_DIR)/main.cc
CLIENT_SOURCES = $(wildcard $(CLIENT_DIR)/src/*.cc) $(CLIENT_DIR)/main.cc

# Includes
INCLUDES = -I$(SERVER_DIR)/include -I$(CLIENT_DIR)/include

# Output binaries
SERVER_BIN = $(BUILD_DIR)/server/main
CLIENT_BIN = $(BUILD_DIR)/client/main

# Default target
all: $(SERVER_BIN) $(CLIENT_BIN)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/server
	mkdir -p $(BUILD_DIR)/client

# Build server
$(SERVER_BIN): $(SERVER_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SERVER_SOURCES) $(INCLUDES) -o $(SERVER_BIN)

# Build client
$(CLIENT_BIN): $(CLIENT_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CLIENT_SOURCES) $(INCLUDES) -o $(CLIENT_BIN)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run both
test: all
	./test/test.sh
