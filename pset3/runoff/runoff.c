#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) //Populates candidates with details (name, votes, elim)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: "); //Number of voters
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) //Vote loop
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name)) //Takes inputs for voter, preference # and candidate name
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("Tie: %s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    // voter = preferences[voter]
    // rank  = preferences[voter][rank] -> update this to align to the candidate's index

    for (int i = 0; i < candidate_count; i++) //Loops through candidates
    {
        if (strcmp(name, candidates[i].name) == 0 && candidates[i].eliminated == false) //If the name chosen at that rank matches a candidate, update j'th preference of voter i to equal that candidate
        {
            preferences[voter][rank] = i; //
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    //Votes = number of Rank 1s -> needs to then become Rank 2s, Ranks 3s etc. after eliminations

    for (int i = 0; i < voter_count; i++) //Loops over voters
    {
        for (int j = 0; j < candidate_count; j++) //Loops
        {
            if (candidates[preferences[i][j]].eliminated == false) //Takes j'th preference (2nd, 3rd etc. in event of runoff) of i'th voter and checks what candidate's index it aligns to
            {
                candidates[preferences[i][j]].votes++; //Increases vote count for that candidate
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) //Loops through candidates
    {
        if (candidates[i].votes > voter_count / 2) //If majority won, instant win for candidate
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
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

                bool tempbool = candidates[iMin].eliminated;//Dummy here to store i'th string
                candidates[iMin].eliminated = candidates[i].eliminated; //Also switch candidate eliminated boolean
                candidates[i].eliminated = tempbool;
            }
        }
    }

    for (int x = 0; x < candidate_count; x++) //Loops through candidates and finds first -> as they are sorted, this will be the candidate with fewest votes
    {
        if (candidates[x].eliminated == false) //Only picks first non-eliminated candidate
        {
            return candidates[x].votes; //Returns minimum number of votes
            break;
        }
    }

    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tiecount = 0; //Creates variable to count how many candidates equal each other on votes
    int validcount = candidate_count; //Number to reach starts at max candidate count and decreases based on eliminated vs remaining candidates

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false) //Only counts a candidate if they've not been eliminated
        {
            tiecount++;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == true) //Decreases max to be reached if candidates are eliminated
        {
            validcount--;
        }
    }

    if (tiecount == validcount) //If number of candidates with equal votes is all the candidates, it's a tie
    {
        tiecount = 0;
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min) //If candidate has lowest votes and isn't eliminated, eliminate them
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
