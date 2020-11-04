#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)//Loop over candidate names provided (candidate names) number times
    {
        if (strcmp(name, candidates[i].name) == 0)//Compare if name input equals a candidate name provided
        {
            candidates[i].votes++; //Iterate number of votes for i candidate if their name matches
            return true;//Valid name; break for loop
        }

    }

    return false;//If loop doesn't find anything, name is invalid

}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count - 1; i++) //Selection sort vote counts; start with n - 1 passes
    {
        int iMin = i;

        for (int j = i + 1; j < candidate_count; j++) //Make n comparisons
        {
            if (candidates[j].votes < candidates[iMin].votes) //If i'th integer is less than i + 1'th integer, switch them
            {
                iMin = j;

                int tempint = candidates[iMin].votes;//Dummy here to store i'th string
                candidates[iMin].votes = candidates[i].votes; //Also switch candidate names
                candidates[i].votes = tempint;

                string tempstr = candidates[iMin].name;//Dummy here to store i'th string
                candidates[iMin].name = candidates[i].name; //Also switch candidate names
                candidates[i].name = tempstr;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++) //If anyone has votes equivalent to the highest number of votes, print their name
    {
        if (candidates[i].votes == candidates[candidate_count - 1].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

