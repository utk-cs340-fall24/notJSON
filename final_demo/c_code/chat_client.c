#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "chat_client.h"

#define SERVER_IP "127.0.0.1" // Localhost
#define SERVER_PORT 8080      // Port number to connect to
#define BUFFER_SIZE 256       // Size of send and receive buffers

size_t chat_message_pack(const chat_message *struct_chat_message, u8 **out) {
  size_t metadata_size = sizeof(u8) * 3 + ((0 + 7) / 8) * sizeof(u8);
  ssize_t optional_index = 0;

  size_t variable_space = 0;

  variable_space += struct_chat_message->message_body_count * sizeof(char);
  variable_space += struct_chat_message->author_count * sizeof(char);
  if (!*out) {
    *out = calloc(1, CHAT_MESSAGE_PACKED_SIZE + metadata_size + variable_space);
  }

  variable_space = CHAT_MESSAGE_PACKED_SIZE + metadata_size;
  u8 *optional = *out + 3;
  (*out)[0] = 0;
  (*out)[1] = 0;

  // message_body
  memcpy(*out + variable_space, struct_chat_message->message_body,
         struct_chat_message->message_body_count *
             sizeof(*struct_chat_message->message_body));
  *(u32 *)(*out + 0 + metadata_size) = variable_space;
  *(u32 *)(*out + 0 + 4 + metadata_size) =
      struct_chat_message->message_body_count;
  variable_space += struct_chat_message->message_body_count *
                    sizeof(*struct_chat_message->message_body);
  // author
  memcpy(*out + variable_space, struct_chat_message->author,
         struct_chat_message->author_count *
             sizeof(*struct_chat_message->author));
  *(u32 *)(*out + 8 + metadata_size) = variable_space;
  *(u32 *)(*out + 8 + 4 + metadata_size) = struct_chat_message->author_count;
  variable_space +=
      struct_chat_message->author_count * sizeof(*struct_chat_message->author);
  // time
  memcpy(*out + 16 + metadata_size, &struct_chat_message->time, 8);

  return variable_space;
}

char *get_chat_message_message_body(const u8 *message) {
  return (char *)(message + *(u32 *)(message + 0 + 3));
}
u32 get_chat_message_message_body_length(const u8 *message) {
  return *(u32 *)(message + 0 + 4 + 3);
}

char *get_chat_message_author(const u8 *message) {
  return (char *)(message + *(u32 *)(message + 8 + 3));
}
u32 get_chat_message_author_length(const u8 *message) {
  return *(u32 *)(message + 8 + 4 + 3);
}

timestamp get_chat_message_time(const u8 *message) {
  return *(timestamp *)(message + 16 + 3);
}

chat_message chat_message_unpack(const u8 *message) {
  return (chat_message){
      .message_body = get_chat_message_message_body(message),
      .message_body_count = get_chat_message_message_body_length(message),
      .author = get_chat_message_author(message),
      .author_count = get_chat_message_author_length(message),
      .time = get_chat_message_time(message),
  };
}
size_t request_pack(const request *struct_request, u8 **out) {
  size_t metadata_size = sizeof(u8) * 3 + ((0 + 7) / 8) * sizeof(u8);
  ssize_t optional_index = 0;

  if (!*out) {
    *out = calloc(1, REQUEST_PACKED_SIZE + metadata_size);
  }

  u8 *optional = *out + 3;
  (*out)[0] = 1;
  (*out)[1] = 0;

  // ignored
  memcpy(*out + 0 + metadata_size, &struct_request->ignored, 8);

  return REQUEST_PACKED_SIZE + metadata_size;
}

timestamp get_request_ignored(const u8 *message) {
  return *(timestamp *)(message + 0 + 3);
}

request request_unpack(const u8 *message) {
  return (request){
      .ignored = get_request_ignored(message),
  };
}

/* Send the provided chat message */
chat_message send_message(chat_message message) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = chat_message_pack(&message, &send_buffer);
  send_buffer[2] = 0;

  // Step 1: Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed"); // Print error message
    exit(1);
  }
  /* printf("Socket created successfully.\n"); */

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
  /* printf("Server address set to %s:%d.\n", SERVER_IP, SERVER_PORT); */

  // Step 3: Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed"); // Print error message
    close(sock);                 // Close the socket
    exit(1);
  }
  /* printf("Connected to the server at %s:%d.\n", SERVER_IP, SERVER_PORT); */

  // Step 4: Send data to the server
  /* printf("Sending data: "); */
  /* for (size_t i = 0; i < send_buffer_size; i++) { */
  /*   printf("%02x ", send_buffer[i]); // Print data being sent */
  /* } */
  /* printf("\n"); */

  bytes_sent = send(sock, send_buffer, send_buffer_size, 0);
  if (bytes_sent < 0) {
    perror("Send failed"); // Print error message
    close(sock);           // Close the socket
    exit(1);
  }
  /* printf("Sent %zd bytes to the server.\n", bytes_sent); */

  // Step 5: Receive response from the server
  bytes_received = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
  if (bytes_received < 0) {
    perror("Receive failed"); // Print error message
    close(sock);              // Close the socket
    exit(1);
  }

  // Step 6: Print the received data
  /* printf("Received %zd bytes from the server: ", bytes_received); */
  /* for (ssize_t i = 0; i < bytes_received; i++) { */
  /*   printf("%02x ", recv_buffer[i]); // Print each byte of received data */
  /* } */
  /* printf("\n"); */

  // Step 7: Close the socket
  close(sock);
  /* printf("Socket closed. Exiting program.\n"); */

  chat_message ret_val = chat_message_unpack(recv_buffer);

  return ret_val;
}
/* Get the latest message from the server */
chat_message get_latest_message(request request) {
  int sock;
  struct sockaddr_in server_addr;
  uint8_t *send_buffer = NULL;
  size_t send_buffer_size;
  uint8_t recv_buffer[BUFFER_SIZE];
  ssize_t bytes_sent, bytes_received;

  send_buffer_size = request_pack(&request, &send_buffer);
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
  /* printf("Sending data: "); */
  /* for (size_t i = 0; i < send_buffer_size; i++) { */
  /*   printf("%02x ", send_buffer[i]); // Print data being sent */
  /* } */
  /* printf("\n"); */

  bytes_sent = send(sock, send_buffer, send_buffer_size, 0);
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

  chat_message ret_val = chat_message_unpack(recv_buffer);

  return ret_val;
}

int main() {
  char buffer[256];

  while (fgets(buffer, sizeof(buffer) - 1, stdin)) {
    buffer[strcspn(buffer, "\n")] = '\0';

    chat_message test = (chat_message){.message_body = buffer,
                                       .message_body_count = strlen(buffer),
                                       .author = getenv("USER"),
                                       .author_count = strlen(getenv("USER")),
                                       .time = time(NULL)};

    send_message((chat_message){.message_body = buffer,
                                .message_body_count = strlen(buffer),
                                .author = getenv("USER"),
                                .author_count = strlen(getenv("USER")),
                                .time = time(NULL)});
  }

  chat_message message = get_latest_message((request){.ignored = time(NULL)});

  char time[256] = {0};
  strftime(time, 255, "%I:%M", localtime(&message.time));

  printf("%*.s <%s>: %*.s\n", (int)message.author_count, message.author, time,
         (int)message.message_body_count, message.message_body);

  return 0; // Exit successfully
}
