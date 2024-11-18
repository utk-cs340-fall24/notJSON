from dataclasses import dataclass
import ctypes
import requests
import struct
from typing import TypeAlias
import pprint
import socket

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
u64 : TypeAlias = ctypes.c_uint64
i32 : TypeAlias = ctypes.c_int32
u32 : TypeAlias = ctypes.c_uint32
i16 : TypeAlias = ctypes.c_int16
u16 : TypeAlias = ctypes.c_uint16
i8 : TypeAlias = ctypes.c_int8
u8 : TypeAlias = ctypes.c_uint8
size_t : TypeAlias = ctypes.c_size_t


class chat_message:
    message_body : string
    author : string
    time : i64


def chat_message_unpack(binary_string):
    format_string_mapping = {
        'string' : 'q',
        'char' : 'B',
        'i64' : 'q',
        'ui64' : 'Q',
        'i32' : 'i',
        'ui32' : 'I',
        'i16' : 'h',
        'ui6' : 'H',
        'i8' : 'b',
        'u8' : 'B'
    }

    format_string = '<q'
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i64'])


    (
        message_body_offset,
        message_body_size,
        author_offset,
        author_size,
        time,
    ) = struct.unpack(format_string, binary_string)

    return 0;


def main():

    # use method 1 (sruct library) to print a binary blob of filler
    # data for the reaction dataclass
    binary_string = struct.pack('<qiiiiqqq', 1, 100, 102, 42, 10, 1, 2, 3) #bytes('a', 'utf-8'), bytes('b', 'utf-8'), bytes('c', 'utf-8'),  )

    (non, off1, s1, off2, s2, time) = struct.unpack('<qiiiiqqq', binary_string)
    
    print(non)
    print(s2)
    print(time)

    print(binary_string)

    #msg = operation_msg_unpack(binary_string)

    ##prompt users to populate example instance of class
    #variables = (vars(operation_msg)['__annotations__'])
    #var_names = list(variables.keys())  
    #var_types = list(variables.values())  

    #ex_operation_msg_input_list = []

    #for index, name in enumerate(var_names):
        #ex_operation_msg_input_list.append(
             #int(input("Enter value for " + name + ': ')) )

    #ex_operation_msg = operation_msg(
        #ex_operation_msg_input_list[0],
        #ex_operation_msg_input_list[1],
        #ex_operation_msg_input_list[2],
    #)

    #bin_string = operation_msg_pack(ex_operation_msg)

    #print(f'binary string: {bin_string}')

    #s = socket.socket()

    ## Define the port on which you want to connect
    #port = 60221 

    ## connect to the server on local computer
    #s.connect(('127.0.0.1', port))

    ## send the binary string that represents the packaged message
    #s.send(bin_string)
    ## close the connection
    #s.close()

    
    
if __name__ == '__main__':
    main()


