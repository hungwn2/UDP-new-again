#!/bin/bash

# test/test_udp.sh

SERVER_PORT=9000
SERVER_EXEC=./server/main
CLIENT_EXEC=./client/main

# Start the server in the background
$SERVER_EXEC $SERVER_PORT &
SERVER_PID=$!
echo "Server started with PID $SERVER_PID"
sleep 1  # Allow server to initialize

# Run the client
$CLIENT_EXEC 127.0.0.1 $SERVER_PORT "Hello, UDP Server!"

# Wait for a moment to ensure message exchange
sleep 1

# Terminate the server
kill $SERVER_PID
echo "Server with PID $SERVER_PID terminated"
