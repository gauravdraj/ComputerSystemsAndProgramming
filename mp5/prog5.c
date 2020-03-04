/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/* 
This program provides the source code for the Wheel of Fortune game. There are
three methods that I had to code - set_seed, start_game, and make_guess. The
game first prompts the player to enter a seed to generate random numbers.
set_seed makes sure that the inputted seed is valid and generates + returns
1 if set properly and 0 if not. start_game is then used to generate 4 solutions
from the pool of possible answers and initializes guess_number and max_score
according to the assignment description. Finally, make_guess takes the user's guess,
evaluates it, and assigns a score to it. If the user entered a valid guess, it will
compare each guess to the solution and inform the user of perfect and misplaced matches.
It'll update the score accordingly and return according to the description.

partner: pranay2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};

/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
      printf("set_seed: invalid seed\n"); //print error message if invalid
      return 0;
    } else {
        srand(seed); //set seed if valid
        return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    //your code here
    for (int index = 0; index < 4; index++) { //loop 4 times for 4 solutions
        int random = rand() % 8; //choose one of the 8 options in the  pool
        for (int letter = 0; letter < 10; letter++) {
            solutions[index][letter] = pool[random][letter]; //assign the chosen option to the solutions
        }
    }
    guess_number = 1; //initialize guess_number
    max_score = -1; //initialize max_score
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
   // your code here
    int score = 0;
    int perfectMatches = 0;
    int misplacedMatches = 0; // this section initializes variables related to matching
    int numGuesses;

    char guessOne[10];
    char guessTwo[10];
    char guessThree[10]; // this section declares variables for the user's inputted guesses
    char guessFour[10];
    char post[2];

    numGuesses = sscanf(guess_str, "%s%s%s%s%1s", guessOne, guessTwo, guessThree, guessFour, post); //parse user input for guesses
    char* guesses[4] = {guessOne, guessTwo, guessThree, guessFour}; //put parsed guesses into an array

    int matchedSolution[4] = {0, 0, 0, 0}; // array for solutions that have been matched
    int matchedGuess[4] = {0, 0, 0, 0}; // array for guesses that have been matched

    if (numGuesses == 4) { // if there aren't 4 guesses, it isn't a valid guess
        for (int i = 0; i < 4; i++) {
            if (is_valid(guesses[i]) == 1) { // if the guess is part of the pool of answers, compare
                if (strcmp(guesses[i], solutions[i]) == 0) {
                    matchedSolution[i] = 1;
                    matchedGuess[i] = 1; // mark indeces as matched
                    ++perfectMatches; // increase perfect matches if indeces match
                }    
            } else {
                printf("make_guess: invalid guess\n"); // if guess is not part of the pool of answers, print error message
                return 0;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (matchedGuess[i] == 0) { // for every unmatched guess
                for (int j = 0; j < 4; j++) {
                    if (strcmp(guesses[i], solutions[j]) == 0 && matchedSolution[j] == 0) { // for every unmatched solution, if a guess = a solution
                        matchedSolution[j] = 1;
                        matchedGuess[i] = 1; //mark indeces as matched
                        ++misplacedMatches; // increase misplaced matches if answers are right but indeces don't match
                    }
                }
            }
        }
    } else {
        printf("make_guess: invalid guess\n"); // invalid guess if there aren't 4 solutions
        return 0;
    }
    score = score + (perfectMatches * 1000); // add corresponding perfect match score to current score
    score = score + (misplacedMatches * 100); // add misplaced match score to current score
    if (score > max_score) max_score = score; //update max_score if current score is greater
    printf("With guess %d, you got %d perfect matches and %d misplaced matches. \nYour score is %d and current max score is %d.\n", guess_number, perfectMatches, misplacedMatches, score, max_score);
    ++guess_number; // increment guess number
    if (perfectMatches == 4) return 2; // signal to end game if all have been matched
    return 1; // signal to continue the game
}
