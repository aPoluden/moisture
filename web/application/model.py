from flask.ext.sqlalchemy import SQLAlchemy
from werkzeug import generate_password_hash, check_password_hash
from func import condition

#Database
db = SQLAlchemy()

#Pump
class Pump():
	
	working = False

	def status(self):
		if self.working is False:
			return condition.OFF
		else:
			return condition.ON

pump = Pump()

#User
class User(db.Model):
	__tablename__ = 'Users'
	uid = db.Column(db.Integer, primary_key = True)
	firstname = db.Column(db.String(100))
	lastname = db.Column(db.String(100))
	email = db.Column(db.String(100), unique=True)
	pwdhash = db.Column(db.String(100))
	# admin = db.Column(db.Integer)
	
	def __init__(self, firstname, lastname, email, password, admin):
	    self.firstname = firstname.title()
	    self.lastname = lastname.title()
	    self.email = email.lower()
	    self.pwdhash = generate_password_hash(password)
	    self.admin = admin
	# salted hash
	def set_password(self, password):
	    self.pwdhash = generate_password_hash(password)
     
	def check_password(self, password):
	    return check_password_hash(self.pwdhash, password)
