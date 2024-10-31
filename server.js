const express = require('express');
const readline = require('readline');
const { operation_msg } = require('./output/optional');
const obj = express();
const port = 8080;	//given port number

obj.use(express.raw({ type: 'application/octet-stream' }));
//obj.use(express.json());

const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});

function promptUser(query) {
	return new Promise((resolve) => rl.question(query, resolve));
}

let initialGreeting = '';
let initialName = '';

obj.post('/api/sendMessage', (req, res) => {
    try {
	console.log('Raw request body:', req.body);
	const receivedData = operation_msg.unpack(req.body);
	//const receivedData = req.body;  // Directly use JSON for testing
	console.log('Unpacked message:', receivedData);
	
	const greeting = receivedData.Greeting || initialGreeting;
	const name = receivedData.Name || initialName;
	const num = receivedData.num || 'optional';
	
	console.log(`Server received: Greeting - ${greeting}, Name - ${name}, Number - ${num}`);

	// Respond to the client with a modified message
	//const responseMessage = optional.operation_msg.pack({
	const responseMessage = new operation_msg({
		Greeting: `${greeting} ${name}`,
		Name: 'Server',
		num: 400 // example response number
	}).pack();
	
	console.log('Sending response:', responseMessage);
	res.send(responseMessage);
    } catch (error) {
	console.error('Error processing message:', error);
        res.status(400).json({ error: 'Failed to process the message' }); // Return JSON error response
    }
});

obj.get('/api/receiveMessage', (req, res) => {
	try {
		const responseMessage = new operation_msg({
			Greeting: 'Hello from server',
			Name: 'Server',
			num: 100  // Example number
		}).pack();

		console.log('Sending message to client:', responseMessage);
		
		res.setHeader('Content-Type', 'application/octet-stream');
		res.send(responseMessage);
	} catch (error) {
		console.error('Error sending message:', error);
		res.status(400).json({ error: 'Failed to send the message' });
	}
});

//const { chat_message } = require('./output/optional');

//starting the server and listening on port 8080
async function startServer() {
	console.log(`Server running at http://localhost:${port}`);

	initialGreeting = await promptUser('Please input your message: Greeting (Optional): ');
	initialName = await promptUser('Name: ');
	 
	console.log(`Initial message: Greeting: ${initialGreeting}, Name: ${initialName}`);

	console.log('Writer: Sent data, waiting for client response...');
	rl.close();

	obj.listen(port, () => {
		console.log(`Server is listening on port ${port}`);
	});
}

startServer().catch(console.error);
