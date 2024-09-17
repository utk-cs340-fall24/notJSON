#!/usr/bin/env python3

import xmltodict
from typing import Any

with open('example.schemafile', 'r') as file:
    content: str = file.read()
    dict = xmltodict.parse(content)
    print(dict)
