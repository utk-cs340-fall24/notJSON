#include "../inc/server.h"
// Client Program
// Connects to a server, sending a hello message

int main(int argc, char* argv[]) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = new_addr(&clientSocket);

    socklen_t lenAddr = sizeof(address);

    int fd = 0;
    char * file  = (char *)malloc(sizeof(char) * sizeof(argv[1]));
    file = argv[1];
    fd = open(argv[1], O_RDONLY);

    if (fd < 1) {
        perror("Unable to open file.");
        return -1;
    }
    int fileSize = lseek(fd, 0, SEEK_END);
    printf("%d \n", fileSize);
    lseek(fd, 0, SEEK_SET);
    char *ServerMessage = (char *)malloc(fileSize * sizeof(char));
    read(fd, ServerMessage, fileSize);


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

        char recBuf[1000];
    
        send(clientSocket, &fileSize, sizeof(fileSize), 0);
        send(clientSocket, ServerMessage, strlen(ServerMessage), 0);
        printf("Client: Message Sent \n");
        //recv(clientSocket, ServerMessage, sizeof(ServerMessage), 0);
        read(clientSocket, recBuf, sizeof(recBuf)-1);
        printf("Message Received. Message: %s\n",  recBuf);


        close(clientSocket);
    
    }
     return 0;
}