// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"


bool dictionaryloaded = false;
int wordcount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //Goes to last possible point (45) then one more for null terminator
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 50; //Increased number of buckets from 1 to 100 to take each hash result

// Hash table
node *table[N];

//Overall usage: ./speller [dictionary] text
//[dictionary] is a file containing a list of lowercase words, one per line
//text is a file to be spell-checked

// Returns true if word is in dictionary else false
bool check(const char *word) //char * essentially means string
{

    //Return true if word is in the dictionary, false otherwise
    //Case insensitive

    //1. Hash word to obtain hash value

    int loc = hash(word);

    if (table[loc] == NULL)
    {
        return false;
    }

    //2. Access linked list at that index in the hash table

    else
    {
        node *cursor = table[loc];

        //3. Traverse linked list looking for a word (strcasecmp -> compares case insensitively)

        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }

            else
            {
                cursor = cursor->next;
            }
        }
    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word) //char * essentially means string
{
    // Source of hash function is http://www.cse.yorku.ca/~oz/hash.html

    unsigned int hash = 5381;
    int c = *word;
    c = tolower(c);

    while ((*word != 0))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        c = *word++;
        c = tolower(c);
    }

    //Returns % of N so it's in the range 0-(N-1) inclusive

    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
// Large dictionary loads by default; 143,091 words -> max 45 letters, none repeating
bool load(const char *dictionary) //char * essentially means string
{

    //TODO
    //1. Open dictionary file

    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL)
    {
        printf("Could not load dictionary\n");
        return false;
    }

    dictionaryloaded = true;

    //2. Read strings from file one at a time (set all to lower case?)

    char word[LENGTH + 1];
    while (fscanf(dictptr, "%s", word) != EOF) //Repeat for each word in the dictionary -> returns EOF at end of file
    {
        // fscanf(dictptr, "%s", word); //Reads each word -> 'word' = character array in memory to be read into
        //Didn't need to use this twice!!!

        //3. Create a new node for each word

        node *n = malloc(sizeof(node)); //Allocate memory for each node -> malloc may return NULL if all memory used
        if (n == NULL)
        {
            printf("Memory error in allocating node\n"); //Check if malloc returns NULL
            return 1;
        }

        //Copy over strings from dictionary into a node

        strcpy(n->word, word); //Change n's word property to whatever word is in the dictionary

        //4. Hash word to obtain a hash value (use hash function created above)

        //How do we determine which linked list to place the node in?
        //Use the hash function -> takes a string and returns the index -> table[x]

        int loc = hash(word);

        //5. Insert node into hash table at that location

        //Index in to the hash table to get particular linked list -> set pointers in correct order
        //Inserting new nodes -> point new node at first element in list, then point head of list to new node

        n->next = table[loc];
        table[loc] = n;

        wordcount++;
    }

    fclose(dictptr);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Increment a counter each time a node is added

    if (dictionaryloaded == true)
    {
        return wordcount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Call free on any memory allocated with malloc
    // Iterate over every node in the linked lists
    // Free all of hash table

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;

        }
    }

    dictionaryloaded = false;

    return true;

}
