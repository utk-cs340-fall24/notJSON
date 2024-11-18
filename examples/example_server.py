# The purpose of this file is to create a python server
# that will be able to receive an example binary message
# sent from the python clinet and then do something with
# that message to show that it is working
import struct
from typing import TypeAlias
import ctypes

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
        'u8' : 'B',
        'timestamp' : i64,
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

    return 0

# Socket is used for networking
import socket

def main(): 
    #create a socket
    s = socket.socket()
    print("Socket succesfully created")

    #select a random port
    #port = 60221
    port = 8080

    # take any incoming connections from the localhost
    # in this demo we are only looking at connection between 
    # local process
    s.bind(('localhost', port))
    s.listen(5)

    while True:
        # Establish connection with client.
        c, addr = s.accept()
        print ('Got connection from', addr )

        # receive message from client
        bin_string = c.recv(1024)

        print(bin_string)

        # Close the connection with the client
        c.close()


if __name__ == '__main__':
    main()
    