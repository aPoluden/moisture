import os, time, datetime, db
from application import app
from model import pump

@app.route('/data/<int:value>',  methods = ['POST', 'GET'])
def receiveData(value):
    ts = getTimeStamp()
    db.insertValues(ts, value)
    return db.dbStatus()

def getTimeStamp():
	ts = time.time()
	return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')

@app.route('/pump/on',  methods = ['PUT', 'GET'])
def turnOn():
	if pump.working is False:
		# Pump turn on logic
	    pump.working = True
	    return "Pump turned on"
	else:
		return "Check pump status"

@app.route('/pump/off',  methods = ['PUT', 'GET'])
def turnOff():
	if pump.working is True:
		# Pump turn off logic
		pump.working = False
		return "Pump turned off"
	else:
		return "Check pump status"

@app.route('/pump/status', methods = ['GET'])
def status():
	return pump.status()
