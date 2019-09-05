const express = require('express')
const app = express()
const port = 8082

app.get('/', (req, res) => res.send('Hello World!'))
app.use(express.static('../resource'))

app.listen(port, () => console.log(`Example app listening on port ${port}!`))
