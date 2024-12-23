# notJSON
![Image](./logo.png)
A tool to generate encoding/decoding modules for transmitting binary messages.

## Authors
- Jackson Mowry jacksonmowry
- Mikolaj Jakowski MikJak75
- Jason West jasonwest

## Description
notJSON is a tool to build efficient and type safe clients/servers for performing data transfer and function calls between the two. The code is generated based on premade templates specific to each target language. Each schema is specified using an XML file.

## Setup
``` bash
python -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# Once you're done working...
deactivate
```

## Running
``` bash
$ python script.py example_schemas/final_demo.schemafile templates/c_server.jinja output/c_server.c
```

The above script should output a C server in the `output/` dir.
To generate the associated header use...

``` bash
$ python script.py example_schemas/final_demo.schemafile templates/c_server_h.jinja output/c_server.h
```

Then try python or JS using the following...

``` bash
$ python script.py example_schemas/final_demo.schemafile templates/python_client.jinja output/python_client.py
$ python script.py example_schemas/final_demo.schemafile templates/js_client.jinja output/js_client.js
```

## Contributing
Before making code changes decide which ticket you are working on. Then create a branch with your name, the project name, and the corresponding ticket number.

For example if my name is bob and I am working on issue number 3 I would create a branch as follows

``` bash
git checkout -b bob/notJSON-3
```

Then once you've made all the changes necessary for your ticket you can commit the changes.

``` bash
git status
git add -A
git commit -m "[notJSON-3] Removed lines from the sample xml file"
```

Then you can push your branch up to github.

``` bash
git push --set-upstream origin bob/notJSON-3
```

You will likely be prompted to create a PR, with a clickable URL, if not you can manually navigate to the github site to create a PR.

``` bash
(venv) jackson@jtop ~/notJSON (jackson/update-schemafile)> git push --set-upstream origin jackson/update-schemafileEnumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 8 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 510 bytes | 510.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
remote: 
remote: Create a pull request for 'jackson/update-schemafile' on GitHub by visiting:
remote:      https://github.com/utk-cs340-fall24/notJSON/pull/new/jackson/update-schemafile
remote: 
To github.com:utk-cs340-fall24/notJSON.git
 * [new branch]      jackson/update-schemafile -> jackson/update-schemafile
branch 'jackson/update-schemafile' set up to track 'origin/jackson/update-schemafile'.
```

From there create a helpful description of what changed in your pr, as well as linking to the issue in your PR.

## License 
[license link](LICENSE.txt)
