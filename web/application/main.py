import os, time, datetime, db
from application import app

@app.route('/data/<int:value>',  methods = ['POST', 'GET'])
def receiveData(value):
    ts = getTimeStamp()
    return db.dbStatus()

def getTimeStamp():
	ts = time.time()
	return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
