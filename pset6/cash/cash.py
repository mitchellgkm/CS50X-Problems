from cs50 import get_float
import math

cash = 0;

while cash < 1:
    cash = get_float("Change owed: ") * 100

def change (x):
    q = math.floor(x / 25)
    x -= q * 25
    d = math.floor(x / 10)
    x -= d * 10
    n = math.floor(x / 5)
    x -= n * 5
    p = math.floor(x)

    total = q + d + n + p
    return total


print(f"{change(cash)}")