/*
 * Coded by Joshua Harris - 20709465 - joshua.harris@ucdconnect.ie
 *
 */

#include <stdio.h>

char Board[8][8];

typedef struct Player{
    char name[30];
    int score;
} player;
int printBoard();
void getPlayerNames(player*, player*);

int main() {
    player p1, p2;


    getPlayerNames(&p1, &p2);
    printBoard(&p1, &p2);
    return 0;
}

void getPlayerNames(player *p1, player *p2){
    /* This function will get the player names from the console  It saves the names into the structs and cl*/

    printf("Black will go first. Player 1, please input your name: ");
    scanf("%s", p1->name);
    // CODE TO ENSURE MAX 30 CHARACTERS
    printf("Player 2, please input your name: ");
    scanf("%s", p2->name);

    p1->score = 0;
    p2->score = 0;
}

int printBoard(player *p1, player *p2){
  /* This function will print out the board, using the values saved within the Board array */

  printf("  %s: %d v %d %s", p1->name, p1->score, p2->score, p2->name);


    for (int i = 0; i< 8; i++){
        printf("\n   --- --- --- --- --- --- --- ---\n");
        printf("%d |", i+1);
        for (int j = 0; j < 8; j++){
            printf(" %c |", Board[i][j]);
        }
    }
    printf("\n   --- --- --- --- --- --- --- ---\n");
    printf("    A   B   C   D   E   F   G   H");

    return 0;
}
