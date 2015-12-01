import os, time, datetime
from flask import request

from application import app

from model import pump, User, db
from func import condition

# Sign IN api
# @app.route('/check',  methods = ['POST'])
# def checkUser():
# 	user_data = request.json
# 	user = User.query.filter_by(email = user_data['email'].lower()).first()
# 	if user and user.check_password(userData['pwd']):
# 		return 'true'
# 	else:
# 		return 'false'

# Pump API
# Turn pump ON
@app.route('/pump/on',  methods = ['PUT', 'GET'])
def turnOn():
	if pump.working is False:
		# Pump turn ON logic
		# Should be with promise
	    pump.working = True
	    return condition.ON
	else:
		return condition.CHECK

# Turn pump off
@app.route('/pump/off',  methods = ['PUT', 'GET'])
def turnOff():
	if pump.working is True:
		# Pump turn OFF logic
		# Shoul be with promise
		pump.working = False
		return condition.OFF
	else:
		return condition.CHECK

# Get pump status
@app.route('/pump/status', methods = ['GET'])
def status():
	# Should be with promise
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