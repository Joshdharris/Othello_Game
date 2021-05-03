/*
 * Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
 */

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

    // If square is empty, verify whether it is a valid move. Move check returns 0 if invalid, 1 if valid. Add to total moves.
    for (int i = 0; i < BDSIZE; i++) {
        for (int j = 0; j < BDSIZE; j++) {
            if (Board[i][j] == ' ') {
                totalMoves += move(i, j, 1);
            }
        }
    }
    return totalMoves;

}
int move(int row, int col, int check){
    /* This function both checks for available moves, and carries out a particular move if required */

    int flag = 1; // used later to ensure player only scores once for an empty square

    for (int rowPos = -1; rowPos <= 1; rowPos++) {
        for (int colPos = -1; colPos <= 1; colPos++) {

            // Ensure each square being checked is on the board. Final bracket ensures we aren't checking the same square.
            if ((rowPos + row >= 0) && (rowPos + row < BDSIZE) && (colPos + col >= 0) && (colPos + col < BDSIZE) && !(rowPos == 0 && colPos == 0)) {

                // Check if square belongs to the opponent. If it does, there is a potential valid move.
                if (Board[rowPos + row][colPos + col] == oppCol) {

                    // The square belongs to the opponent. Keep checking in that direction. Save position of the checked square.
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

                                while (!(dirRow == row && dirCol == col)) {  // Backtracks through the squares and changes to current player's colour.
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
    /* Updates the player's score */

    if (Board[dirRow][dirCol] == 'B'){
        black.score++;
        white.score--;

    }
    else if (Board[dirRow][dirCol] == 'W'){
        white.score++;
        black.score--;
    }
}