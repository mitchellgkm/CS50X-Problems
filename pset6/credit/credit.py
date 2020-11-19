from cs50 import get_int
import math

def length(n):
    return int(len(str(n)))


def luhn(num):

    num = str(num)

    digit_sum = 0 #Inspired by https://stackoverflow.com/questions/32541487/is-this-the-most-efficient-way-to-write-the-luhn-algorithm-in-python

    for i, digit in enumerate(reversed(num)):
        n = int(digit)

        if i % 2 == 0: #Add if at an 'even' point in the card number
            digit_sum += n
        elif n >= 5: #Check digit
            digit_sum += n * 2 - 9
        else: #Double digit if 'odd' position in card number
            digit_sum += n * 2

    if digit_sum % 10 == 0:
        return True
    else:
        return False

n = 0
while n < 1:
    n = get_int("Number: ")

    lu = luhn(n)

    length = length(n)

    while n > 100:
        n /= 10

    n = math.floor(n)

    if (lu == True and (n == 34 or n == 37) and length == 15):
        print("AMEX")
    elif (lu == True and math.floor(n / 10) == 4 and (length == 13 or length == 16)):
        print("VISA")
    elif (lu == True and 51 <= n <= 55 and length == 16):
        print("MASTERCARD")
    else:
        print("INVALID")










