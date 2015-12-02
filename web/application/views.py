from application import app
from model import User

from flask import render_template, redirect, url_for, request, session, flash
from functools import wraps

# create the application object
# config
app.secret_key = 'my precious'
# login required decorator
def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('You need to login first.')
            return redirect(url_for('login'))
    return wrap

@app.route('/')
@login_required
def index():
    return render_template('dashboard.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        # TO - DO check credentials with database
        userPwd = request.form['password']
        user = User.query.filter_by(email = request.form['username']).first()
        if not user:
            error = 'Invalid Credentials. Please try again.'
        else:
            if user.check_password(userPwd):
                session['logged_in'] = True
                flash('You were logged in.')
                return redirect(url_for('index'))
            else:
                render_template('login.html', error=error)
    return render_template('login.html', error=error)

@app.route('/logout')
@login_required
def logout():
    session.pop('logged_in', None)
    flash('You were logged out.')
    return redirect(url_for('login'))