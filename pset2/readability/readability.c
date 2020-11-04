#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Your program should count the number of letters, words, and sentences in the text.
You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z,
any sequence of characters separated by spaces should count as a word, and that any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.

Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.

If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+"
instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".
*/

int main(void)
{

    string s = get_string("Text: ");

    float low = 0; //Count number of lower case letters
    float up = 0; //Count number of upper case letters
    float spaces = 0; //Count number of words -> spaces + 1 = words
    float puncs = 0; //Counts full stops, exclamations, question marks -> sentences = puncs

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            low++;
        }

        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            up++;
        }

        else if (s[i] == ' ')
        {
            spaces++;
        }

        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            puncs++;
        }
    }

    /*printf("Lower: %f\n",low);
    printf("Upper: %f\n",up);
    printf("Words: %f\n",spaces + 1);
    printf("Sentences: %f\n",puncs);*/

    float words = spaces + 1;
    float l = ((low + up) * 100) / words;
    float st = (puncs * 100) / words;
    float grade = 0.0588 * l - 0.296 * st - 15.8;

    /*printf("%f\n",l);
    printf("%f\n",st);*/

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %.0f\n", round(grade));
    }



    //L = number of letters per 100 words = (letters * 100) / words
    //S = average number of sentences per 100 words = (sentences * 100) / words


}

