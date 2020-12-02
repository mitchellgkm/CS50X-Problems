from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///lecture.db") #Assign the database file to a variable

@app.route('/') # Default or index page is just a slash
def index():
    rows = db.execute("SELECT * FROM registrants") #Run SQL query and save in a variable
    return render_template("index.html", rows = rows)

@app.route('/register', methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("name")
        email = request.form.get("email")
        db.execute(f"INSERT INTO registrants (name,email) VALUES ('{name}','{email}')")
        return redirect('/')
