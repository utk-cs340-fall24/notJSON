const express = require('express');
const app = express();
const port = 8080;	//given port number

app.use(express.json());

//tool to parse binary data
app.use(express.raw({ type: 'application/octet-stream' }));

app.post('/api/sendMessage', (req, res) => {
	const receivedMessage = req.body.toString(); // Parse the buffer into a string
	console.log('Received encoded message:', receivedMessage);
	// Simulate sending back a response message
	const responseMessage = JSON.stringify({
        	type: 1,
		version: 1,
		fields: { responseField1: 'responseValue1' }
	});

	res.set('Content-Type', 'application/octet-stream');
	res.send(Buffer.from(responseMessage));

	let encodedMessage = [];
	req.on('data', chunk => {
		encodedMessage.push(chunk);
	}).on('end', () => {
		const fullMessage = Buffer.concat(encodedMessage);
		let decodedMessage = JSON.parse(fullMessage.toString());

		console.log('Received message:', decodedMessage);
		// Send back a response to the client
		res.status(200).send(fullMessage);  // Echo back the received message
	});
});

app.get('/api/receiveMessage', (req, res) => {
	const message = JSON.stringify({
		type: 1,
		version: 1,
		fields: { field1: 'value1', field2: 'value2' }
	});

	res.set('Content-Type', 'application/octet-stream');
	res.send(Buffer.from(message));
	

	const mockMessage = {
		type: 1,
		version: 1,
		fields: { field1: 'mockValue1', field2: 'mockValue2' }
	};

	// Encode and send back the message
	let encodedMessage = Buffer.from(JSON.stringify(mockMessage));
	res.status(200).send(encodedMessage);
});


//defining the /api/hello route
app.get('/api/hello', (req, res) => {
	res.send('hello world');
});


//starting the server and listening on port 8080
app.listen(port, () => {
	//using this to print the URL we can access the server with
	console.log(`Server is running on http://localhost:${port}`);
});
