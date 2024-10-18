# Sprint 1

Name: Mikolaj Jakowski
Github ID: mikojakowski@gmail.com
Group name: notJSON

### What you planned to do

-   Create documentation instructing user or contributor how to add support for another language to the tool [Issue 14](https://github.com/utk-cs340-fall24/notJSON/issues/14)

-   Investigate potential binary packing methods for Python [Issue 55](https://github.com/utk-cs340-fall24/notJSON/issues/55)

-   Implement examples of binary message packing methods in python to showcase functionality [Issue 55](https://github.com/utk-cs340-fall24/notJSON/issues/55)

-   Create prototype client code in Python [Issue 8](https://github.com/utk-cs340-fall24/notJSON/issues/8)

-   Create Jinja template for creating prototype client and message packing code [Issue 8](https://github.com/utk-cs340-fall24/notJSON/issues/8)

### What you did not do

-   Create fully robust templating for creating python class based on message, not every type is supported

### What problems you encountered

-   Understanding Jinjja syntax and what the necessary functionality was
-   Figuring out reconcile C notion of memory and pointers with Python restriction of such concepts 
-   Communicating with group while I was out of the country


### Issues you worked on
-   Prototype Client Code Generation (Python) [Issue 8](https://github.com/utk-cs340-fall24/notJSON/issues/8)
-   Tutorial to Add New Languages [Issue 14](https://github.com/utk-cs340-fall24/notJSON/issues/14)
-   Find/Implement A Library for binary message packing in Python [Issue 55](https://github.com/utk-cs340-fall24/notJSON/issues/55)

### Files you worked on

- notJSON/documentation/new_langugage_tutorial.md [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/documentation/new_language_tutorial.md)
- notJSON/examples/binpack_test.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/examples/binpack_test.py)
- notJSON/examples/example_client.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/examples/example_client.py)
- notJSON/templates/python_client.jinja [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/templates/python_client.jinja)

### What you accomplished

One main task I worked on in this sprint was creating a tutorial for how to add new languages to the tool. This tutorial will aid users or contributers by clearly stating the steps necessary in order to add new language support. This means that it will be easier to add support and
expand the tool in the future. Another aspect that I focused on was investigating python tools and methods that would allow for the binary packing
and unpacking of messages. The two main tools that I outlined were the python struct library and cstruct library hosted on github. I also implemented code showcasing these methods and how they work.
After discovering several binary packing methods I implemented a prototype python client with basic networking functions and support for python
classes that would be able to hold the necessary fields outlined by a specific example of message xml. Then once this was accomplished I added a jinja templated that would generate this client automatically.
