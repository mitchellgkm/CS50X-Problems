#include <stdio.h> //Standard package
#include <cs50.h> //Additional packages, including get_string

int main(void) //Main function
{
    string a = get_string("Hello, what is your name?\n"); //Prompts user for string input
    printf("Hello, %s\n", a); //Prints "Hello" and their input using a %s placeholder
}