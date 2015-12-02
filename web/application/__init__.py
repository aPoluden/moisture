from flask import Flask
from model import db
from flask.ext.cors import CORS

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://artiom:password@localhost:3036/village'
db.init_app(app)
cors = CORS(app)

from application import views
from application import api
