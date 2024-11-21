from dataclasses import dataclass
import ctypes
import requests
import struct
from typing import TypeAlias
import pprint
import socket
import os
import datetime
import time

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

def make_binary(hexcode: str) -> str:
    template = "{:0" + str(len(hexcode)*4) + "b}"
    return template.format((int(hexcode, 16)))


string : TypeAlias = str
char : TypeAlias = ctypes.c_uint8
i64 : TypeAlias = ctypes.c_int64
u64 : TypeAlias = ctypes.c_uint64
i32 : TypeAlias = ctypes.c_int32
u32 : TypeAlias = ctypes.c_uint32
i16 : TypeAlias = ctypes.c_int16
u16 : TypeAlias = ctypes.c_uint16
i8 : TypeAlias = ctypes.c_int8
u8 : TypeAlias = ctypes.c_uint8
size_t : TypeAlias = ctypes.c_size_t
#timestamp : TypeAlias = ctypes.c_uint64
timestamp : TypeAlias = ctypes.c_time_t

chat_message_packed_size = 27

class chat_message:
    message_body_offset : i32
    message_body_size : i32
    message_body : bytes
    author_offset : i32
    author_size : i32
    author : bytes
    time : timestamp

    field_mapping_dict = {}

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
        'u8' : 'B',
        'timestep' : 'Q',
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

def chat_message_pack(chat_message_var):
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
      'u8' : 'B',
      'timestamp' : 'Q',
  }

  #format_string = '<'
  format_string = '>'
  format_string += 'ii'
  format_string += 'ii'
  format_string += format_string_mapping['timestamp']
  #format_string += str(getattr(chat_message_var, 'message_body_size')) + format_string_mapping['char']
  #format_string += str(getattr(chat_message_var, 'author_size')) + format_string_mapping['char']
  #format_string += str(getattr(chat_message_var, 'message_body_size')) + 's' 
  #format_string += str(getattr(chat_message_var, 'author_size')) + 's'

  print(f'format_string is {format_string}')

  bin_string = struct.pack(format_string,
                            getattr(chat_message_var, 'message_body_offset'),
                            getattr(chat_message_var, 'message_body_size'),
                            getattr(chat_message_var, 'author_offset'),
                            getattr(chat_message_var, 'author_size'),
                            getattr(chat_message_var, 'time'),
                            #getattr(chat_message_var, 'message_body'),
                            #getattr(chat_message_var, 'author'),
                          )

  #bin_string += bytes((8 - getattr(chat_message_var, 'message_body_size')) % 8)
  bin_string += bytes(3)
  bin_string += getattr(chat_message_var, 'message_body')
  #bin_string += bytes((8 - getattr(chat_message_var, 'author_size')) % 8)
  bin_string += getattr(chat_message_var, 'author')

  return bin_string

def main():

    # use method 1 (sruct library) to print a binary blob of filler
    # data for the reaction dataclass
    #bin_string = make_binary("0000001b000000050000002000000007000000aa413c670000000068656c6c6f4d696b6f6c616a")
    bin_string = bytes.fromhex("0000001b000000050000002000000007000000aa413c670000000068656c6c6f4d696b6f6c616a")
    
    #print(bin_string)

    binary_string = struct.pack('<qiiiiqqqq', 1, 100, 102, 42, 10, 1, 2, 3, 1) #bytes('a', 'utf-8'), bytes('b', 'utf-8'), bytes('c', 'utf-8'),  )

    #(non, off1, s1, off2, s2, time,) = struct.unpack_from('<qiiiiqqq', binary_string, offset=0)
    a = struct.unpack_from('<qiiiiqqq', binary_string, offset=0)
    #a = struct.unpack('<qiiiiqqq', binary_string)
    non = a[0]
    s2 = a[4]
    #print(non)
    #print(s2)
    #print(time)

    #print(binary_string)
    message_body_string = input()
    message_body_size = len(message_body_string)
    message_body_offset = chat_message_packed_size
    message_body = bytes(message_body_string, 'utf8')

    author_string = os.getenv('USER')
    author_size = len(author_string)
    author_offset = message_body_offset + message_body_size
    author = bytes(author_string, 'utf8')
    print(author)

    timstmp = int(datetime.datetime.utcnow().timestamp())
    #timstmp = 10
    timstmp = int(time.time())

    #cm = chat_message()
    #cm.message_body = b'hello'
    #cm.author = b'Mikolaj'
    #cm.message_body_offset = 27
    #cm.message_body_size = 5
    #cm.author_offset = 32
    #cm.author_size = 7
    #cm.time = 10

    cm = chat_message()
    cm.message_body = message_body
    cm.author = author
    cm.message_body_offset = message_body_offset
    cm.message_body_size = message_body_size
    cm.author_offset = author_offset
    cm.author_size = author_size
    #cm.time = time.time()
    cm.time = timstmp
    cm.time = 4

    #print(type(cm.author))

    bin_string = chat_message_pack(cm)

    print(bin_string)


    s = socket.socket()

    # Define the port on which you want to connect
    port = 8080

    # connect to the server on local computer
    s.connect(('127.0.0.1', port))

    # send the binary string that represents the packaged message
    s.send(bin_string)
    # close the connection
    s.close()

    
    
if __name__ == '__main__':
    main()


