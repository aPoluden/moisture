import os, time, datetime
from application import app
from model import pump, condition, User, db
from flask import request

# Sign IN api
@app.route('/check',  methods = ['POST'])
def checkUser():
	user_data = request.json
	user = User.query.filter_by(email = user_data['email'].lower()).first()
	if user and user.check_password(userData['pwd']):
		return 'true'
	else:
		return 'false'

def getTimeStamp():
	ts = time.time()
	return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')

# Pump API 
@app.route('/pump/on',  methods = ['PUT', 'GET'])
def turnOn():
	if pump.working is False:
		# Pump turn on logic
	    pump.working = True
	    return condition.ON
	else:
		return condition.CHECK

@app.route('/pump/off',  methods = ['PUT', 'GET'])
def turnOff():
	if pump.working is True:
		# Pump turn off logic
		pump.working = False
		return condition.OFF
	else:
		return condition.CHECK

@app.route('/pump/status', methods = ['GET'])
def status():
	return pump.status()

# Add new user
# @app.route('/submit',  methods = ['POST'])
# def signIn():
# 	newuser = User('firstname', 'lastname', 'email', 'pwd', 1)
# 	db.session.add(newuser)
# 	db.session.commit()

# Data API without SQLAlchemy
# @app.route('/data/<int:value>',  methods = ['POST', 'GET'])
# def receiveData(value):
#     ts = getTimeStamp()
#     db.insertValues(ts, value)
#     return db.dbStatus()