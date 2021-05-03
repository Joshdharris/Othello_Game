//
// Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
// Contains any functions that involve user input.

#include "Moves.h"
#include "UserInput.h"
#include "GlobalValues.h"

void initialSetup(){
    /* This function will get the player names from the console.  It also resets their scores and sets up the initial board status */

    printf("Black will go first. Player 1, please input your name: ");
    fgets(black.name,sizeof(black.name)-1,stdin); // Get player 1's name.
    if (strchr(black.name, '\n') == NULL){ //If the user enters too many characters, this will remove excess from stdin.
        clearBuffer();
    }
    black.name[strcspn(black.name, "\n")] = 0;  // remove trailing new line character

    // Repeat for player 2
    printf("Player 2, please input your name: ");
    fgets(white.name,sizeof(white.name)-1,stdin);
    if (strchr(white.name, '\n') == NULL){
        clearBuffer();
    }
    white.name[strcspn(white.name, "\n")] = 0;

    // Set scores to 2
    black.score = 2;
    white.score = 2;

    // Clear the board, by blanking every element.
    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j< BDSIZE; j++) {
            Board[i][j] = ' ';
        }
    }

    // This prepares the board. The pieces are placed in the middle. (Note this game will support a board that is an
    // odd number of squares. In this case, the starting pieces will still be near the center.)
    Board[BDSIZE/2 - 1][BDSIZE/2 - 1] = 'B';
    Board[BDSIZE/2 - 1][BDSIZE/2] = 'W';
    Board[BDSIZE/2][BDSIZE/2 - 1] = 'W';
    Board[BDSIZE/2][BDSIZE/2] = 'B';

}
void playerMove(){
    unsigned char column;
    int row, colNum, valid = 0;

    //Ask the player for their move, using ternary option.
    printf("%s, select your move:  ", (currCol == 'B' ? black.name : white.name));

    while (valid == 0){
        scanf(" %c%d", &column, &row);  // Take in user input
        clearBuffer();                  //Remove excess characters
        column = toupper(column);       //Converts lowercase character to upper-case
        row--;                          //Remove 1 from row number as the board starts from 1 but the array starts from 0.
        colNum = column - 'A';          //Convert column to a number
        if (validMoves[row][colNum] == 1){
            valid = 1;                  //Breaks the loop if the move is valid
        }
        else
            puts("Sorry, that's not a valid move. Try again");
    }

    move(row, colNum, 0); //Take the move
}
void clearBuffer(){
    // Just eats up any extra letters at the end of an input line. Helps prevent errors with users writing too much.
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}