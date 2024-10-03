#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
<<<<<<< HEAD
#include <arpa/inet.h>

#define PORT 8080

struct sockaddr_in new_addr(int *socketfd); // Fills Socket Address
int end_connection(int); // Disconnects from the server.
=======

#define PORT 8080

struct sockaddr_in new_addr(int *socketfd);
>>>>>>> cb9b675563a4c950b93493553f17e4c07053332c
