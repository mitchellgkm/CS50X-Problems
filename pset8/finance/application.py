import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Build out pulling from the transaction history

    userId = session["user_id"]
    cashRaw = db.execute(f"SELECT cash FROM users WHERE id={userId}")[0]["cash"]
    cash = usd(cashRaw)
    totalValue = float(cashRaw)

    sharesOwned = db.execute(f"SELECT * FROM transactions WHERE user_id={userId}")

    #Update prices
    for share in sharesOwned:
        symbol = share["symbol"]
        currentPrice = lookup(symbol)["price"]
        db.execute(f"UPDATE transactions SET current_price = '{currentPrice}' WHERE user_id='{userId}' AND symbol='{symbol}'")

    index = db.execute(f"SELECT symbol, SUM(shares), name, AVG(current_price) FROM transactions WHERE user_id='{userId}' GROUP BY symbol HAVING SUM(shares)>0")

    for share in index:
        symbol = share["symbol"]
        count = share["SUM(shares)"]
        price = lookup(symbol)["price"]
        value = count * price
        totalValue += value

    totalValue = usd(totalValue)

    return render_template("index.html", cash=cash, index=index, totalValue=totalValue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":

        symbolInput = request.form.get("symbol")
        shares = float(request.form.get("shares"))

        symbolName = lookup(symbolInput)["name"]
        symbolPrice = lookup(symbolInput)["price"]
        symbolTicker = lookup(symbolInput)["symbol"]

        if symbolInput != symbolTicker or symbolInput == "" or shares == "" or shares < 1:
            return apology("No buy for you senpai!")

        else:
            userId = session["user_id"]
            totalPrice = shares * symbolPrice
            availableCash = float(db.execute(f"SELECT cash FROM users WHERE id={userId}")[0]["cash"])

            if totalPrice > availableCash:
                return apology("Not enough available tendies")
            else:
                now = datetime.now()
                transTime = now.strftime("%d/%m/%Y %H:%M:%S")
                availableCash -= totalPrice

                db.execute(f"UPDATE users SET cash = '{availableCash}' WHERE id = '{userId}'")

                db.execute(f"INSERT INTO transactions (trans_time, trans_type, user_id, symbol, price, shares, value, name, current_price) VALUES ('{transTime}','BUY','{userId}','{symbolTicker}','{symbolPrice}','{shares}','{totalPrice}','{symbolName}','{symbolPrice}')")

                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    userId = session["user_id"]

    shares = db.execute(f"SELECT symbol, shares, price, trans_time FROM transactions WHERE user_id={userId} ORDER BY trans_id DESC")

    return render_template("history.html", shares=shares)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":

        symbolInput = request.form.get("symbol")

        symbolName = lookup(symbolInput)["name"]
        symbolPrice = lookup(symbolInput)["price"]
        symbolTicker = lookup(symbolInput)["symbol"]

        if symbolInput != symbolTicker or symbolInput == "":
            return apology("No quote for you senpai!")

        else:
            return render_template("quoted.html", name=symbolName, symbol=symbolTicker, price=usd(symbolPrice))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        passwordConfirm = request.form.get("password2")

        if password != passwordConfirm or username == "" or password == "":
            return apology("")

        else:
            hashed = generate_password_hash(password)
            db.execute(f"INSERT INTO users (username,hash) VALUES ('{username}','{hashed}')")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return apology("Something went fucky wucky")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    userId = session["user_id"]

    sharesOwned = db.execute(f"SELECT symbol, SUM(shares) FROM transactions WHERE user_id={userId} GROUP BY symbol HAVING SUM(shares)>0")

    if request.method == "GET":

        return render_template("sell.html", sharesOwned=sharesOwned)

    elif request.method == "POST":

        symbolInput = request.form.get("symbol")
        shares = float(request.form.get("shares")) * (-1)

        symbolName = lookup(symbolInput)["name"]
        symbolPrice = lookup(symbolInput)["price"]
        symbolTicker = lookup(symbolInput)["symbol"]

        shareCount = float(db.execute(f"SELECT SUM(shares) FROM transactions WHERE user_id={userId} AND symbol='{symbolInput}' GROUP BY symbol HAVING SUM(shares)>0")[0]["SUM(shares)"] * (-1))

        if symbolInput != symbolTicker or symbolInput == "" or shares == "" or shares > 0 or shares < shareCount:
            return apology("No sell for you senpai!")

        else:
            totalPrice = shares * symbolPrice
            availableCash = float(db.execute(f"SELECT cash FROM users WHERE id={userId}")[0]["cash"])

            now = datetime.now()
            transTime = now.strftime("%d/%m/%Y %H:%M:%S")
            availableCash -= totalPrice

            db.execute(f"UPDATE users SET cash = '{availableCash}' WHERE id = '{userId}'")

            db.execute(f"INSERT INTO transactions (trans_time, trans_type, user_id, symbol, price, shares, value, name, current_price) VALUES ('{transTime}','SELL','{userId}','{symbolTicker}','{symbolPrice}','{shares}','{totalPrice}','{symbolName}','{symbolPrice}')")

            return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Custom function - add cash to account"""
    if request.method == "GET":
        return render_template("addcash.html")
    elif request.method == "POST":
        userId = session["user_id"]

        cash = float(request.form.get("cash"))

        if cash == "" or cash < 1:
            return apology("No money woney for honey!")

        else:
            availableCash = float(db.execute(f"SELECT cash FROM users WHERE id={userId}")[0]["cash"])

            newCash = availableCash + cash

            db.execute(f"UPDATE users SET cash = '{newCash}' WHERE id = '{userId}'")

            return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
