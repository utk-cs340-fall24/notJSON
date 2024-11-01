#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "embedded.h"

size_t operation_pack(const operation *struct_operation, u8 **out) {
  size_t metadata_size = sizeof(u8) * 3 + ((0 + 7) / 8) * sizeof(u8);
  ssize_t optional_index = 0;

  if (!*out) {
    *out = calloc(1, OPERATION_PACKED_SIZE + metadata_size);
  }

  u8 *optional = *out + 3;
  (*out)[0] = 0;
  (*out)[1] = 0;

  // operand_one
  memcpy(*out + 0 + metadata_size, &struct_operation->operand_one, 4);
  // operand_two
  memcpy(*out + 4 + metadata_size, &struct_operation->operand_two, 4);

  return OPERATION_PACKED_SIZE + metadata_size;
}

i32 get_operation_operand_one(const u8 *message) {
  return *(i32 *)(message + 0 + 3);
}

i32 get_operation_operand_two(const u8 *message) {
  return *(i32 *)(message + 4 + 3);
}

operation operation_unpack(const u8 *message) {
  return (operation){
      .operand_one = get_operation_operand_one(message),
      .operand_two = get_operation_operand_two(message),
  };
}
size_t result_pack(const result *struct_result, u8 **out) {
  size_t metadata_size = sizeof(u8) * 3 + ((0 + 7) / 8) * sizeof(u8);
  ssize_t optional_index = 0;

  if (!*out) {
    *out = calloc(1, RESULT_PACKED_SIZE + metadata_size);
  }

  u8 *optional = *out + 3;
  (*out)[0] = 1;
  (*out)[1] = 0;

  // res
  memcpy(*out + 0 + metadata_size, &struct_result->res, 4);

  return RESULT_PACKED_SIZE + metadata_size;
}

i32 get_result_res(const u8 *message) { return *(i32 *)(message + 0 + 3); }

result result_unpack(const u8 *message) {
  return (result){
      .res = get_result_res(message),
  };
}

/*
      Perform the operation provded and return the result
     */
size_t addition(operation ops, u8 **out) {
  result return_val;
  return_val.res = ops.operand_one + ops.operand_two;

  return result_pack(&return_val, out);
}
/*
      Perform the operation provded and return the result
     */
size_t subtraction(operation ops, u8 **out) {
  result return_val;
  return_val.res = ops.operand_one - ops.operand_two;

  return result_pack(&return_val, out);
}
/*
      Perform the operation provded and return the result
     */
size_t multiplication(operation ops, u8 **out) {
  result return_val;
  return_val.res = ops.operand_one * ops.operand_two;

  return result_pack(&return_val, out);
}
/*
      Perform the operation provded and return the result
     */
size_t division(operation ops, u8 **out) {
  result return_val;
  return_val.res = ops.operand_one / ops.operand_two;

  return result_pack(&return_val, out);
}

#define PORT 8080
#define BUFFER_SIZE 1024

// Function to handle incoming data
size_t handle_request(const u8 *input, u8 **output) {
  switch (input[2]) {
  case 0: {
    operation arg = operation_unpack(input);
    return addition(arg, output);
  }
  case 1: {
    operation arg = operation_unpack(input);
    return subtraction(arg, output);
  }
  case 2: {
    operation arg = operation_unpack(input);
    return multiplication(arg, output);
  }
  case 3: {
    operation arg = operation_unpack(input);
    return division(arg, output);
  }
  default:
    puts("unsupported operation");
  }

  return 0;
}

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  u8 buffer[BUFFER_SIZE] = {0};
  u8 *response = NULL;

  // Create socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Set socket options
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  // Define the address
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port %d\n", PORT);

  while (1) {
    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // Read data from the client
    int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
      perror("read");
      close(new_socket);
      continue;
    }

    // Null terminate the received data
    buffer[bytes_read] = '\0';

    // Handle the request
    size_t response_size = handle_request(buffer, &response);

    // Send the response back to the client
    send(new_socket, response, response_size, 0);

    // Close the socket for this client
    close(new_socket);
  }

  return 0;
}
