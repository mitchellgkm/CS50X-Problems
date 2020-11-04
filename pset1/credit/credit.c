#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Amex = 15 digits ; start with 34 or 37
// Mastercard = 16 digits ; start with 51 - 55
// VISA = 13 and 16 digits ; start with 4
// All card numbers have 'checksums' that check for fraud etc. through typos

// Luhn's Algorithm;
// 1. Multiply every other digit by 2, starting with second to last digit, then add the product together
// 2. Add the sum to the sum of the digits that weren't multiplied by 2
// 3. If the total's last digit is 0 then it is valid

int luhn(long f); //Call custom function (Luhn's Algorithm)

int main(void)
{
    long n;
    do
    {
        n = get_long("Number: \n");
    }
    while (n < 1);

    int lu = luhn(n); //Input n into the algorithm to check if valid

    int len = floor(1.0 + log10((double) llabs(n))); //Check card number length

    while (n > 100) //While loop that divides n by 10 until it can't go below 2 digits
    {
        n /= 10; //Gets first 2 digits
    }

    if (lu == 1 && (n == 34 || n == 37) && len == 15) //Self explanatory

    {
        printf("AMEX\n");
    }
    else if (lu == 1 && n / 10 == 4 && (len == 13 || len == 16))

    {
        printf("VISA\n");
    }
    else if (lu == 1 && (n == 51 || n == 52 || n == 53 || n == 54 || n == 55) && len == 16)

    {
        printf("MASTERCARD\n");
    }

    else

    {
        printf("INVALID\n");
    }
}

int luhn(long f)
{

    long prod = 0; //Defines product variable which will sumproduct the odd digits
    long alt = 0; //Defines alt variable which will sum the remaining digits
    long h = 10;
    long a = 1;

    int i = floor(1.0 + log10((double) llabs(f))) + 2 / 2; //Divide n + 2 by 2 to get number of iterations

    while (--i > 0) //Reduce i to 0 by increments of 1, but run this loop that many times
    {
        long m = f / h; // n / 10 to shift digits over one to get second to last digit
        long x = m % 10; // modulo 10 of new number -> e.g. 100,042 / 10 = 10,004 r 2 ; 10,004 / 10 = 1000 r 4
        long d = 2 * x; //Multiplies chosen digit by 2

        while (d > 0)  //Takes this selected digit * 2 then splits it into constituent digits if > 10
        {
            int e1 = d % 10; // e.g. 12 modulo 10 = 1 r 2; 34 modulo 10 = 3 r 4
            prod += e1; // Adds to product
            d /= 10; //Starts again to get first digit, then loops again
        }

        long m2 = f / a; //Gets every other digit starting from last => just starts with n
        long x2 = m2 % 10; //Starts as just n modulo 10 to give final digit (e.g. 100,002 -> 10,000 r 2)
        alt += x2;

        h *= 100; //Increases denominator for m by 10 squared each loop to get odd digit
        a *= 100; //Increases denominator for m2 by 10 squared each loop to get odd digit
    }
    long result = prod + alt; //Adds up result
    long check = result % 10;

    if (check == 0)
    {
        return 1; //Simple boolean to check if card is valid
    }
    else
    {
        return 0;
    }


}
