from application import app
from flask import make_response

@app.route('/')
def index(): 
	return make_response(open('static/index.html').read())