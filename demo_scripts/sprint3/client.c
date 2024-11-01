#include <arpa/inet.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "embedded_client.h"

#define SERVER_IP "127.0.0.1" // Localhost
#define SERVER_PORT 8080      // Port number to connect to
#define BUFFER_SIZE 256       // Size of send and receive buffers

size_t operation_pack(const operation *struct_operation, u8 **out) {
  size_t metadata_size = sizeof(u8) * 3 + ((0 + 7) / 8) * sizeof(u8);
  printf("%zu\n", metadata_size);
  assert(metadata_size == 3);
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
result addition(operation ops) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = operation_pack(&ops, &send_buffer);
  send_buffer[2] = 0;

  // Step 1: Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed"); // Print error message
    exit(1);
  }
  printf("Socket created successfully.\n");

  // Step 2: Prepare the server address structure
  memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure
  server_addr.sin_family = AF_INET;             // IPv4
  server_addr.sin_port =
      htons(SERVER_PORT); // Convert port to network byte order

  // Convert IPv4 address from text to binary form
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address / Address not supported");
    close(sock); // Close the socket before exiting
    exit(1);
  }
  printf("Server address set to %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 3: Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed"); // Print error message
    close(sock);                 // Close the socket
    exit(1);
  }
  printf("Connected to the server at %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 4: Send data to the server
  printf("Sending data: ");
  for (size_t i = 0; i < send_buffer_size; i++) {
    printf("%02x ", send_buffer[i]); // Print data being sent
  }
  printf("\n");

  bytes_sent = send(sock, send_buffer, sizeof(send_buffer), 0);
  if (bytes_sent < 0) {
    perror("Send failed"); // Print error message
    close(sock);           // Close the socket
    exit(1);
  }
  printf("Sent %zd bytes to the server.\n", bytes_sent);

  // Step 5: Receive response from the server
  bytes_received = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
  if (bytes_received < 0) {
    perror("Receive failed"); // Print error message
    close(sock);              // Close the socket
    exit(1);
  }

  // Step 6: Print the received data
  printf("Received %zd bytes from the server: ", bytes_received);
  for (ssize_t i = 0; i < bytes_received; i++) {
    printf("%02x ", recv_buffer[i]); // Print each byte of received data
  }
  printf("\n");

  // Step 7: Close the socket
  close(sock);
  printf("Socket closed. Exiting program.\n");

  result ret_val = result_unpack(recv_buffer);

  return ret_val;
}
/*
      Perform the operation provded and return the result
     */
result subtraction(operation ops) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = operation_pack(&ops, &send_buffer);
  send_buffer[2] = 1;

  // Step 1: Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed"); // Print error message
    exit(1);
  }
  printf("Socket created successfully.\n");

  // Step 2: Prepare the server address structure
  memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure
  server_addr.sin_family = AF_INET;             // IPv4
  server_addr.sin_port =
      htons(SERVER_PORT); // Convert port to network byte order

  // Convert IPv4 address from text to binary form
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address / Address not supported");
    close(sock); // Close the socket before exiting
    exit(1);
  }
  printf("Server address set to %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 3: Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed"); // Print error message
    close(sock);                 // Close the socket
    exit(1);
  }
  printf("Connected to the server at %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 4: Send data to the server
  printf("Sending data: ");
  for (size_t i = 0; i < sizeof(send_buffer); i++) {
    printf("%02x ", send_buffer[i]); // Print data being sent
  }
  printf("\n");

  bytes_sent = send(sock, send_buffer, sizeof(send_buffer), 0);
  if (bytes_sent < 0) {
    perror("Send failed"); // Print error message
    close(sock);           // Close the socket
    exit(1);
  }
  printf("Sent %zd bytes to the server.\n", bytes_sent);

  // Step 5: Receive response from the server
  bytes_received = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
  if (bytes_received < 0) {
    perror("Receive failed"); // Print error message
    close(sock);              // Close the socket
    exit(1);
  }

  // Step 6: Print the received data
  printf("Received %zd bytes from the server: ", bytes_received);
  for (ssize_t i = 0; i < bytes_received; i++) {
    printf("%02x ", recv_buffer[i]); // Print each byte of received data
  }
  printf("\n");

  // Step 7: Close the socket
  close(sock);
  printf("Socket closed. Exiting program.\n");

  result ret_val = result_unpack(recv_buffer);

  return ret_val;
}
/*
      Perform the operation provded and return the result
     */
result multiplication(operation ops) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = operation_pack(&ops, &send_buffer);
  send_buffer[2] = 2;

  // Step 1: Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed"); // Print error message
    exit(1);
  }
  printf("Socket created successfully.\n");

  // Step 2: Prepare the server address structure
  memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure
  server_addr.sin_family = AF_INET;             // IPv4
  server_addr.sin_port =
      htons(SERVER_PORT); // Convert port to network byte order

  // Convert IPv4 address from text to binary form
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address / Address not supported");
    close(sock); // Close the socket before exiting
    exit(1);
  }
  printf("Server address set to %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 3: Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed"); // Print error message
    close(sock);                 // Close the socket
    exit(1);
  }
  printf("Connected to the server at %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 4: Send data to the server
  printf("Sending data: ");
  for (size_t i = 0; i < sizeof(send_buffer); i++) {
    printf("%02x ", send_buffer[i]); // Print data being sent
  }
  printf("\n");

  bytes_sent = send(sock, send_buffer, sizeof(send_buffer), 0);
  if (bytes_sent < 0) {
    perror("Send failed"); // Print error message
    close(sock);           // Close the socket
    exit(1);
  }
  printf("Sent %zd bytes to the server.\n", bytes_sent);

  // Step 5: Receive response from the server
  bytes_received = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
  if (bytes_received < 0) {
    perror("Receive failed"); // Print error message
    close(sock);              // Close the socket
    exit(1);
  }

  // Step 6: Print the received data
  printf("Received %zd bytes from the server: ", bytes_received);
  for (ssize_t i = 0; i < bytes_received; i++) {
    printf("%02x ", recv_buffer[i]); // Print each byte of received data
  }
  printf("\n");

  // Step 7: Close the socket
  close(sock);
  printf("Socket closed. Exiting program.\n");

  result ret_val = result_unpack(recv_buffer);

  return ret_val;
}
/*
      Perform the operation provded and return the result
     */
result division(operation ops) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = operation_pack(&ops, &send_buffer);
  send_buffer[2] = 3;

  // Step 1: Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed"); // Print error message
    exit(1);
  }
  printf("Socket created successfully.\n");

  // Step 2: Prepare the server address structure
  memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure
  server_addr.sin_family = AF_INET;             // IPv4
  server_addr.sin_port =
      htons(SERVER_PORT); // Convert port to network byte order

  // Convert IPv4 address from text to binary form
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address / Address not supported");
    close(sock); // Close the socket before exiting
    exit(1);
  }
  printf("Server address set to %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 3: Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed"); // Print error message
    close(sock);                 // Close the socket
    exit(1);
  }
  printf("Connected to the server at %s:%d.\n", SERVER_IP, SERVER_PORT);

  // Step 4: Send data to the server
  printf("Sending data: ");
  for (size_t i = 0; i < sizeof(send_buffer); i++) {
    printf("%02x ", send_buffer[i]); // Print data being sent
  }
  printf("\n");

  bytes_sent = send(sock, send_buffer, sizeof(send_buffer), 0);
  if (bytes_sent < 0) {
    perror("Send failed"); // Print error message
    close(sock);           // Close the socket
    exit(1);
  }
  printf("Sent %zd bytes to the server.\n", bytes_sent);

  // Step 5: Receive response from the server
  bytes_received = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
  if (bytes_received < 0) {
    perror("Receive failed"); // Print error message
    close(sock);              // Close the socket
    exit(1);
  }

  // Step 6: Print the received data
  printf("Received %zd bytes from the server: ", bytes_received);
  for (ssize_t i = 0; i < bytes_received; i++) {
    printf("%02x ", recv_buffer[i]); // Print each byte of received data
  }
  printf("\n");

  // Step 7: Close the socket
  close(sock);
  printf("Socket closed. Exiting program.\n");

  result ret_val = result_unpack(recv_buffer);

  return ret_val;
}

int main() {
  printf("Select an operation (+,-,*,/): ");
  char op;
  scanf("%c", &op);

  int one, two;
  printf("Operand 1: ");
  scanf("%d", &one);
  printf("Operand 2: ");
  scanf("%d", &two);

  switch (op) {
  case '+':
    printf("%d\n",
           addition((operation){.operand_one = one, .operand_two = two}).res);
    break;
  case '-':
    printf(
        "%d\n",
        subtraction((operation){.operand_one = one, .operand_two = two}).res);
    break;
  case '*':
    printf("%d\n",
           multiplication((operation){.operand_one = one, .operand_two = two})
               .res);
    break;
  case '/':
    printf("%d\n",
           division((operation){.operand_one = one, .operand_two = two}).res);
    break;
  }
  return 0; // Exit successfully
}
