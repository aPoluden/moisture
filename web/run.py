#!flask/bin/python
from application import app

app.run(
		port = 5000,
		host = '0.0.0.0'
	)