#include "../inc/server.h"
// Client Program
// Connects to a server, sending a hello message

int main(int argc, char* argv[]) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = new_addr(&clientSocket);

    socklen_t lenAddr = sizeof(address);

    if (clientSocket  < 0) {
        perror("Unable to create socket");
        return -1;
    }



    int connectStatus = connect(clientSocket, (struct sockaddr*)&address, lenAddr);
    if (connectStatus== -1) {
        perror("Unable to Connect to Server");
        return -1;
    }
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }


    else {
        int running = 1;
            char ServerMessage[1000]= "Hello, From Client";
            char recBuf[1000];
            send(clientSocket, ServerMessage, strlen(ServerMessage), 0);
            printf("Client: Message Sent \n");
            //recv(clientSocket, ServerMessage, sizeof(ServerMessage), 0);
            recv(clientSocket, recBuf, sizeof(recBuf)-1,  MSG_WAITALL);
            printf("Client: Message Received. Message: %s\n",  recBuf);
        while (running) {
            scanf(" %s", ServerMessage);
            printf("Used: %s \n", ServerMessage);
            send(clientSocket, ServerMessage, strlen(ServerMessage), 0);
            printf("Client: Message Sent \n");
            //recv(clientSocket, ServerMessage, sizeof(ServerMessage), 0);
            recv(clientSocket, recBuf, sizeof(recBuf)-1,  MSG_WAITALL);
            printf("Client: Message Received. Message: %s\n",  recBuf);
        }

        end_connection(clientSocket);

    }
     return 0;
}