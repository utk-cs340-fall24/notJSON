# The purpose of this file is to create a python server
# that will be able to receive an example binary message
# sent from the python clinet and then do something with
# that message to show that it is working


# Socket is used for networking
import socket

def main(): 
    #create a socket
    s = socket.socket()
    print("Socket succesfully created")

    #select a random port
    port = 60221

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
    