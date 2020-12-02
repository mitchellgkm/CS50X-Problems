from flask import Flask, render_template, request
import random

app = Flask(__name__)

@app.route('/') # Default or index page is just a slash
def index():
    x = random.randint(1,10)
    return render_template('index.html', name=x)

@app.route('/goodbye') # Default or index page is just a slash
def goodbye():
    return 'Goodbye'

@app.route('/hello')
def hello():
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    else:
        return render_template("hello.html", name=name)