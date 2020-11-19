# prints a list of students for a given house in alphabetical order
# accept name of house as a command-line argument
# query the students table in the student.db database
# print out each student's full name and birth year, formatted as e.g. Harry James Potter, born 1980 or Luna Lovegood, born 1981
# students ordered by last name; ordered by first name if last name the same

import csv
import cs50
import sqlite3
import sys


if len(sys.argv) != 2:
    print("Usage: python roster.py HOUSENAME")
    sys.exit()

if sys.argv[1].lower() == "gryffindor" or sys.argv[1].lower() == "hufflepuff" or sys.argv[1].lower() == "ravenclaw" or sys.argv[1].lower() == "slytherin":

    house = sys.argv[1].capitalize()

    db = cs50.SQL("sqlite:///students.db")  # Establish connection and assign it to a variable

    result = db.execute(
        f"SELECT first, middle, last, birth FROM students WHERE house = '{house}' ORDER BY last, first")  # Runs SQL query

    for row in result:

        first = row["first"]
        middle = row["middle"]
        last = row["last"]
        birth = row["birth"]

        if middle == None:
            print(f"{first} {last}, born {birth}")

        else:
            print(f"{first} {middle} {last}, born {birth}")


else:
    print("Usage: python roster.py HOUSENAME")
    sys.exit()
