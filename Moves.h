/*
 * Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
 *
 * Important to talk a little about the move function. It takes in 3 arguments, the row, the column and the check.
 * Check verifies whether it is checking for available moves, or whether it is carrying out a move. Depending on the
 * number, 1 means it is checking. In this case, if it finds a valid move, it will simply update the corresponding
 * position in the validMoves array. 0 means it is taking a move. In this case, it will allocate that square to the
 * current player, change any valid squares belong to the opponent, to the current player, and update the players scores.
 *
 * The way the check works is to start from a blank square. It then checks every square around it to see if it belongs to
 * the opponent. If it finds one, it will continue to move in that direction, checking each square until it reaches the end
 * of the board, an empty square, or the current player's square. If it's the current player's square, the program will
 * then backtrack to the empty square, changing all the opponent squares on the way.
 * Rather than having an individual function for each direction, this function checks all directions for the square, each
 * time the function runs.
 */

#ifndef OTHELLO_GAME_MOVES_H
#define OTHELLO_GAME_MOVES_H

int checkMoves();  //Checks if a move is valid
int move(int, int, int);  //Iterates through the board array, checking for valid moves. Updates board if necessary
void updatePlayerScore(int, int);  //Player score is updated as the move is made

#endif //OTHELLO_GAME_MOVES_H
