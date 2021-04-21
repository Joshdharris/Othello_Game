/*
 * Coded by Joshua Harris - 20709465 - joshua.harris@ucdconnect.ie
 *
 *
 * Alteration to consider:
 * Makes sure character name is not too long in initialInput
 * Change user input coordinates to allow for changing board size. This will mean changing the print function and stuff
 * Change user input of co-ordinates to prevent too long string
 *
 *
 *
 */

#include <stdio.h>

#define BDSIZE 8  //This is the size of the board. We start with an 8 by 8.

char Board[BDSIZE][BDSIZE]; // Contains current board setup
int validMoves[BDSIZE][BDSIZE]; //
char currCol = 'B';
char oppCol = 'W';

// These structs will hold the players name and score.
typedef struct Player{
    char name[20];
    int score;
} player;

//MAY HAVE TO MOVE THIS INTO MAIN, CHECK AS CODE PROGRESSES.
player black, white; //Create a struct for black and one for white.

int printBoard();
void initialSetup();
void updatePlayerScore();
int checkMoves();
int play();
void playerMove();
void move(int row, int col);
void endGame();
void clearBuffer();

int main() {

    int movesAvailable = 1;

    initialSetup(); // Prepare the game.
    printBoard(); // Print the board

    //As long as there are available moves, run the game
    while (movesAvailable > 0) {
        movesAvailable = play();
    }

    endGame(); // Print final scores

    return 0;
}
void initialSetup(){
    /* This function will get the player names from the console  It also resets their scores and sets up the initial board status */

    printf("Black will go first. Player 1, please input your name: ");
    fgets(black.name,19,stdin);
    clearBuffer();
    printf("Player 2, please input your name: ");
    fgets(white.name,19,stdin);
    clearBuffer();

    black.score = 2;
    white.score = 2;

    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j< BDSIZE; j++) {
            Board[i][j] = ' ';
        }
    }

    Board[3][3] = 'B';
    Board[3][4] = 'W';
    Board[4][3] = 'W';
    Board[4][4] = 'B';

}
void updatePlayerScore(){
    /* Scans through the array and updates each player's score based on number of matches in the array */
    black.score = 0;
    white.score = 0;

    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j < BDSIZE; j++){
            if (Board[i][j] == 'B'){
                black.score++;
            }
            if (Board[i][j] == 'W'){
                white.score++;
            }
        }
    }
}
int printBoard(){
  /* This function will print out the board, using the values saved within the Board array */

  printf("  %s: %d v %d :%s", black.name, black.score, white.score, white.name);

    for (int i = 0; i< BDSIZE; i++){
        printf("\n   --- --- --- --- --- --- --- ---\n");
        printf("%d |", i+1);
        for (int j = 0; j < BDSIZE; j++){
            printf(" %c |", Board[i][j]);
        }
    }
    printf("\n   --- --- --- --- --- --- --- ---\n");
    printf("    A   B   C   D   E   F   G   H\n\n");

    return 0;
}
void switchPlayer() {
    // This function simply swaps the colours, which will change whose turn it is.
    if (currCol == 'B') {
        currCol = 'W';
        oppCol = 'B';
        // CHANGE POINTER TO PLAYER 2
    }
    else{
        currCol = 'B';
        oppCol = 'W';
    }    // CHANGE POINTER TO PLAYER 1


}
int checkMoves() {
    /* Well this function is a ball of fun! So let's walk through what it does. Basically it checks every single value
     * in the array to see if it's valid. How it does is commented below */

    int totalMoves = 0; //Keeps track of total number of available moves.
    // Loop through every square in the Board array
    for (int i = 0; i < BDSIZE; i++) {
        for (int j = 0; j < BDSIZE; j++) {
            // If the square is empty, we check every square around it. rowPos and rowCol will start from the previous row/column
            // and check previous, current and next square for each row/column.
            if (Board[i][j] == ' ') {
                //  printf("B%d%d, ", i+1, j+1);
                for (int rowPos = -1; rowPos <= 1; rowPos++) {
                    for (int colPos = -1; colPos <= 1; colPos++) {
                        // We make sure that each square being checked is on the board. The final bracket ensures we aren't checking the
                        // same square (which will be at rowPos = 0, colPos = 0)
                        if ((rowPos + i >= 0) && (rowPos + i < BDSIZE) && (colPos + j >= 0) && (colPos + j < BDSIZE) &&
                            !(rowPos == 0 && colPos == 0)) {
                            // As long as it's a valid square we check if it belongs to the opponent. If it does, there is a potential valid move.
                            if (Board[rowPos + i][colPos + j] == oppCol) {
                                // The square belongs to the opponent. We need to keep checking in that direction. Save the position of the checked square.
                                int dirRow = rowPos + i;
                                int dirCol = colPos + j;
                                // While ensuring the squares we are checking are on the board and belong to our opponent, we continue checking in
                                // that direction
                                while ((dirRow > 0) && (dirCol > 0) && (dirRow < BDSIZE) && (dirCol < BDSIZE) &&
                                       (Board[dirRow][dirCol] == oppCol)) {
                                    dirRow = dirRow + rowPos;
                                    dirCol = dirCol + colPos;
                                    // If the square belongs to us, then we have a line with a blank square, a series of opponent squares, then our
                                    // square. Thus the blank square is a valid move. We update the value on the validMoves array.
                                    if (Board[dirRow][dirCol] == currCol) {
                                        validMoves[i][j] = 1;
                                        totalMoves++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
                // If the square isn't empty, it's not a valid move. Change the validMoves array to reflect this.
            else
                validMoves[i][j] = 0;
        }
    }
    return totalMoves;
}
int play(){
    int anyValid;
    anyValid = checkMoves(); // Check for possible moves
    if (anyValid == 0){
        if (currCol == 'B'){
            printf("Sorry %s, you have no available moves\n", black.name);
        }
        else
            printf("Sorry %s, you have no available moves\n", white.name);
        switchPlayer();
        anyValid = checkMoves();
        //If this is returned 0, then we have checked for both players and there are no moves.
        if (anyValid == 0){
            return 0;
        }
    }
    playerMove();// Ask the current player for their turn
    // Do player's turn
    updatePlayerScore();
    printBoard();// Reprint board
    switchPlayer();// Switch Players?? (Or in main?)

    return 1;
}
void playerMove(){
    char column;
    int row;
    int colNum;
    int valid = 0;
    //Ask the player for their move.
    if (currCol == 'B')
        printf("%s, select your move:  ", black.name);
    else
        printf("%s, select your move:  ", white.name);

    while (valid == 0){
        scanf(" %c%d", &column, &row);
        clearBuffer();
        while (column < 'A' || column > 'H' || row < 1 || row > 8) {
            printf("Sorry, please input your co-ordinates in a format like this: A1\n");
            scanf(" %c%d", &column, &row);
            clearBuffer();
        }
        //Remove 1 from row number as the board starts from 1 but the array starts from 0.
        row--;
        //Convert column to a number
        colNum = column - 'A';
        if (validMoves[row][colNum] == 1){
            valid = 1;
        }
        else
            puts("Sorry, that's not a valid move. Try again");
    }

    move(row, colNum); //Take the move
}
void move(int row, int col){

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
                    // While ensuring the squares we are checking are on the board and belong to our opponent, we continue checking in
                    // that direction
                    while ((dirRow > 0) && (dirCol > 0) && (dirRow < BDSIZE) && (dirCol < BDSIZE) &&
                           (Board[dirRow][dirCol] == oppCol)) {
                        dirRow = dirRow + rowPos;
                        dirCol = dirCol + colPos;
                        // If the square belongs to us, then we have a line with a blank square, a series of opponent squares, then our
                        // square. We now go back through the squares and change them to our colour.
                        if (Board[dirRow][dirCol] == currCol) {
                            while (!(dirRow == row && dirCol == col)){
                                dirRow = dirRow - rowPos;
                                dirCol = dirCol - colPos;
                                Board[dirRow][dirCol] = currCol;
                            }
                        }
                    }
                }
            }
        }
    }
}
void endGame(){

    printf("\n\nGAME OVER\n");
    printf("Final scores are:\n %s: %d\n %s: %d\n", black.name, black.score, white.name, white.score);
    if (black.score > white.score){
        printf("%s wins!", black.name);
    }
    else if (black.score < white.score){
        printf("%s wins!", white.name);
    }
    else
        printf("It's a tie.");
}
void clearBuffer(){
    // Just eats up any extra letters at the end of an input line. Helps prevent errors with users writing too much.
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}
