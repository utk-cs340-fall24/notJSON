//Example client class
//const fetch = require('node-fetch');  // Make sure node-fetch is available
//const { pack, unpack } = require('../../output/optional');

class notJSONClient {
    constructor(base_url) {
        this.base_url = base_url;
    }

    encodeMessage(message_type, version, fields) {
	    console.log('Fields received:', fields);
	    const message = {
		    Greeting: fields.Greeting || '',
		    Name: fields.Name,
		    num: fields.num || 0
	    };
	   // const encoded_message = operation_msg.pack(message);
	   // return encoded_message;
		/*	
	    	let metadata = {
		        type: message_type,
		        version: version,
		        fields: fields
	      	};
		*/
	      	//converting metadata object into a JSON string then converting to binary (Buffer)
	    try {
		    //const encoded_message = operation_msg.pack(message);
		    const encoded_message = Buffer.from(JSON.stringify(message));
		    return encoded_message;	
	    } catch (error) {
		    console.error('Failed to encode message:', error);
		    throw new Error('Encoding error');
	    }
        }

        decodeMessage(encodedMessage) {
	      	//decoding the message from binary buffer
	    try{  	
		let decoded_message = JSON.parse(encodedMessage.toString());
	      	//const decoded_message = operation_msg.unpack(encodedMessage);
		return decoded_message;
	    } catch (error) {
		console.error('Failed to decode message:', encodedMessage.toString());
		throw new Error('Decoding error: Received unexpected format');
	    }
	}
		

        async sendMessage(message_type, version, fields) {
	          const encoded_message = this.encodeMessage(message_type, version, fields);
	          const response = await fetch(`${this.base_url}/api/sendMessage`, {
		            method: 'POST',
		            body: encoded_message,
		            headers: {
		                'Content-Type': 'application/octet-stream'
		            }
	          });
	          if (!response.ok) {
			const errorText = await response.text(); //getting error text for more details
			console.error('Server Error:', errorText);
		        throw new Error('Failed to send message');
	          }

	          const response_body = await response.arrayBuffer();
	          return this.decodeMessage(Buffer.from(response_body));
        }

        async receiveMessage() {
	      const response = await fetch(`${this.base_url}/api/receiveMessage`, {
		        method: 'GET'
	      });

	      const response_body = await response.arrayBuffer();
	      return this.decodeMessage(Buffer.from(response_body));
    }
}

const client = new notJSONClient('http://localhost:8080');

client.sendMessage(1, 1, { Greeting: 'Hello', Name: 'client' })
    .then(response => {
	      //console.log(`Response from server: Greeting - ${response.Greeting}, Name - ${response.Name}, Number - ${response.num}`);
    })

    .catch(error => {
	      console.error('Error sending message:', error);
    });

client.receiveMessage()
    .then(received => {
	    //:console.log(`Message from server: Greeting - ${received.Greeting}, Name - ${received.Name}, Number - ${received.num}`);
    })
    .catch(error => {
	    console.error('Error receiving message:', error);
    });
   
