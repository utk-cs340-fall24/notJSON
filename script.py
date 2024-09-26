#!/usr/bin/env python3

import xmltodict
import 
from typing import Any, Dict, List

@dataclass
class Message:
    name: str
    base_size: int
    fields: list[Field]

#parsing the xml content
with open('example.schemafile', 'r') as file:
    content: str = file.read()
    parsed_xml: Any = xmltodict.parse(content)
    #dict = xmltodict.parse(content)
    #print(dict)

#extract messages
def extract_messages(parsed_xml):
    messages = parsed_xml['schema']['messages']['message']
    message_data = {};
    
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
        print("field_names:\n") 
        print(field_names)
        print("\n\n")

    return message_data

#extract procedures
def extract_procedures(parsed_xml: Any) -> Dict[str, Dict[str, List[str]]]:
    procedures = parsed_xml['schema']['procedures']['procedure']
    procedure_data = {}

    #loop through the procedures provided in the xml code
    for procedure in procedures:
        procedure_name = procedure['@name'] #extract procedure name

        procedure_info = {'parameters': [], 'returns': []}

        #extract parameters
        parameters = procedure['parameters']['field']
        if isinstance(parameters, list):
            for param in parameters:
                procedure_info['parameters'].append(param['#text'])
        #case for a single parameter
        else: 
            procedure_info['parameters'].append(parameters['#text'])

        #now extract the return fields
        returns = procedure['returns']['field']
        if isinstance(returns, list):
            for ret in returns:
                procedure_info['returns'].append(ret['#text'])
        else:
            procedure_info['returns'].append(returns['#text'])

        procedure_data[procedure_name] = procedure_info
    
    return procedure_data

#examples of usage:
message_data = extract_messages(parsed_xml)
procedure_data = extract_procedures(parsed_xml)

print("Messages:\n")
print(message_data)

print("\nProcedures:\n")
print(procedure_data)
        
