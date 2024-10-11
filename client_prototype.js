//Example client class

class notJSONClient {
    constructor(base_url) {
	this.base_url = base_url;
    }

    encodeMessage(message_type, version, fields) {
	//lowkey random logic for now 
	let metadata = {
		type: message_type,
		version: version,
		fields: fields
	};

	//converting metadata object into a JSON string then converting to binary (Buffer)
	let encoded_message = Buffer.from(JSON.stringify(metadata));
	return encoded_message;
    }

    decodeMessage(encodedMessage) {
	// Simulate decoding the message from binary buffer
	let decoded_message = JSON.parse(encodedMessage.toString());
	return decoded_message;
    }

    async sendMessage(message_type, version, fields) {
	let encoded_message = this.encodeMessage(message_type, version, fields);
	let response = await fetch(`${this.base_url}/api/sendMessage`, {
		method: 'POST',
		body: encoded_message,
		headers: {
			'Content-Type': 'application/octet-stream'
		}
	});
	if (!response.ok) {
		throw new Error('Failed to send message');
	}

	let response_body = await response.arrayBuffer();
	let decoded_response = this.decodeMessage(Buffer.from(response_body));
	return decoded_response;
    }

    async recieveMessage() {
	let response = await fetch(`${this.base_url}/api/receiveMessage`, {
		method: 'GET'
	});

	let response_body = await response.arrayBuffer();
	let decoded_message = this.decodeMessage(Buffer.from(response_body));
	return decoded_message;
    }
}

const client = new notJSONClient('http://localhost:8080');

client.sendMessage(1, 1, { field1: 'f1', field2: 'f2' })
    .then(response => {
	    console.log('Received response from server:', response);
    })

    .catch(error => {
	    console.error('Error sending message:', error);
    });
