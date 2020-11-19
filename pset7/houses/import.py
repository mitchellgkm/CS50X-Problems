# TODO
import csv
import cs50
import sqlite3
import sys


if len(sys.argv) != 2:
    print("Usage: python import.py source.csv")
    sys.exit()

# Open database file and write to it
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")  # Set db variable equal to the DB object (aliasing)


# Create table to export data into
# Create table structure within the database file
db.execute("CREATE TABLE students(first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

#Add first, middle and last name functionality#

source = sys.argv[1]  # Deem the source file as that passed through the argument

file = open(source, "r")  # Open the source data file

reader = csv.DictReader(file, delimiter=",")  # Reads from the source file

for row in reader:

    # Accesses values in key-value pair structure
    name = row["name"]

    # Split name into first, middle and last using the split method
    # https://www.tutorialspoint.com/python/string_split.htm
    # str.split(str="", num=string.count(str)) -?
    # str = string to be split
    # first argument is delimiter to be split on (default is space)
    # Second argument is number of splits to make
    # Produces a list of each substring

    nameList = name.split()

    if len(nameList) == 3:
        first = nameList[0]
        middle = nameList[1]
        last = nameList[2]

    else:
        first = nameList[0]
        middle = None  # Stands in for the NULL character in Python
        last = nameList[1]

    house = row["house"]
    birth = row["birth"]

    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle,
               last, house, birth)  # Insert data from source into movies.db using the ? as placeholders
