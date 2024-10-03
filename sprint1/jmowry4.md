# Sprint 1

Jackson Mowry, jmowry4, notJSON

### What you planned to do
(Give a short bulleted list of the items you planned to do for this sprint. Include the github issue number and link to the issue)
- Writing a custom message packing algorithm, #23, https://github.com/utk-cs340-fall24/notJSON/issues/23
- Detecting Message Circular Dependencies, #4, https://github.com/utk-cs340-fall24/notJSON/issues/4
- Define Binary Encoding, #4, https://github.com/utk-cs340-fall24/notJSON/issues/5

### What you did not do
(Give a short bulleted list of the items that you planned to do, but did not accomplish)
- Writing a custom message packing algorithm, #23, https://github.com/utk-cs340-fall24/notJSON/issues/23

### What problems you encountered
(List the problems you encountered)
- We lost a group member
- My group was radio silent for the entire first week of the sprint with no commits made
- In our reduced 4 person group, myself and Jason were the only ones that had meaningful contributions to the project
- I was blocked waiting on others to contribute until yesterday evening

### Issues you worked on
(List the specific github issues that you worked on with a link to the issue (ex: [#1](https://github.com/utk-cs340-fall22/ClassInfo/issues/1) Sample Issue)
- [#4] (https://github.com/utk-cs340-fall24/notJSON/issues/4) Detect Message Circular Dependencies
- [#27] (https://github.com/utk-cs340-fall24/notJSON/issues/27) Create a Javascript client skeleton
- [#22] (https://github.com/utk-cs340-fall24/notJSON/issues/22) Create Metadata Type
- [#21] (https://github.com/utk-cs340-fall24/notJSON/issues/21) Define Builtin Datatypes
- [#1] (https://github.com/utk-cs340-fall24/notJSON/issues/1) Define XML Schema
- [#24] (https://github.com/utk-cs340-fall24/notJSON/issues/24) Investigate Possible Way to Represent Variable Length Data
- [#20] (https://github.com/utk-cs340-fall24/notJSON/issues/20) Implement Basic C Struct Generation from Message Definitions
- [#6] (https://github.com/utk-cs340-fall24/notJSON/issues/6) Decied on a Templating Language/Tool
- [#5] (https://github.com/utk-cs340-fall24/notJSON/issues/5) Define Binary Encoding
- [#16] (https://github.com/utk-cs340-fall24/notJSON/issues/16) Define a Datatype to Represent 'fields' of Messages/Procedures/Returns

### Files you worked on
(Give a bulleted list of the files in your github repo that you worked on. Give the full pathname.)
- script.py
- schema_definition.xsd
- requirements.txt
- example.schemafile
- .gitignore
- README.md
- templates/c_server.jinja
- documentation/Untitled-2024-09-21-1025.png
- clients/javascript/echo_server.sh
- clients/javascript/index.html

### What you accomplished
(Give a description of the features you added or tasks you accomplished. Provide some detail here. This section will be a little longer than the bulleted lists above) 
- I chose a templating language that we will use to transform the schemafile into the target language for either the server or client
- I wrote an xml schema definition (XSD) file to ensure that our schemas conform the the expected shape of data
- I wrote the associated python dataclasses to give types/names to each field
- I did some research into how we can represent all of the possible combinations of fixed/variable length fields in the binary encoding
- I wrote up our scripts to enable the demo to go smoothly

