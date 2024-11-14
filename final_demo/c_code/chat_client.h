#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef char* string;
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

#define CHAT_MESSAGE_PACKED_SIZE 24
  typedef struct chat_message {
      char* message_body;
      size_t message_body_count;
      char* author;
      size_t author_count;
      timestamp time;
  } chat_message;

#define REQUEST_PACKED_SIZE 8
  typedef struct request {
      timestamp ignored;
  } request;


size_t chat_message_pack(const chat_message* struct_chat_message, u8** out);

        char* get_chat_message_message_body(const u8* message);
        u32 get_chat_message_message_body_length(const u8* message);

        char* get_chat_message_author(const u8* message);
        u32 get_chat_message_author_length(const u8* message);

        timestamp get_chat_message_time(const u8* message);


  chat_message chat_message_unpack(const u8* message);
size_t request_pack(const request* struct_request, u8** out);

        timestamp get_request_ignored(const u8* message);


  request request_unpack(const u8* message);

