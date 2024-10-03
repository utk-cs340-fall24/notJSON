#include "../inc/server.h"

#define PORT 8080

// Fills a socket address 
struct sockaddr_in new_addr(int *socketfd) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    return address;
}


int end_connection(int socket) {
    close(socket);
    return 0;
}
