const express = require('express');
const obj = express();
const port = 8080;	//given port number

//defining the /api/hello route
obj.get('/api/hello', (req, res) => {
	res.send('hello world');
});

//starting the server and listening on port 8080
obj.listen(port, () => {
	//using this to print the URL we can access the server with
	console.log(`Server is running on http://localhost:${port}`);
});
