#!/bin/bash
echo "Starting server..."
./build/server/main &
SERVER_PID=$!
sleep 1

echo "Running client..."
./build/client/main

echo "Killing server..."
kill $SERVER_PID
