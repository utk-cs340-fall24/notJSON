# This program is intended to be and example of what
# a client program written in python should look like
# once generated by the tool. The idea of creating this
# file is so that once we know what the client should look
# like we can work backwards on the templating aspect to 
# add some variability into the code. In this program we 
# will hard code in a a message_reaction message data 
# structure. This is only an example and test case. The idea
# of using templates is that in the future the user can 
# specify any new type of message

from dataclasses import dataclass
import ctypes
import requests
import struct
from typing import TypeAlias

#typedef char * string;
#typedef int64_t i64;
#typedef uint64_t u64;
#typedef int32_t i32;
#typedef uint32_t u32;
#typedef int16_t i16;
#typedef uint16_t u16;
#typedef int8_t i8;
#typedef uint8_t u8;
#typedef time_t timestamp;
#typedef bool boolean;

string : TypeAlias = str
char : TypeAlias = str
i64 : TypeAlias = ctypes.c_int64
u32 : TypeAlias = ctypes.c_uint32
size_t : TypeAlias = ctypes.c_size_t

typedict = {
    'i32' : ctypes.c_int32,
    'string' : ctypes.c_uint64,
}


#@dataclass
#class reaction:
    ##emoji : ctypes.c_uint64
    #emoji : typedict['string']
    #count : typedict['i32']

#typedef struct operation_msg {
  #random_chars : list[char]
  #size_t random_chars_count;
  #u32 * operands;
  #size_t operands_count;
  #char operation;
#}

@dataclass
class operation_msg:
    random_chars : list[char]
    #random_chars_count : size_t
    operands : list[u32]
    #operands_count : size_t
    operation : char



def main():
    print("hello")

    #make example http get request
    x = requests.get('https://google.com')
    print('Google get request status code: ')
    print(x.status_code)


    # use method 1 (sruct library) to print a binary blob of filler
    # data for the reaction dataclass
    #print(struct.pack('<Ql', 6, 1023))

    op = operation_msg(['a'], [1], 'b')

    print(op.operation)

if __name__ == '__main__':
    main()
