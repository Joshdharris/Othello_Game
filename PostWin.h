//
// Created by Josh on 03/05/2021.
//

#ifndef OTHELLO_GAME_POSTWIN_H
#define OTHELLO_GAME_POSTWIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printBoard(); // (Found in Othello.c) - This prints the board
void endGame(int); // Print final results to screen, determine winner
int saveToFile(long, char); // Save final results to file

#endif //OTHELLO_GAME_POSTWIN_H
