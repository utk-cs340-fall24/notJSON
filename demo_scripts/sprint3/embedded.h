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

#define OPERATION_PACKED_SIZE 8
  typedef struct operation {
      i32 operand_one;
      i32 operand_two;
  } operation;

#define RESULT_PACKED_SIZE 4
  typedef struct result {
      i32 res;
  } result;


size_t operation_pack(const operation* struct_operation, u8** out);

        i32 get_operation_operand_one(const u8* message);

        i32 get_operation_operand_two(const u8* message);


  operation operation_unpack(const u8* message);
size_t result_pack(const result* struct_result, u8** out);

        i32 get_result_res(const u8* message);


  result result_unpack(const u8* message);

  /* 
        Perform the operation provded and return the result
       */
  size_t addition(
    operation ops,
  u8 **out
  );
  /* 
        Perform the operation provded and return the result
       */
  size_t subtraction(
    operation ops,
  u8 **out
  );
  /* 
        Perform the operation provded and return the result
       */
  size_t multiplication(
    operation ops,
  u8 **out
  );
  /* 
        Perform the operation provded and return the result
       */
  size_t division(
    operation ops,
  u8 **out
  );
