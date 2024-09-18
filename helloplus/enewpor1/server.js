const express = require('express');
const app = express();
const port = 8080;

app.get('/api/hello', (req, res) => {
  res.send('hello world');
});

app.listen(port, () => {
  console.log(`Server is listening on port ${port}`);
});