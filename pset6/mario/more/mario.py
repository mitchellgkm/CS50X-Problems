from cs50 import get_int


x = 0;

while x < 1 or x > 8:
    x = get_int("Height: ")

for i in range(x):
    print(f"{(x-1-i)*' '}{(i+1)*'#'}  {(i+1)*'#'}")


