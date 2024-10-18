# Sprint n (1, 2, 3, or 4)

Name: Mikolaj Jakowski
Github ID: mikojakowski@gmail.com
Group name: notJSON

### What you planned to do

-   Add documentation for how to use Conda [Issue 65](https://github.com/utk-cs340-fall24/notJSON/issues/69)
-   Add yml environment file [Issue 65](https://github.com/utk-cs340-fall24/notJSON/issues/69)
-   Add template for creating class that can handle any type of expected data in python [Issue 68](https://github.com/utk-cs340-fall24/notJSON/issues/68)
-   Add template for creating unpacking function for any fixed length message in python [Issue 69](https://github.com/utk-cs340-fall24/notJSON/issues/69)
-   Add code to test and demo templated unpacking function [Issue 69](https://github.com/utk-cs340-fall24/notJSON/issues/69)

### What you did not do

-   Add code for templateing unpacking funciton for variable length message in python [Issue 69](https://github.com/utk-cs340-fall24/notJSON/issues/69)

### What problems you encountered

-   Figuring out way to dynamically render strings in jinja template
-   Understanding exactly how unpacking algorithm should work
-   Brainstorming how to structure data classes and what is necessary in each class
-   Figuring out how to unpacking variable length message

### Issues you worked on

-   [Issue 65](https://github.com/utk-cs340-fall24/notJSON/issues/69)
-   [Issue 68](https://github.com/utk-cs340-fall24/notJSON/issues/68)
-   [Issue 69](https://github.com/utk-cs340-fall24/notJSON/issues/69)

### Files you worked on

- notJSON/documentation/How_Conda_Works.md [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/documentation/How_Conda_Works.md)
- notJSON/notJSON_environment.yml [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/notJSON_environment.yml)
- notJSON/examples/example_client.py [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/examples/example_client.py)
- notJSON/templates/python_client.jinja [Link](https://github.com/utk-cs340-fall24/notJSON/blob/main/templates/python_client.jinja)



### What you accomplished

In this sprint I worked in two main areas. The first was conda support. I added documentation and an environment file that would allow for a user to figure out how to use conda, as well as how to reproduce the environment in the yml file. This is the environment that will be used for the project. The other main area I worked on was creating the necessary python functions and classes in order to process the messages, and working on the template to create this. This included coming up with a python class and unpacking function that would work and also be able to be templated, then implementing the jinja template for these classes and functions.
