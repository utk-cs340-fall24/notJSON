#!/usr/bin/env sh

source venv/bin/activate

head -n 25 example_schemas/example.schemafile | bat
python script.py example_schemas/example.schemafile templates/c_server.jinja output/basic.c
bat output/basic.c
