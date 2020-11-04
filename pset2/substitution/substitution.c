#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// encrypts "This is CS50" as "Cbah ah KH50" using yukfrnlbavmwzteogxhcipjsqd as key
//    output not valid ASCII text
// encrypts "This is CS50" as "Cbah ah KH50" using YUKFRNLBAVMWZteogxhcipjsqd as key
//    output not valid ASCII text


int main(int argc, string argv[])
{

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Just use one alphabet all in caps

    int a = 0;

    if (argc == 2)
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1; //Break
        }

        else

        {

            for (int z = 0; z < 26; z++) //Convert the key to uppercase

            {
                argv[1][z] = toupper(argv[1][z]);
            }

            string key = argv[1]; //Turn the argument into an array of characters

            {

                for (int x = 0; x < strlen(argv[1]); x++)

                {

                    if (!isalpha(key[x]))
                    {
                        printf("Key can contain only alphabetic characters\n");
                        return 1; //Break
                    }

                    for (int j = x + 1; j < 26; j++)
                    {
                        // if there is a repeated char, print an error and return 1
                        if (key[x] == key[j] || key[x] == ' ')
                        {
                            printf("Key doesn't allow repeating characters.\n");
                            return 1;
                            break;
                        }
                    }

                }

            }

            string s = get_string("plaintext: "); //Input

            for (int n = 0; n < strlen(s); n++)
            {
                // check if the char is a letter
                if (isalpha(s[n])) //If character in the nth index of the string, go ahead with the second loop
                {
                    // loop that goes through all the alphabet letters to see which one the current letter is and to change it with the keys one
                    for (int m = 0; m < 26; m++) //Loop through alphabets
                    {
                        if (toupper(s[n]) == alphabet[m]) //Convert all to upper; if nth letter of string = mth alphabet character, convert to key
                        {
                            // conditions that keep the cases of the substituted chars
                            if (islower(s[n]))
                            {
                                s[n] = tolower(key[m]); //Converts lower case part of string to lower case of key
                            }
                            else if (isupper(s[n]))
                            {
                                s[n] = toupper(key[m]); //Converts upper case part of string to upper case of key
                            }
                            break; // add this to prevent iterating over the same letter more than once
                        }
                    }
                }
                // if char is not letter, leave it as it is
                else
                {
                    s[n] = s[n];
                }
            }

            printf("ciphertext: %s\n", s); //Output
            return 0;
        }


    }



    else

    {
        printf("Usage: ./substitution key\n");
        return 1; //Break
    }





}