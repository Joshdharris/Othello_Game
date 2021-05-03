/*
 *  Created by Joshua Harris (20709465) joshua.harris@ucdconnect.ie on 03/05/2021.
 *  This contains any functions that run after the game has been won.
 */

#include "PostWin.h"
#include "GlobalValues.h"

void endGame(int seconds){

    printBoard(); //Print the board again to show final winning board layout

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
    /* Saves the results and the date & time to a file. */

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