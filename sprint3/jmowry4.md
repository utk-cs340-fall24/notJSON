# Sprint 3

Jackson Mowry, jmowry4, notJSON

### What you planned to do
(Give a short bulleted list of the items you planned to do for this sprint. Include the github issue number and link to the issue)
- https://github.com/utk-cs340-fall24/notJSON/issues/92 Implement Procedure Code Generation (C Server) #92
- https://github.com/utk-cs340-fall24/notJSON/issues/93 Implement Procedure Generation (C Client) #93
- https://github.com/utk-cs340-fall24/notJSON/issues/94 Write Basic Reusable C Socket Client Functions #94

### What you did not do
(Give a short bulleted list of the items that you planned to do, but did not accomplish)
- N/A

### What problems you encountered
(List the problems you encountered)
- I ran into an issue implementing the ability to embed messages with variable length fields within each other. This caused me to have to pivot what I was going to work on about halfway through our sprint. Luckily we're aboe to work around this within our current framework, and will still be able to have a good demo.

### Issues you worked on
(List the specific github issues that you worked on with a link to the issue (ex: [#1](https://github.com/utk-cs340-fall22/ClassInfo/issues/1) Sample Issue)
- https://github.com/utk-cs340-fall24/notJSON/issues/92 Implement Procedure Code Generation (C Server) #92
- https://github.com/utk-cs340-fall24/notJSON/issues/93 Implement Procedure Generation (C Client) #93
- https://github.com/utk-cs340-fall24/notJSON/issues/94 Write Basic Reusable C Socket Client Functions #94

### Files you worked on
(Give a bulleted list of the files in your github repo that you worked on. Give the full pathname.)
- templates/c_client.jinja
- example_schemas/optional.schemafile
- script.py
- demo_scripts/sprint3/server.c
- demo_scripts/sprint3/embedded.h
- demo_scripts/sprint3/optional.c
- demo_scripts/sprint3/client.c
- templates/c_server.jinja
- demo_scripts/sprint3optional.h
- example_schemafiles/embedded.schemafile
- example_schemafiles/arithmetic.schemafile
- templates/c_server_h.jinja
- output/embedded_client.h
- tepmlates/c_client_h.jinja



### What you accomplished
(Give a description of the features you added or tasks you accomplished. Provide some detail here. This section will be a little longer than the bulleted lists above) 
- This week I was finishing implementing the last few pieces of our tool to make a good demo. We now have procedures fully implemented for both the server and the client, with networked communication between the two. 
- Procedures on the server side are presented as prototypes with the body of the procedure to be written by the user. This allows the user to write as little or as much code as they would like, without having to worry about the network side of things.
- Procedure generation code on the client side is even simpler. All the user has to do is pass a struct of the correct type, call the function, and wait on the result to be returned. Full type safety without having to worry about the network layer.

