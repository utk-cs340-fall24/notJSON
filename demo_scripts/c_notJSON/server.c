#include "optional.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 1024

int main() {
  uint8_t *buffer = NULL;

  char *greeting = NULL;
  char *name = NULL;
  int num;
  size_t size;
  char *buf;

  printf("Please input your message: ");
  printf("Greeting (optional): ");
  getline(&buf, &size, stdin);
  buf[strlen(buf) - 1] = 0;
  greeting = malloc(strlen(buf) + 1);
  strcpy(greeting, buf);
  greeting[strcspn(greeting, "\n")] = '\0';
  printf("Name: ");
  getline(&buf, &size, stdin);
  name = malloc(strlen(buf) + 1);
  strcpy(name, buf);
  name[strcspn(name, "\n")] = '\0';

  operation_msg om = {.greeting = greeting,
                      .greeting_count = strlen(greeting),
                      .greeting_present = true,
                      .num_present = false,
                      .name = name,
                      .name_count = strlen(name) + 1};
  size_t bytes = operation_msg_pack(&om, &buffer);

  uint8_t response[BUFFER_SIZE];

  // Create the named pipe
  mkfifo(FIFO_PATH, 0666);

  // Open the FIFO for writing
  int fd = open(FIFO_PATH, O_WRONLY);
  if (fd == -1) {
    perror("Failed to open FIFO for writing");
    exit(EXIT_FAILURE);
  }

  // Send data to the reader
  write(fd, buffer, bytes);
  printf("Writer: Sent data\n");

  // Close the writing end
  close(fd);

  // Open the FIFO for reading (blocking)
  fd = open(FIFO_PATH, O_RDONLY);
  if (fd == -1) {
    perror("Failed to open FIFO for reading");
    exit(EXIT_FAILURE);
  }

  // Receive response from the reader
  read(fd, response, BUFFER_SIZE);
  printf("Writer: Received response: ");
  operation_msg recv = operation_msg_unpack(response);
  printf("Client sent: %s %s %d\n", recv.greeting, recv.name, recv.num);

  // Close the reading end
  close(fd);
  unlink(FIFO_PATH); // Clean up the FIFO
  free(buffer);
  free(greeting);
  free(name);
  free(buf);

  return 0;
}
