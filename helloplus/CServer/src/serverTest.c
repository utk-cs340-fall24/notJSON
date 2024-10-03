// Note: Run/written on Linux Via WSL
// Server Program
// Allows a client to connect, receiving a hello message, and sending it back


#include "../inc/server.h"

int main(int argc, char * argv[]) {
    if (argc != 2) {
        perror("Error: Need an argument");
        return -1;
    }
    int fd = 0;
    int serverSocket;
    int opt = 1;
    struct sockaddr_in  address = new_addr(&serverSocket);
    socklen_t lenAddr = sizeof(address);
    // fd = open(argv[1], O_RDONLY);
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
    char *buf = (char *)malloc(fileSize * sizeof(char));
    read(fd, buf, fileSize);
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket  < 0) {
        perror("Unable to create socket");
        return -1;
    }

    // TODO: Cooldown on running server on same port after a former run, resolve
<<<<<<< HEAD
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_RCVTIMEO | SO_KEEPALIVE, &opt, sizeof(opt));
=======
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
>>>>>>> cb9b675563a4c950b93493553f17e4c07053332c

    bind(serverSocket, (struct sockaddr *)&address, lenAddr);

    listen(serverSocket, 100);
    // printf("%s", buf);
    
    int clientSocket = accept(serverSocket, (struct sockaddr *)&address, &lenAddr);
    if (clientSocket < 0) {
        perror("Error Connecting");
        return -1;
    }

<<<<<<< HEAD
    int running = 1;


    while (running) {
        sleep(10);
        char testBuf[1000] = "Message Received";
        char recBuf[1000];
        recv(clientSocket, recBuf, sizeof(recBuf)-1 ,  MSG_WAITALL);
        printf("Server: Message Received. Message : %s\n", recBuf);
        send(clientSocket, testBuf, strlen(testBuf), 0);
        printf("Server: Message Sent.\n");
    }
=======

    char * testBuf = "Hello, From Server";
    char recBuf[1000];
    read(clientSocket, recBuf, sizeof(recBuf)-1);
    printf("Server: Message Received. Message : %s\n", recBuf);
    
    send(clientSocket, testBuf, strlen(testBuf), 0);
    printf("Server: Message Sent.\n");
>>>>>>> cb9b675563a4c950b93493553f17e4c07053332c
    
   
    close(serverSocket);
    close(clientSocket);
    close(fd);
    return 0;
}