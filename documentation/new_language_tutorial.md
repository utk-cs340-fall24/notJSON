# New Language Tutorial

The purpose of this documentation is to create a guide so
that outlines the steps necessary in order to add support
for new langauges to the notJSON tool. The notJSON tool
is intended to simplify the process of creating efficient
client-server applications. The tool accomplishes this by 
creating templated applications that employd data structures
that have particular c like structure layouts. Based on the
assumptions about the memory layout of the data structures
notJSON is able to efficient send, receieve, pack and unpack
binaries of data corresponding to predefinded message. The tool
is not able to anticipate how to create such a data structure
in every programming language, thus if it is desire that the 
tool is extended to another programming language the
corresponding data structures need to be implemented by someone
else. 

This is where one who wishes to add a new language to the tool
will need to create their own file.

For example consider the xml schema file: 

```
<?xml version="1.0" encoding="UTF-8"?>
<schema version="1.0.0">
  <messages>
    <message name="reaction">
      <fields>
        <field type="string" required="true">emoji</field>
        <field type="i32" default="0">count</field>
      </fields>
    </message>
    <message name="chat_message">
      <fields>
        <field type="string" required="true">author</field>
        <field type="timestamp" required="true">message_sent</field>
        <field type="i32">likes</field>
        <field type="string" required="true">body</field>
        <field type="reaction[]">reactions</field>
      </fields>
    </message>
  </messages>
  <procedures>
    <procedure name="send_message">
      <description>
        Submits a new chat message along with the users authentication token.
      </description>
      <parameters>
        <field type="chat_message" required="true">message</field>
        <field type="string" required="true">auth_token</field>
      </parameters>
      <returns>
        <field type="boolean">success</field>
      </returns>
    </procedure>
    <procedure name="get_messages">
      <description>
        Get the latest `Count` messages from the server, requires a users
        authentication token.
        `Count` defaults to 10 messages.
      </description>
      <parameters>
        <field type="i32">count</field>
        <field type="string" required="true">auth_token</field>
      </parameters>
      <returns>
        <field type="chat_message[]">messages</field>
      </returns>
    </procedure>
  </procedures>
</schema>
```


This xml file specifies a specific kind of message. This
message has a specific layout. In C the message would
resemble the following struct:

```
typedef struct reaction {
      string emoji;
      i32 count;
} reaction;

typedef struct chat_message {
      string author;
      timestamp message_sent;
      i32 likes;
      string body;
      reaction* reactions;
      size_t reactions_count;
} chat_message;
```


In order to generate bolerplate python code that would 
contain a data structure that is compatible with this
c struct the following jinja code could be used:

```
typedict = {
    'i32' : ctypes.c_int32,
    'string' : ctypes.c_uint64,
}

{% for message in messages -%}
@dataclass
class {{ message.name }} :
  {% for field in message.fields %}
    {% if field.array %}
    list : typedict[ '{{ field.type_field }}' ]
    {{ field.name}} : ctypes.c_size_t 
    {% else %}
    {{ field.name }} : typedict[ '{{ field.type_field }}' ] 
    {% endif %}
  {% endfor %}

{% endfor %}
```

This jinja template code would result in this python file :

```
typedict = {
    'i32' : ctypes.c_int32,
    'string' : ctypes.c_uint64,
}

@dataclass
class reaction :
    emoji : typedict[ 'string' ] 
    count : typedict[ 'i32' ] 

@dataclass
class chat_message :
    author : typedict[ 'string' ] 
    message_sent : typedict[ 'timestamp' ] 
    likes : typedict[ 'i32' ] 
    body : typedict[ 'string' ] 
    list : typedict[ 'reaction' ]
    reactions : ctypes.c_size_t 

```

In order to implement another programming language
than python the user would need to determine what data 
structure would be fitting, then write a jinja template
that could create this boilerplate instance of the 
data structure based on a random type of message