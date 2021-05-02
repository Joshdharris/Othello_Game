/*
 * Coded by Joshua Harris - 20709465 - joshua.harris@ucdconnect.ie
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define BDSIZE 8 // This is the size of the board. Works for any board up to 26 x 26.

char Board[BDSIZE][BDSIZE]; // Contains current board setup
int validMoves[BDSIZE][BDSIZE]; // Contains moves that are valid

// 2 characters which hold which colour is currently playing, and opposition colour.
char currCol = 'B';
char oppCol = 'W';

// These structs will hold the players name and score.
typedef struct Player{
    char name[20];
    int score;
} player;

player black, white; //Create a struct for black and one for white.

// Function declarations
int printBoard();
void initialSetup();
void updatePlayerScore(int, int);
int checkMoves();
int play();
void playerMove();
int move(int row, int col, int check);
void endGame(int seconds);
int saveToFile(long, char);
void clearBuffer();



int main() {

    // First get the time the game started, which is the number of seconds since the Epoch (1 Jan 1970)
    time_t seconds = time(NULL);

    initialSetup(); // Prepare the game.

    //As long as there are available moves, run the game
    int movesAvailable = 1;
    while (movesAvailable > 0) {
        movesAvailable = play();
    }

    // Print final scores and record to file the time the game started, and the winner.
    endGame(seconds);

    return 0;
}
void initialSetup(){
    /* This function will get the player names from the console.  It also resets their scores and sets up the initial board status */

    printf("Black will go first. Player 1, please input your name: ");
    fgets(black.name,sizeof(black.name)-1,stdin); // Get player 1's name.
    if (strchr(black.name, '\n') == NULL){ //If the user enters too many characters, this will remove excess from stdin.
        clearBuffer();
    }
    black.name[strcspn(black.name, "\n")] = 0;  // remove trailing new line character

    // Repeat for player 2
    printf("Player 2, please input your name: ");
    fgets(white.name,sizeof(white.name)-1,stdin);
    if (strchr(white.name, '\n') == NULL){
        clearBuffer();
    }
    white.name[strcspn(white.name, "\n")] = 0;

    // Set scores to 2
    black.score = 2;
    white.score = 2;

    // Clear the board, by blanking every element.
    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j< BDSIZE; j++) {
            Board[i][j] = ' ';
        }
    }

    // This prepares the board. The pieces are placed in the middle. (Note this game will support a board that is an
    // odd number of squares. In this case, the starting pieces will still be near the center.
    Board[BDSIZE/2 - 1][BDSIZE/2 - 1] = 'B';
    Board[BDSIZE/2 - 1][BDSIZE/2] = 'W';
    Board[BDSIZE/2][BDSIZE/2 - 1] = 'W';
    Board[BDSIZE/2][BDSIZE/2] = 'B';

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
int printBoard(){
  /* After a bit of faffing about with this, I managed to rewrite this function so that it works for any size board */

    printf("  %s: %d v %d :%s\n", black.name, black.score, white.score, white.name);

    // Print top line of board
    for (int i = 0; i< BDSIZE; i++){
        printf(" ---");
    }
    printf("\n");

    for (int j = 0; j< BDSIZE; j++){
        for (int k = 0; k < BDSIZE; k++){
            printf("| %c ", Board[j][k]); // prints each line with the values from Board array
        }
        printf("| %d", j+1);  // Prints row number
        printf("\n");
        for (int i = 0; i< BDSIZE; i++){
            printf(" ---");  //prints line under each row
        }
        printf("\n");
    }

    // prints letters for the columns
    for (int i = 0; i<BDSIZE; i++){
        printf("  %c ", 'A'+ i);
    }
    printf("\n");


    //  LISTS VALID MOVES - looks through validMoves array to check which squares are valid.
    puts("Valid Moves");
    for (int i = 0; i< BDSIZE; i++){
        for (int j = 0; j < BDSIZE; j++){
            if (validMoves[i][j] == 1){
                printf("%c%d ", j+'A',i+1);
            }
        }
    }
    printf("\n\n");

    return 0;
}
void switchPlayer() {
    // This function simply swaps the colours, which will change whose turn it is.
    if (currCol == 'B') {
        currCol = 'W';
        oppCol = 'B';
    }    // CHANGE CURRENT PLAYER TO PLAYER 2
    else {
        currCol = 'B';
        oppCol = 'W';
    }    // CHANGE CURRENT PLAYER TO PLAYER 1


}
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
int play(){
    int anyValid;

   // updatePlayerScore();
    anyValid = checkMoves(); // Check for possible moves
    if (anyValid == 0){
        printf("Sorry %s, you have no available moves\n", (currCol == 'B' ? black.name : white.name));
        switchPlayer();
        anyValid = checkMoves();
        //If this is returned 0, then we have checked for both players and there are no moves.
        if (anyValid == 0){
            return 0;
        }
    }
    printBoard();// Reprint board
    playerMove();// Ask the current player for their turn
    switchPlayer();// Switch players

    return 1;
}
void playerMove(){
    char column;
    int row, colNum, valid = 0;

    //Ask the player for their move, using ternary option.
    printf("%s, select your move:  ", (currCol == 'B' ? black.name : white.name));

    while (valid == 0){
        scanf(" %c%d", &column, &row);  // Take in user input
        clearBuffer();                  //Remove excess characters
        column = toupper(column);       //Converts lowercase character to upper-case
        row--;                          //Remove 1 from row number as the board starts from 1 but the array starts from 0.
        colNum = column - 'A';          //Convert column to a number
        if (validMoves[row][colNum] == 1){
            valid = 1;                  //Breaks the loop if the move is valid
        }
        else
            puts("Sorry, that's not a valid move. Try again");
    }

    move(row, colNum, 0); //Take the move
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
void endGame(int seconds){

    printBoard(); //Print the board again

    // Print final scores and save the results to a file.
    printf("\nGAME OVER\n");
    printf("Final scores are:\n %s: %d\n %s: %d\n", black.name, black.score, white.name, white.score);
    if (black.score > white.score){
        printf("%s wins!", black.name);
        saveToFile(seconds, 'B');
    }
    else if (black.score < white.score){
        printf("%s wins!", white.name);
        saveToFile(seconds, 'W');
    }
    else {
        printf("It's a tie.");
        saveToFile(seconds, 'T');
    }


}
int saveToFile(long gameStart, char player){

    struct tm currentTime = *localtime(&gameStart); // The time in seconds is divided into year, month, etc.

    // Open the file othello-results. If it fails, inform the user.
    FILE *fp;
    if ((fp = fopen("othello-results.txt", "a"))== NULL) {
        puts("Othello text file could not be found! Results will not be saved!");
        exit(1);
    }
    // If file is opened successfully, print the date, time and the winning player
    fprintf(fp, "On %02d-%02d-%d ", currentTime.tm_mday, currentTime.tm_mon + 1, currentTime.tm_year + 1900);
    fprintf(fp, "at %02d:%02d:%02d ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
    if (player == 'T'){ // If it's a tie
        fprintf(fp, "The match was a tie, with both players scoring %d points", black.score); // Get either player's score as they are the same.
    }
    else
        fprintf(fp, "%s won with %d points\n", (player == 'B' ? black.name : white.name), (player == 'B' ? black.score : white.score));

    fclose(fp); //Close the file
    return 0;
}
void clearBuffer(){
    // Just eats up any extra letters at the end of an input line. Helps prevent errors with users writing too much.
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}
