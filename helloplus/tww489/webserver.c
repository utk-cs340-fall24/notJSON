// https://learn.microsoft.com/en-us/windows/win32/api/winsock/
// followed https://www.youtube.com/watch?v=qlymbA0tDMQ tutorial to create simple server
#include <winsock2.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>


int main () {
    WSADATA wsadata;
    char servReq[256] = "sehding test buffer";
    char buffer[256];
    WSAStartup(MAKEWORD(2,2), &wsadata);
    SOCKET testSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(8080);
    bind(testSocket, (SOCKADDR *)&sockAddr, sizeof(sockAddr)); //associates local addr with a socket
    

    listen(testSocket,  SOMAXCONN);// listen allows a socket to listen for an incoming connection
    SOCKET clientSocket = accept(testSocket, 0,0);
    send(clientSocket, buffer, sizeof(buffer)-1, 0);
    shutdown(testSocket, SD_SEND);
     recv(clientSocket, servReq, 256, 0);


        FILE* testFile = fopen("index.html", "r");
        fread(buffer, 1, 256, testFile);
        fclose(testFile);
        send(clientSocket, buffer, sizeof(buffer)-1, 0);

    
     WSACleanup();
    closesocket(testSocket);
}
   