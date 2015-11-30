from flask import Flask
from model import db
from flask.ext.cors import CORS

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://artiom:password@193.219.42.49:3036/moisture'
db.init_app(app)
cors = CORS(app)

from application import views
from application import api
