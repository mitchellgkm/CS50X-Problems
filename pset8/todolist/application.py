from flask import Flask, render_template, request, redirect, session
from flask_session import Session
import random

app = Flask(__name__)
app.config["SESSION PERMANENT"] = False #Don't want a permanent session
app.config["SESSION TYPE"] = "filesystem" #Stores session data in local file area
Session(app) #Allows the app to access the Session library


@app.route('/') # Default or index page is just a slash
def tasks():
    if "todos" not in session: #If this current session doesn't have 'todos' present
        session["todos"] = [] #Array of todo items
    return render_template("tasks.html", todos=session["todos"]) #Personalised list of tasks

@app.route('/add', methods=["GET", "POST"]) #Can get both get (request data) and post (send data) requests
def add():
    if request.method == "GET": #If the user is requesting data
       return render_template("add.html")
    else: #If the user is sending data (through the form)
        todo = request.form.get("newtask") #Access data from form
        session["todos"].append(todo) #Add new item to the todos array
        return redirect("/") #Use redirect to redirect to a certain URL

