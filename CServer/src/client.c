#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080

int main(int argc, char* argv[]) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    socklen_t lenAddr = sizeof(address);


    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket  < 0) {
        perror("Unable to create socket");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int connectStatus = connect(clientSocket, (struct sockaddr*)&address, lenAddr);
    if (connectStatus== -1) {
        perror("Unable to Connect to Server");
        return -1;
    }
    else {
        char * ServerMessage = "Hello, From Client";
        char recBuf[1000];
        send(clientSocket, ServerMessage, strlen(ServerMessage), 0);
        printf("Client: Message Sent \n");
        //recv(clientSocket, ServerMessage, sizeof(ServerMessage), 0);
        read(clientSocket, recBuf, sizeof(recBuf));
        printf("Message Received. Message: %s\n", recBuf);


        close(clientSocket);
    
    }
     return 0;
}