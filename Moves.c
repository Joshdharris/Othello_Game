//
// Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
//

#include "Moves.h"
#include "GlobalValues.h"

int checkMoves() {
    /* This function checks whether a move is valid. */

    // First reset the valid moves array so there are no valid moves.
    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j<BDSIZE; j++){
            validMoves[i][j] = 0;
        }
    }

    // Then we check for valid moves, and change that position in the valid moves array to 1, if the move is valid.

    int totalMoves = 0; //Keeps track of total number of available moves.

    // If a square on the board is empty, we run the move check to verify whether it is a valid move or not. Move check
    // will return 0 if the move is not valid, and 1 if it is. We add this to our total moves.
    for (int i = 0; i < BDSIZE; i++) {
        for (int j = 0; j < BDSIZE; j++) {
            if (Board[i][j] == ' ') {  // If
                totalMoves += move(i, j, 1);
            }
        }
    }
    return totalMoves;

}
int move(int row, int col, int check){
    int flag = 1; // used later to ensure player only scores once for an empty square

    for (int rowPos = -1; rowPos <= 1; rowPos++) {
        for (int colPos = -1; colPos <= 1; colPos++) {

            // We make sure that each square being checked is on the board. The final bracket ensures we aren't checking the
            // same square (which will be at rowPos = 0, colPos = 0)
            if ((rowPos + row >= 0) && (rowPos + row < BDSIZE) && (colPos + col >= 0) && (colPos + col < BDSIZE) && !(rowPos == 0 && colPos == 0)) {

                // As long as it's a valid square we check if it belongs to the opponent. If it does, there is a potential valid move.
                if (Board[rowPos + row][colPos + col] == oppCol) {

                    // The square belongs to the opponent. We need to keep checking in that direction. Save the position of the checked square.
                    int dirRow = rowPos + row;
                    int dirCol = colPos + col;

                    // While ensuring the squares being checked are on the board and belong to our opponent, continue checking in that direction
                    while ((dirRow >= 0) && (dirCol >= 0) && (dirRow < BDSIZE) && (dirCol < BDSIZE) && (Board[dirRow][dirCol] == oppCol)) {
                        dirRow = dirRow + rowPos;
                        dirCol = dirCol + colPos;

                        // If the square belongs to us, then we have a line with a blank square, a series of opponent squares, then our square.
                        if (Board[dirRow][dirCol] == currCol) {

                            if (check == 1){             // If we are checking for available moves, update validMoves array and return 1.
                                validMoves[row][col] = 1;
                                return 1;
                            }

                            else {  // If we are taking a move: go back through the squares and change them to our colour.

                                if (flag > 0) {
                                    (currCol == 'B' ? black.score++ : white.score++);  // Add 1 to player's score for the empty square
                                    flag--; // Flag ensures blank square is not counted multiple times.
                                }

                                while (!(dirRow == row && dirCol == col)) {
                                    dirRow = dirRow - rowPos;
                                    dirCol = dirCol - colPos;
                                    Board[dirRow][dirCol] = currCol;

                                    // Finally we update the score to reflect changing those pieces which have swapped colours.
                                    if (!(dirRow == row && dirCol == col)) {
                                        updatePlayerScore(dirRow, dirCol);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
void updatePlayerScore(int dirRow, int dirCol){

    if (Board[dirRow][dirCol] == 'B'){
        black.score++;
        white.score--;

    }
    else if (Board[dirRow][dirCol] == 'W'){
        white.score++;
        black.score--;
    }
}