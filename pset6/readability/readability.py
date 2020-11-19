from cs50 import get_string
import string
import math
import re

s = get_string("Text: ")

letters = sum(c.isalpha() for c in s) #Counts all alphanumeric characters
words = sum(c.isspace() for c in s) + 1 #All spaces + 1 -> counts total words
sentences = len(re.split(r'[.!?]+', s)) - 1 #Splits the sentence into chunks through a regex and puts into an array

l = (letters * 100) / words
st = (sentences * 100) / words
grade = 0.0588 * l - 0.296 * st - 15.8

if (grade >= 16):
    print("Grade 16+")

elif (grade < 1):
    print("Before Grade 1")

else:
    print(f"Grade {round(grade)}") #Rounds final grade