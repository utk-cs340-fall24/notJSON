#!/usr/bin/env python3

import xmltodict
from jinja2 import Environment, FileSystemLoader
from typing import Any
from dataclasses import dataclass

@dataclass
class Field:
    required: bool
    default_val: str
    type_field: str
    name: str

with open('example.schemafile', 'r') as file:
    content: str = file.read()
    dict = xmltodict.parse(content)

    messages = dict['schema']['messages']

    environment = Environment(loader=FileSystemLoader("templates/"))
    environment.trim_blocks = True
    environment.lstrip_blocks = True
    environment.keep_trailing_newline = True

    template = environment.get_template("c_server.jinja")
    context = {
        "messages": messages["message"]
    }

    print(template.render(context))
