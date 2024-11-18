# Sprint 3

Name: Mikolaj Jakowski
Github ID: mikojakowski@gmail.com
Group name: notJSON

### What you planned to do

- Add client code that prompted user to populate all fields in a class created by the schemafile [Issue 83](https://github.com/utk-cs340-fall24/notJSON/issues/83)
- Add client code to pack an arbitary message [Issue 84](https://github.com/utk-cs340-fall24/notJSON/issues/84)
- Add arbitary message generation to jinja template [Issue 84](https://github.com/utk-cs340-fall24/notJSON/issues/84)
- Create networking capabilities for python client and send a binary message [Issue 84](https://github.com/utk-cs340-fall24/notJSON/issues/84)
- Implement code to receive binary message in the python server and print it [Issue 85](https://github.com/utk-cs340-fall24/notJSON/issues/85)


### What you did not do

-   Add fully functional Jinja template for python server [Issue 85](https://github.com/utk-cs340-fall24/notJSON/issues/85) 

### What problems you encountered

- Difficutly in figuring out how to network with python
- Hard to figure out how to prompt user given an arbitrary input
- Figuring out how to accept binary data input

### Issues you worked on

-   [Issue 83](https://github.com/utk-cs340-fall24/notJSON/issues/83)
-   [Issue 84](https://github.com/utk-cs340-fall24/notJSON/issues/84)
-   [Issue 85](https://github.com/utk-cs340-fall24/notJSON/issues/85)

### Files you worked on

- notJSON/examples/example_client.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/notJSON-84/examples/example_client.py)
- notJSON/templates/ptyhon_client.jinja [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/notJSON-84/templates/python_client.jinja)
- notJSON/examples/example_server.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/notJSON-84/examples/example_server.py)


### What you accomplished

In this sprint I worked on extending functionality for the python client for demoing and the python server code as well. For the python client this included adding functions that could pack a message and code for prompting the user to populate an instance of the class type they declared in the schema file. After this was implemented code was added to set up a connection with a server and send the binary data across the connection, the function that created the binary data was the packing function. Support for generation of this code was added to the python client jinja template. Additionally work was done on the python server. This included setting up a connection, listening for a message, and then printing that message, which represented the binary data being sent from the client.
