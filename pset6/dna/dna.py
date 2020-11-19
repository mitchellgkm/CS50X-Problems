import csv
import sys  # Command-line argument handler
import re  # Regex

# Remind of usage
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit()

# Define a function to return count of consecutive groupings for each STR

def sequencecount(STR, sequence):
    groups = re.findall(rf'(?:{STR})+', sequence)  # Produces an array of x amount of consecutive 'groups'
    if len(groups) == 0:
        return(0)
    largest = max(groups, key=len)  # Finds the biggest one
    return(len(largest) // len(STR))  # Integer divisor // gives whole number for largest number of consecutive groupings


# Tap into mainline arguments
# sys.argv[0] = dna.py
database = sys.argv[1]  # Database CSV file
sequence = sys.argv[2]  # Sequence text file for specific person


# Open sequence text file and read from it
f = open(sys.argv[2])
sequencestring = f.read()


countAGATC = sequencecount("AGATC", sequencestring)
countAATG = sequencecount("AATG", sequencestring)
countTATC = sequencecount("TATC", sequencestring)


# Open database file and read it
# use csv.DictReader to output the CSV into dict form:
# DictReader creates a sequence of dictionaries

with open(database, mode='r') as csvfile:
    reader = csv.DictReader(csvfile)
    data = [r for r in reader]  # Convert to list then tap into like an array

if database == "databases/small.csv":
    for i in range(len(data)):
        if int(data[i]['AGATC']) == countAGATC and int(data[i]['AATG']) == countAATG and int(data[i]['TATC']) == countTATC:
            print(f"{data[i]['name']}")
            break
        elif i == len(data) - 1:
            print("No match")

elif database == "databases/large.csv":
    countTTTTTTCT = sequencecount("TTTTTTCT", sequencestring)
    countTCTAG = sequencecount("TCTAG", sequencestring)
    countGATA = sequencecount("GATA", sequencestring)
    countGAAA = sequencecount("GAAA", sequencestring)
    countTCTG = sequencecount("TCTG", sequencestring)

    for i in range(len(data)):
        if int(data[i]['AGATC']) == countAGATC and int(data[i]['AATG']) == countAATG and int(data[i]['TATC']) == countTATC and int(data[i]['TTTTTTCT']) == countTTTTTTCT and int(data[i]['TCTAG']) == countTCTAG and int(data[i]['GATA']) == countGATA and int(data[i]['GAAA']) == countGAAA and int(data[i]['TCTG']) == countTCTG:
            print(f"{data[i]['name']}")
            break
        elif i == len(data) - 1:
            print("No match")
