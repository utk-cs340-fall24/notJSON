# Sprint 4

Name: Mikolaj Jakowski
Github ID: mikojakowski@gmail.com
Group name: notJSON

### What you planned to do

- Add variable message length unpacking for python client [Issue 104](https://github.com/utk-cs340-fall24/notJSON/issues/104)
- Add variable message length unpacking for python server[Issue 105](https://github.com/utk-cs340-fall24/notJSON/issues/105) 
- Create Jinja template that can generate python client [Issue 106](https://github.com/utk-cs340-fall24/notJSON/issues/106)
- Create fully polished demo for presentation [Issue 107](https://github.com/utk-cs340-fall24/notJSON/issues/107)


### What you did not do

-  Have completely polished demo for presentation [Issue 107](https://github.com/utk-cs340-fall24/notJSON/issues/107) 

### What problems you encountered

- Confusion in certain aspects of variable length unpacking algorithm
- Determing what networking to tool use to communicate between cross platform apps
- Figuring out how to switch between variable and unvariable length in templating algorithm

### Issues you worked on

- [Issue 104](https://github.com/utk-cs340-fall24/notJSON/issues/104)
- [Issue 105](https://github.com/utk-cs340-fall24/notJSON/issues/105) 
- [Issue 106](https://github.com/utk-cs340-fall24/notJSON/issues/106)  
- [Issue 107](https://github.com/utk-cs340-fall24/notJSON/issues/107) 

### Files you worked on

- notJSON/examples/demo_client.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/Sprint4/examples/demo_client.py)
- notJSON/examples/example_server.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/Sprint4/examples/example_server.py)
- notJSON/templates/python_server.jinja [Link](https://github.com/utk-cs340-fall24/notJSON/blob/miko/Sprint4/templates/python_server.jinja)


### What you accomplished

In this sprint I worked on adding support for variable length data unpacking in both the python client and server. This included updates to the previous algorithm I was using, since in this case it had to be able to accept the different format and break down the binary data in a different way. Additionally I worked on adding a jinja template for the python server which would allow for automatic generation of the python server using the script. These tasks were in service of creating a fully polished demo client for the presentation. This demo client will be able to connect to a server written/generated in a different language and unpack/pack a message.
