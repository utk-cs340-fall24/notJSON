#!/bin/bash

# Define the port on which the server will listen
PORT=1234

echo "Bash Echo Server is running and listening on port $PORT..."

# Start the server and listen for incoming connections
while true; do
  {
    # Read the incoming request
    read request

    # Send the HTTP response with CORS headers
    echo -ne "HTTP/1.1 200 OK\r\n"
    echo -ne "Access-Control-Allow-Origin: *\r\n"  # Allow all origins
    echo -ne "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
    echo -ne "Access-Control-Allow-Headers: Content-Type\r\n"
    echo -ne "\r\n"  # End of headers

    # Echo the request back (or process as needed)
    echo -ne "$request\r\n"
  } | netcat -l -p $PORT
done
