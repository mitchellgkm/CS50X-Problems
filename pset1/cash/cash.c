#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    float f;
    do 
    {
        f = round(get_float("Change owed: ") * 100); //Multiply inputs into cents ($0.41 becomes 41c)
    }   //Round up floats to make sure not too many trailing decimals
    while
    (f < 1);
    {
    
    float quarters = floor(f / 25); //Divides by the largest to find how much it can be 'filled', then rounds down
    
    f -= quarters * 25; //Total is then reduced by this rounded down number
    
    float dimes = floor(f / 10); //Remainder is worked on here
    
    f -= dimes * 10; //Reduced again
   
    float nickels = floor(f / 5);
    
    f-= nickels * 5;
    
    float pennies = floor(f);

    float total = quarters + dimes + nickels + pennies; //Gives total count

    printf("%.0f\n",total); //Print out with no decimal place
}
}