//
// This contains code that I have attempted to use, but either couldn't get to work, or decided on a different method.
// It's saved her for posterity, and also so I reuse it back if I need it.
//

/*
void checkN(int i, int j, validMove valid){
    //This works for checking but is messy. Firstly it only checks for 1 colour. Secondly, it's messy.

    printf("in check N i=%d, j=%d\n", i, j);
    while ((i > 0) && (j > 0) && (Board[i-1][j-1] == oppCol)){ //must be in range
        printf("in while");
        i--;
        j--;
    }
    if (Board[i][j] != myCol){
        printf("in if");
        availableMoves(i*8+j, valid); }


    // Look for any W. If found, check below it for B
       for (int i = 1; i< BDSIZE; i++){ //Start at 1. As first row can't have further north position.
           for (int j = 0; j < BDSIZE; j++){

               if (Board[i][j] == '\0'){ //Ensures space is empty
                   if (Board[i + 1][j] == oppC) { // Identifies which spaces have a white piece on them
                       int k = i-1;
                       while(Board[k][j] == oppC){  // Keeps going south to ensure there are white pieces underneath.
                           k++;                   }
                       if((Board[k][j] != oppC) && (Board[k][j] != '\0')){  //When there are no more white pieces, we'll either have a blank square or a black one
                           printf("Found move: %d %d", i, j); //If it's black then we can go in the original position
                       }
                   }
               }
           }
       }
   }


   /*
   void check(validMove valid){
       printf("in check all\n");
       // check through entire array
       for (int i = 0; i< BDSIZE; i++) {
           for (int j = 0; j < BDSIZE; j++) {
               if (Board[i][j] == myCol){ //If the square belongs to current player
                   //Note: There must be at least 2 squares in x direction in order to capture it (one for opposing player and 1 empty)
                   if (i > 1){
                       checkN(i, j, valid);
                       if (j> 1){
                           checkNW(i, j, valid);
                       }
                       if (j < BDSIZE-2){
                           checkNE();
                       }
                   }
                   if (i < BDSIZE-2){
                       checkS();
                       if (j> 1){
                           checkSW();
                       }
                       if (j < BDSIZE-2){
                           checkSE();
                       }
                   }
                   if (j > 1){
                       checkW();
                   }
                   if (j < BDSIZE-2){
                       checkE();
                   }
               }
           }
       }
   }
   void checkNW(int i, int j, validMove valid){  //HAVE STARTPOS. KEEP IT THE SAME. HAVE CURRPOS THAT CHANGES. END AT CURRPOS.
       printf("in check NW i=%d, j=%d\n", i, j);
       while ((i > 0) && (j > 0) && (Board[i-1][j-1] == oppCol)){ //must be in range
           printf("in while");
               i--;
               j--;
       }
       if (Board[i][j] != myCol){
           printf("in if");
           availableMoves(i*8+j, valid); }
   }

   void availableMoves(int value, validMove valid){
       valid.values[valid.total] = value;
       valid.total++;

   }
   void checkNE(){};
   void checkS(){};
   void checkSW(){};
   void checkSE(){};
   void checkE(){};
   void checkW(){};
   /* PSEUDO FOR CHECKING:
    * Check each square - is it mine? - DONE
    * If no, skip - DONE
    * If yes, check each direction around square. Is it opponent's? - HALF DONE
    * If no, skip
    * If yes, continue in direction until not opponents.
    * Is it out of range? Skip
    * If it mine? skip
    * Is it empty? Record as available move.
*/

/*
//Clear the Valid Moves Array
for (int i = 0; i< BDSIZE; i++) {
    for (int j = 0; j < BDSIZE; j++) {
        validMoves[i][j] = 0;
    }
}
 */


/*INSIDE CHECK ALGORITHM
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
while ((dirRow >= 0) && (dirCol >= 0) && (dirRow < BDSIZE) && (dirCol < BDSIZE) &&
(Board[dirRow][dirCol] == oppCol)) {
dirRow = dirRow + rowPos;
dirCol = dirCol + colPos;
// If the square belongs to us, then we have a line with a blank square, a series of opponent squares, then our
// square. Thus the blank square is a valid move. We update the value on the validMoves array.
if (Board[dirRow][dirCol] == currCol) {
validMoves[i][j] = 1;
//  printf("%c%d", j+'A',i+1); // TEST - REMOVE LATER
totalMoves++;
}
}
}
}
} */

// OLD SCORE CHECKING
/* Scans through the array and updates each player's score based on number of matches in the array


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
} */