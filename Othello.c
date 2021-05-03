/*
 * Coded by Joshua Harris - 20709465 - joshua.harris@ucdconnect.ie
 *
 * This program runs a game of Othello. The board can be any size and must be set under BDSIZE in the GlobalValues header file.
 * By default, it is set to an 8x8 board. The game requires 2 human players. After each turn the score will be printed, then
 * the current board layout, and then the valid Moves. If there are no valid moves for a player, they will be informed and then
 * play will automatically pass to the other player. The game ends when either the board is full, or both players have no valid moves.
 *
 * At the end of play the scores and the winner will be printed out, and will be saved, along with the start time of the game, to a
 * file called Othello-results.txt
 */

#include <stdio.h>
#include <time.h>
#include "UserInput.h"  // Any functions involving user input
#include "Moves.h"      // Any functions to do with moving / checking the board for moves
#include "PostWin.h"    // End game functions, which run after someone has won.
#include "GlobalValues.h"   //Any values which are used across the entire program.

// 2 characters which hold which colour is currently playing, and opposition colour.
char currCol = 'B';
char oppCol = 'W';

// Function declarations
void printBoard();
void switchPlayer();
int play();

int main() {

    // Store the time the game started, which is the number of seconds since the Epoch (1 Jan 1970)
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

    // Print out both player's name and score.
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
                printf("%c%d, ", j+'A',i+1); // if the move is valid, prints out the column letter and row number
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
    /* Runs 1 turn of the game */

    int anyValid = checkMoves(); // Check for possible moves

    // If there are no valid moves for the current player, they are informed and the game switches to the next player.
    // If the next player has no valid moves, the game ends.
    if (anyValid == 0){
        printf("Sorry %s, you have no available moves\n", (currCol == 'B' ? black.name : white.name));
        switchPlayer();
        anyValid = checkMoves();
        if (anyValid == 0){ //If this is returned 0, then we have checked for both players and there are no moves.
            return 0;
        }
    }

    printBoard();// Print board
    playerMove();// Ask the current player for their turn
    switchPlayer();// Switch players

    return 1;  // Returning 1 informs the main function that there are more available moves.
}
