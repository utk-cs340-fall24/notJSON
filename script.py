#!/usr/bin/env python3

import xmltodict
import argparse
from typing import Any, Dict, List
from jinja2 import Environment, FileSystemLoader
from typing import Any
from dataclasses import dataclass
from enum import Enum

# Creates a mapping of typename to type size
class Primitive(Enum):
    NJ_STRING = 8
    NJ_I64 = 8
    NJ_U64 = 8
    NJ_I32 = 4
    NJ_U32 = 4
    NJ_I16 = 2
    NJ_U16 = 2
    NJ_I8 = 1
    NJ_U8 = 1
    NJ_CHAR = 1
    NJ_DOUBLE = 8
    NJ_FLOAT = 4
    NJ_TIMESTAMP = 8
    NJ_BOOLEAN = 1

@dataclass
class Field:
    required: bool
    default_val: str
    type_field: str
    name: str

@dataclass
class Message:
    name: str
    base_size: int
    fields: list[Field]

@dataclass
class Procedure:
    name: str
    description: str
    parameters: list[Field]
    return_values: list[Field]

#extract messages
def extract_messages(parsed_xml) -> List[Message]:
    messages = parsed_xml['schema']['messages']['message']
    message_data = []

    for message in messages:
        message_name = message['@name']  #extract message name

        field_names = []
        fields = message['fields']['field']
        
        #checking if fields is a list or a single field
        if isinstance(fields, list):
            for field in fields:
                field_object = Field(
                    required = field.get('@required', 'false') == 'true',
                    default_val = field.get('@default', ''),
                    type_field = field['@type'],
                    name = field['#text']
                )
                field_names.append(field_object)

        #running for a single field case so for loop isn't executed when unecessary
        else:
            field_object = Field(
                required = fields.get('@required', 'false') == 'true',
                default_val = fields.get('@default', ''),
                type_field = fields['@type'],
                name = fields['#text']
            )
            #do something similar to this, grap type and default value instead
            field_names.append(field_object)
        
        message_data.append(Message(name = message_name, base_size = 0, fields = field_names))

    return message_data

#extract procedures
def extract_procedures(parsed_xml: Any) -> List[Procedure]:
    procedures = parsed_xml['schema']['procedures']['procedure']
    procedure_data = []

    #loop through the procedures provided in the xml code
    for procedure in procedures:
        procedure_name = procedure['@name'] #extract procedure name
        description = procedure['description']

        #procedure_info = {'parameters': [], 'returns': []}

        #extract parameters
        parameters = procedure['parameters']['field']
        parameter_data = []
        
        if isinstance(parameters, list):
            for parameter in parameters:
                param_object = Field(
                    required = parameter.get('@required', 'false') == 'true',
                    default_val = parameter.get('@default', ''),
                    type_field = parameter['@type'],
                    name = parameter['#text']
                )

                parameter_data.append(param_object)
        #case for a single parameter
        else: 
            param_object = Field(
                required = parameters.get('@required', 'false') == 'true',
                default_val = parameters.get('@default', ''),
                type_field = parameters['@type'],
                name = parameters['#text']
            )

            parameter_data.append(param_object)

        #now extract the return fields
        returns = procedure['returns']['field']
        return_data = []

        if isinstance(returns, list):
            for ret in returns:
                ret_object = Field(
                    required = ret.get('@required', 'false') == 'true',
                    default_val = ret.get('@default', ''),
                    type_field = ret['@type'],
                    name = ret['#text']
                )

                return_data.append(ret_object)
        else:
            ret_object = Field(
                required = returns.get('@required', 'false') == 'true',
                default_val = returns.get('@default', ''),
                type_field = returns['@type'],
                name = returns['#text']
            )

            return_data.append(ret_object)

        #updating values in the Procedure class
        procedure_data.append(Procedure(name = procedure_name, description = description, parameters = parameter_data, return_values = return_data))
    
    return procedure_data

def read_file(filename: str):
    with open(filename, 'r') as file:
        content: str = file.read()
    return content

def write_file(filename: str, contents: str):
    with open(filename, 'w') as file:
        file.write(contents)

def main(schemafile: str, template_file: str, output_file: str):
    #parsing the xml content
    content: str = read_file(schemafile)
    parsed_xml: Any = xmltodict.parse(content)

    environment = Environment(loader=FileSystemLoader("."))
    environment.trim_blocks = True
    environment.lstrip_blocks = True
    environment.keep_trailing_newline = True

    message_data = extract_messages(parsed_xml);
    procedure_data = extract_procedures(parsed_xml)

    template = environment.get_template(template_file)
    context = {
        "messages": message_data
    }

    output: str = template.render(context)
    write_file(output_file, output)



if __name__ == '__main__':
    parser: argparse.ArgumentParser = argparse.ArgumentParser(
        prog='notJSON',
        description='A CLI Tool to generate clients/servers for notJSON schemas',
    )

    parser.add_argument('schemafile', help='Your input schemafile, should end in `.schemafile`')
    parser.add_argument('template', help='Your output Jinja Template, should end in `.jinja`')
    parser.add_argument('outputfile', help='The destination file notJSON should write to, file extension should match generated source file')

    args = parser.parse_args()

    main(args.schemafile, args.template, args.outputfile)
