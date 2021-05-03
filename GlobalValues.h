/*
 * Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
 *
 * This contains all the global variables, etc. used across the program. They include 2 array to hold the board and any
 * valid moves, a struct for both players, and a char that holds the which colour is playing and the opponent colour.
 *
 * It also includes BDSIZE which allows you to change the size of the board to any size up to 26x26. Default is set to 8.
 *
 * I'm aware it's not generally great practice to use global variables. However as the program is not too big, and to avoid
 * having excessive function arguments where I am sending the same thing into each function, this seemed a more sensible
 * way to handle it.
 */

#ifndef OTHELLO_GAME_GLOBALVALUES_H
#define OTHELLO_GAME_GLOBALVALUES_H

#define BDSIZE 8 // This is the size of the board. This game works for any board up to 26 x 26.

// These structs will hold the players name and score.
typedef struct Player{
    char name[20];
    int score;
} player;

// 2 structs to hold the name and score of each player.
player black, white;

char Board[BDSIZE][BDSIZE]; // Contains current board setup
int validMoves[BDSIZE][BDSIZE]; // Contains moves that are valid

// 2 characters which hold which colour is currently playing, and opposition colour.
extern char currCol, oppCol;


#endif //OTHELLO_GAME_GLOBALVALUES_H
