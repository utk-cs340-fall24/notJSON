#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char *string;
typedef int64_t i64;
typedef uint64_t u64;
typedef int32_t i32;
typedef uint32_t u32;
typedef int16_t i16;
typedef uint16_t u16;
typedef int8_t i8;
typedef uint8_t u8;
typedef time_t timestamp;
typedef bool boolean;

#define OPERATION_MSG_PACKED_SIZE 24
typedef struct operation_msg {
  char *name;
  size_t name_count;
  char *greeting;
  size_t greeting_count;
  bool greeting_present;
  i32 num;
  bool num_present;
} operation_msg;

size_t operation_msg_pack(const operation_msg *struct_operation_msg, u8 **out);

char *get_operation_msg_name(const u8 *message);
u32 get_operation_msg_name_length(const u8 *message);

char *get_operation_msg_greeting(const u8 *message);
u32 get_operation_msg_greeting_length(const u8 *message);
bool get_operation_msg_greeting_present(const u8 *message);

i32 get_operation_msg_num(const u8 *message);
bool get_operation_msg_num_present(const u8 *message);

operation_msg operation_msg_unpack(const u8 *message);
