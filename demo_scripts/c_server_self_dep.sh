#!/usr/bin/env sh

source venv/bin/activate

head -n 25 example_schemas/self_dep.schemafile | bat
python script.py example_schemas/self_dep.schemafile templates/c_server.jinja output/basic.c
