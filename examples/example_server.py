import socket
import struct


def main(): 
    s = socket.socket()
    print("Socket succesfully created")

    port = 60221

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
    