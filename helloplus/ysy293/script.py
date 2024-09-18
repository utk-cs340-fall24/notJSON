#!/usr/bin/env python3

import xmltodict
from typing import Any

with open('example.schemafile', 'r') as file:
    content: str = file.read()
    parsed_xml: Any = xmltodict.parse(content)
    #dict = xmltodict.parse(content)
    #print(dict)

def extract_messages(parsed_xml):
    messages = parsed_xml['schema']['messages']['message']
    message_data = {}

    for message in messages:
        message_name = message['@name']  #extract message name

        field_names = []
        fields = message['field']

        #checking if fields is a list or a single field
        if isinstance(fields, list):
            for field in fields:
                field_names.append(field['#text']) 
        else:
            field_names.append(fields['#text'])  #for single field case

        message_data[message_name] = field_names

    return message_data

message_data = extract_messages(parsed_xml)
print(message_data)
