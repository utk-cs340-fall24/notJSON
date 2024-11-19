#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "chat_server.h"

chat_message last_message;

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
size_t send_message(chat_message message, u8 **out) {
  chat_message return_val;

  char time[256] = {0};
  if (strftime(time, 255, "%I:%M", localtime(&message.time)) == 0) {
    perror("strftime");
  }

  printf("%.*s <%s>: %.*s\n", (int)message.author_count, message.author, time,
         (int)message.message_body_count, message.message_body);

  last_message = message;
  return_val = message;

  return chat_message_pack(&return_val, out);
}
/* Get the latest message from the server */
size_t get_latest_message(request request, u8 **out) {
  chat_message return_val;

  return_val = last_message;

  return chat_message_pack(&return_val, out);
}

#define PORT 8080
#define BUFFER_SIZE 1024

// Function to handle incoming data
size_t handle_request(const u8 *input, u8 **output) {
  switch (input[2]) {
  case 0: {
    chat_message arg = chat_message_unpack(input);
    return send_message(arg, output);
  }
  case 1: {
    request arg = request_unpack(input);
    return get_latest_message(arg, output);
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

    printf("here\n");
    // printf("%hhi", buffer[7]);
    for (int i=0; i<bytes_read; i++) {
      printf("%02x ", buffer[i]);
      if ((i+1)%16 == 0) printf("\n");
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
