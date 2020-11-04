#include <cs50.h>
#include <stdio.h>

int main(void){
    int n;
    do{
        n = get_int("Height: \n");
    }
    while(n < 1 || n > 8);
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = n - i; j > 1; j--){
            printf(" ");
        }
        for (int x = 0; x < i + 1; x++)
        {
            printf("#");
        }
            printf("  ");
            
        for (int y = 0; y < i + 1; y++)
        {
            printf("#");
        }
            printf("\n");

    }


}
}
