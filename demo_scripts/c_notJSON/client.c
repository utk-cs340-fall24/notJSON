#include "optional.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 1024

int main() {
  uint8_t buffer[BUFFER_SIZE];
  uint8_t *response = NULL;

  // Open the FIFO for reading (blocking)
  int fd = open(FIFO_PATH, O_RDONLY);
  if (fd == -1) {
    perror("Failed to open FIFO for reading");
    exit(EXIT_FAILURE);
  }

  // Receive data from the writer
  read(fd, buffer, BUFFER_SIZE);
  operation_msg msg = operation_msg_unpack(buffer);
  printf("Server sent: %.2s %s %s\n", msg.greeting, msg.name,
         msg.num_present ? "Num present" : "Num optional");

  // Open the FIFO for writing
  fd = open(FIFO_PATH, O_WRONLY);
  if (fd == -1) {
    perror("Failed to open FIFO for writing");
    exit(EXIT_FAILURE);
  }

  // Send response back to the writer
  operation_msg om = {.greeting = "hi",
                      .greeting_count = 3,
                      .greeting_present = true,
                      .num = 400,
                      .num_present = true,
                      .name = "Server",
                      .name_count = strlen("Client") + 1};
  size_t bytes = operation_msg_pack(&om, &response);
  write(fd, response, bytes);
  printf("Reader: Sent response\n");

  // Close the writing end
  close(fd);
  free(response);

  return 0;
}
