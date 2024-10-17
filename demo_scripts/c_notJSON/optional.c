#include "optional.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t operation_msg_pack(const operation_msg *struct_operation_msg, u8 **out) {
  size_t metadata_size = sizeof(u8) + sizeof(u8) + ((2 + 7) / 8) * sizeof(u8);
  ssize_t optional_index = 0;

  size_t variable_space = 0;

  variable_space += struct_operation_msg->name_count * sizeof(char);
  if (struct_operation_msg->greeting_present) {
    variable_space += struct_operation_msg->greeting_count * sizeof(char);
  }
  if (*out == NULL) {
    *out =
        calloc(1, OPERATION_MSG_PACKED_SIZE + metadata_size + variable_space);
  }

  variable_space = OPERATION_MSG_PACKED_SIZE + metadata_size;
  u8 *optional = *out + 2;
  (*out)[0] = 0;
  (*out)[1] = 0;

  // name
  memcpy(*out + variable_space, struct_operation_msg->name,
         struct_operation_msg->name_count *
             sizeof(*struct_operation_msg->name));
  *(u32 *)(*out + 0 + metadata_size) = variable_space;
  *(u32 *)(*out + 0 + 4 + metadata_size) = struct_operation_msg->name_count;
  variable_space +=
      struct_operation_msg->name_count * sizeof(*struct_operation_msg->name);
  // greeting
  if (struct_operation_msg->greeting_present) {
    optional[optional_index / 8] |= (1 << optional_index % 8);
    memcpy(*out + variable_space, struct_operation_msg->greeting,
           struct_operation_msg->greeting_count *
               sizeof(*struct_operation_msg->greeting));
    *(u32 *)(*out + 8 + metadata_size) = variable_space;
    *(u32 *)(*out + 8 + 4 + metadata_size) =
        struct_operation_msg->greeting_count;
    variable_space += struct_operation_msg->greeting_count *
                      sizeof(*struct_operation_msg->greeting);
  } else {
    optional[optional_index / 8] &= ~(1 << optional_index % 8);
  }
  ++optional_index;
  // num
  if (struct_operation_msg->num_present) {
    optional[optional_index / 8] |= (1 << optional_index % 8);
    memcpy(*out + 16 + metadata_size, &struct_operation_msg->num, 4);
  } else {
    optional[optional_index / 8] &= ~(1 << optional_index % 8);
  }
  ++optional_index;

  return variable_space;
}

char *get_operation_msg_name(const u8 *message) {
  return (char *)(message + *(u32 *)(message + 0 + 3));
}
u32 get_operation_msg_name_length(const u8 *message) {
  return *(u32 *)(message + 0 + 4 + 3);
}

char *get_operation_msg_greeting(const u8 *message) {
  return (char *)(message + *(u32 *)(message + 8 + 3));
}
u32 get_operation_msg_greeting_length(const u8 *message) {
  return *(u32 *)(message + 8 + 4 + 3);
}
bool get_operation_msg_greeting_present(const u8 *message) {
  return ((message + 2)[0 / 8] >> (0 % 8)) & 0x1;
}

i32 get_operation_msg_num(const u8 *message) {
  return *(i32 *)(message + 16 + 3);
}
bool get_operation_msg_num_present(const u8 *message) {
  return ((message + 2)[1 / 8] >> (1 % 8)) & 0x1;
}

operation_msg operation_msg_unpack(const u8 *message) {
  return (operation_msg){
      .name = get_operation_msg_name(message),
      .name_count = get_operation_msg_name_length(message),
      .greeting = get_operation_msg_greeting_present(message)
                      ? get_operation_msg_greeting(message)
                      : 0,
      .greeting_count = get_operation_msg_greeting_present(message)
                            ? get_operation_msg_greeting_length(message)
                            : 0,
      .greeting_present = get_operation_msg_greeting_present(message),
      .num = get_operation_msg_num_present(message)
                 ? get_operation_msg_num(message)
                 : 0,
      .num_present = get_operation_msg_num_present(message),
  };
}
