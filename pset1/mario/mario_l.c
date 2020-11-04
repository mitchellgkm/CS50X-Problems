#include <cs50.h>
#include <stdio.h>

int main(void)
{
    
    int n;
    
    do
    {
        
        n = get_int("Height: \n"); //Input
        
    }
    while (n < 1 || n > 8); //Re-prompts if below 1 or above 8, or not a number
    
    {
        
        for (int i = 0; i < n; i++) //Starts loop and counts up to input -> runs whole loops n times
        
        { 
            
            for (int j = n - i; j > 1; j--) //Prints n - 1 spaces every loop and reduces by 1; e.g. for 3 2 spaces, then 1, then 0 etc.
        
            { 
           
                printf(" ");
            
            }
        
            for (int x = 0; x < i + 1; x++) //Nested for loop; Prints i + 1 amount of hashes each loop; starts with 1, then 2 etc.
        
            {
        
                printf("#");
        
            
            }
            
            printf("\n");
        
        }


    }
}
