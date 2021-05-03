//
// Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
//

#ifndef OTHELLO_GAME_USERINPUT_H
#define OTHELLO_GAME_USERINPUT_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void initialSetup(); //Sets up the initial game board, gets user names, sets scores
void playerMove();   // Get's player's move
void clearBuffer();  // Removes excess characters stored in input buffer

#endif //OTHELLO_GAME_USERINPUT_H
