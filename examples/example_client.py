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
import pprint

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


typedict = {
    'i32' : ctypes.c_int32,
    'string' : ctypes.c_uint64,
}


@dataclass
class operation_msg:
    operand_one : i32
    operand_two : i32
    operation : char

def operation_msg_unpack (binary_string) -> operation_msg:
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

    format_string = '<'
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['char'])

    (
        operand_one,
        operand_two,
        operation,
    ) = struct.unpack(format_string, binary_string)

    object = operation_msg(
        operand_one,
        operand_two,
        operation,
    )

    return object
    
def operation_msg_pack(operation_msg_var):
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

    format_string = '<'
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['i32'])
    format_string += (format_string_mapping['char'])

    bin_string = struct.pack(format_string, getattr(operation_msg_var, 'operand_one'),
                             getattr(operation_msg_var, 'operand_two'),
                             getattr(operation_msg_var, 'operation'),
                             )

    return bin_string

def main():
    print("hello")

    #make example http get request
    x = requests.get('https://google.com')
    print('Google get request status code: ')
    print(x.status_code)


    # use method 1 (sruct library) to print a binary blob of filler
    # data for the reaction dataclass
    binary_string = struct.pack('<iic', 1, 1023, bytes('a', 'utf-8'))
    msg = operation_msg_unpack(binary_string)

    #prompt users to populate example instance of class
    variables = (vars(operation_msg)['__annotations__'])
    var_names = list(variables.keys())  
    var_types = list(variables.values())  

    ex_operation_msg_input_list = []

    for index, name in enumerate(var_names):
        ex_operation_msg_input_list.append(
             int(input("Enter value for " + name + ': ')) )

    ex_operation_msg = operation_msg(
        ex_operation_msg_input_list[0],
        ex_operation_msg_input_list[1],
        ex_operation_msg_input_list[2],
    )

    bin_string = operation_msg_pack(ex_operation_msg)

    print(f'binary string: {bin_string}')
    
if __name__ == '__main__':
    main()
