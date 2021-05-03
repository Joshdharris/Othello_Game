//
// Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
//

#ifndef OTHELLO_GAME_GLOBALVALUES_H
#define OTHELLO_GAME_GLOBALVALUES_H

#define BDSIZE 8 // This is the size of the board. This game works for any board up to 26 x 26.

// These structs will hold the players name and score.
typedef struct Player{
    char name[20];
    int score;
} player;

player black, white;

char Board[BDSIZE][BDSIZE]; // Contains current board setup
int validMoves[BDSIZE][BDSIZE]; // Contains moves that are valid

// 2 characters which hold which colour is currently playing, and opposition colour.
extern char currCol, oppCol;


#endif //OTHELLO_GAME_GLOBALVALUES_H
