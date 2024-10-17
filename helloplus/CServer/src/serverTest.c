// Note: Run/written on Linux Via WSL
// Server Program
// Allows a client to connect, receiving a hello message, and sending it back


#include "../inc/server.h"

int main(int argc, char * argv[]) {

    int fd = 0;
    int serverSocket;
    int opt = 1;
    struct sockaddr_in  address = new_addr(&serverSocket);
    socklen_t lenAddr = sizeof(address);
    // fd = open(argv[1], O_RDONLY);
    char * file  = (char *)malloc(sizeof(char) * sizeof(argv[1]));
    file = argv[1];
   
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket  < 0) {
        perror("Unable to create socket");
        return -1;
    }
    // TODO: Cooldown on running server on same port after a former run, resolve
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bind(serverSocket, (struct sockaddr *)&address, lenAddr);

    listen(serverSocket, 100);
    // printf("%s", buf);
    
    int clientSocket = accept(serverSocket, (struct sockaddr *)&address, &lenAddr);
    if (clientSocket < 0) {
        perror("Error Connecting");
        return -1;
    }


    char * testBuf = "Hello, From Server";
    int fileSize = 0;
    recv(clientSocket, &fileSize, sizeof(fileSize), 0);
    
    
    char recBuf[fileSize];
    recv(clientSocket, recBuf, fileSize, 0);    
    printf("Server: Message Received. Message : %s\n", recBuf);
    
    fd = open("src/receivedFile.c", O_CREAT| O_RDWR, 0666);

    if (fd < 1) {
        perror("Unable to open file.");
        return -1;
    }
    lseek(fd, 0, SEEK_SET);
    write(fd, recBuf, fileSize);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket  < 0) {
        perror("Unable to create socket");
        return -1;
    }
    
    send(clientSocket, testBuf, strlen(testBuf), 0);
    printf("Server: Message Sent.\n");
    
   
    close(serverSocket);
    close(clientSocket);
    close(fd);
    return 0;
}