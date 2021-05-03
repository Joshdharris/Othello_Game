//
// Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
//

#ifndef OTHELLO_GAME_MOVES_H
#define OTHELLO_GAME_MOVES_H

int checkMoves();  //Checks if a move is valid
int move(int, int, int);  //Iterates through the board array, checking for valid moves. Updates board if necessary
void updatePlayerScore(int, int);  //Player score is updated as the move is made

#endif //OTHELLO_GAME_MOVES_H
