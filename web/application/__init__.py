from flask import Flask

app = Flask(__name__)

if __name__ == '__main__':
    app.run()

from application import main
from application import views