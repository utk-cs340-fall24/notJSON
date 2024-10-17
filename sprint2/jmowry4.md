# Sprint 1

Jackson Mowry, jmowry4, notJSON

### What you planned to do
(Give a short bulleted list of the items you planned to do for this sprint. Include the github issue number and link to the issue)
- https://github.com/utk-cs340-fall24/notJSON/issues/10  Implement Interprocess Communication #10 
- https://github.com/utk-cs340-fall24/notJSON/issues/23  Write custom message packing algorithm #23 
- https://github.com/utk-cs340-fall24/notJSON/issues/80  Add support for optional fields in messages #80 

### What you did not do
(Give a short bulleted list of the items that you planned to do, but did not accomplish)
- N/A

### What problems you encountered
(List the problems you encountered)
- This time around the only issue that I ran into was implementing communication within the same machine using different processes. For some reason I was running into a kernel panic when attempting to open a FIFO. Turns out I had a bad sector on my disk, and switching my OS to an NVMe solved the issue.

### Issues you worked on
(List the specific github issues that you worked on with a link to the issue (ex: [#1](https://github.com/utk-cs340-fall22/ClassInfo/issues/1) Sample Issue)
- [#10] https://github.com/utk-cs340-fall24/notJSON/issues/10  Implement Interprocess Communication #10 
- [#23] https://github.com/utk-cs340-fall24/notJSON/issues/23  Write custom message packing algorithm #23 
- [#80] https://github.com/utk-cs340-fall24/notJSON/issues/80  Add support for optional fields in messages #80 

### Files you worked on
(Give a bulleted list of the files in your github repo that you worked on. Give the full pathname.)
- demo_scripts/c_notJSON/client.c
- demo_scripts/c_notJSON/server.c
- templates/c_server.jinja
- templates/c_server_h.jinja
- example_schemas/optional.schemafile
- example_schemas/no_variable_length.schemafile
- example_schemas/variable_length.schemafile
- templates/c_client.jinja
- templates/c_client_h.jinja
- script.py



### What you accomplished
(Give a description of the features you added or tasks you accomplished. Provide some detail here. This section will be a little longer than the bulleted lists above) 
- This was by far a more productive sprint for me. I made huge progress in encoding messages, with nearly all of our "final" features implemented.
- I was also able to write the decoder for objects, which supports both optional and variable length fields, including a combination of the two.
- I create a custom struct packing algorithm that reorders struct fields to both save space, and to ensure that all memory accesses are perfectly aligned to improve performance.
- Lastly I created a demo that sends a message between a client and a server on the same machine through a FIFO.


