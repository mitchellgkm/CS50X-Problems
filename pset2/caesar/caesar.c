#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//Unencrypted text is generally called plaintext.
//Encrypted text is generally called ciphertext.
//And the secret used is called a key.
//Encrypting plaintext with a key of 1 shifts every letter 1 down into ciphertext, e.g. A becomes B, X becomes Y
// Caesars algorithm 'rotates' by ci = (pi + k) % 26
//ci = ith cypher char, pi = ith plain char, k = key and then gets remainder when dividing by 26
//Prompt the user for a key using mainline argument and a plaintext input

int main(int argc, string argv[])
{

    int a = 1;

    if (argc == 2) // If arguments consist of ./caesar and one other item only
    {
        for (int x = 0; x < strlen(argv[1]); x++) //Loop through elements within 'array' of inputted argument
        {
            a *= (int) isdigit(argv[1][x]); //Multiply 1 by 'isdigit' result of each character (returns zero if not a numeric)
        }

        if (a == 0) //If any of the characters are non numeric the whole end result will be zero
        {
            printf("Usage: ./caesar key\n");
            return 1; //Break
        }

        else
        {
            int k = (int) strtol(argv[1], 0, 0) % 26; //Gets key as an int by converting the string pointer argv

            string s = get_string("plaintext: "); //Input

            for (int i = 0; i < strlen(s); i++) //Iterates through each letter of the input
            {
                if (s[i] >= 'a' && s[i] <= 'z') //Selects the lower case alphabetic characters only
                {
                    if (s[i] + k < 'a' || s[i] + k > 'z') //If the result isn't another lowercase character
                    {
                        s[i] = s[i] + (k - 26); //Reverses / loops key back round if returned character isn't a letter
                    }
                    else
                    {
                        s[i] = s[i] + k; //Adds the key to the letter's ASCII code
                    }
                }

                else if (s[i] >= 'A' && s[i] <= 'Z') //Same as above with upper case letters
                {
                    if (s[i] + k < 'A' || s[i] + k > 'Z')
                    {
                        s[i] = s[i] + (k - 26);
                    }
                    else
                    {
                        s[i] = s[i] + k;
                    }
                }

                else
                {
                    s[i] = s[i]; //Keep the character as is if it's not a lowercase or uppercase
                }
            }

            printf("ciphertext: %s\n", s); //Output

        }

    }

    else
    {
        printf("Usage: ./caesar key\n");
        return 1; //Break
    }


}