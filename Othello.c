/*
 * Coded by Joshua Harris - 20709465 - joshua.harris@ucdconnect.ie
 *
 */

#include <stdio.h>
#include <time.h>
#include "UserInput.h"
#include "Moves.h"
#include "GlobalValues.h"
#include "PostWin.h"

// 2 characters which hold which colour is currently playing, and opposition colour.
char currCol = 'B';
char oppCol = 'W';

// Function declarations
void printBoard();
void switchPlayer();
int play();


int main() {

    // First get the time the game started, which is the number of seconds since the Epoch (1 Jan 1970)
    time_t seconds = time(NULL);

    initialSetup(); // Prepare the game.

    //As long as there are available moves, run the game
    int movesAvailable = 1;
    while (movesAvailable > 0) {
        movesAvailable = play();
    }

    // Print final scores and record to file the time the game started, and the winner.
    endGame(seconds);

    return 0;
}
void printBoard(){
  /* After a bit of faffing about with this, I managed to rewrite this function so that it works for any size board */

    printf("  %s: %d v %d :%s\n", black.name, black.score, white.score, white.name);

    // Print top line of board
    for (int i = 0; i< BDSIZE; i++){
        printf(" ---");
    }
    printf("\n");

    for (int j = 0; j< BDSIZE; j++){
        for (int k = 0; k < BDSIZE; k++){
            printf("| %c ", Board[j][k]); // prints each line with the values from Board array
        }
        printf("| %d", j+1);  // Prints row number
        printf("\n");
        for (int i = 0; i< BDSIZE; i++){
            printf(" ---");  //prints line under each row
        }
        printf("\n");
    }

    // prints letters for the columns
    for (int i = 0; i<BDSIZE; i++){
        printf("  %c ", 'A'+ i);
    }
    printf("\n");


    //  LISTS VALID MOVES - looks through validMoves array to check which squares are valid.
    printf("Valid Moves: ");
    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j < BDSIZE; j++){
            if (validMoves[i][j] == 1){
                printf("%c%d ", j+'A',i+1);
            }
        }
    }
    printf("\n\n");

}
void switchPlayer() {
    // This function simply swaps the colours, which will change whose turn it is.
    if (currCol == 'B') {
        currCol = 'W';
        oppCol = 'B';
    }    // CHANGE CURRENT PLAYER TO PLAYER 2
    else {
        currCol = 'B';
        oppCol = 'W';
    }    // CHANGE CURRENT PLAYER TO PLAYER 1


}
int play(){
    int anyValid;

    anyValid = checkMoves(); // Check for possible moves
    if (anyValid == 0){
        printf("Sorry %s, you have no available moves\n", (currCol == 'B' ? black.name : white.name));
        switchPlayer();
        anyValid = checkMoves();
        //If this is returned 0, then we have checked for both players and there are no moves.
        if (anyValid == 0){
            return 0;
        }
    }
    printBoard();// Reprint board
    playerMove();// Ask the current player for their turn
    switchPlayer();// Switch players

    return 1;
}
