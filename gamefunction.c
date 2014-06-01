#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// global variables
char player1[20];
char player2[20];

struct board gameField;
int gameFieldWidth = 7;
int gameFieldHeigth = 6;
int gameFieldCreated = 0;
int coinPosition = 1; //where the coin is actually placed
int playersTurn;
char playersCoin; //contains X or O
char victor;
int moves;
int end = 0;

/**
* gameFunction first forces users to enter their names and checks them for different mistakes
* after that startGame() is called within the gameloop, which processes the main game flow
* last but not least we check for a winner or check for draw and continue to Hall of Shame.
* @return no return because of void
*/
void gameFunction(){
	moves = 0;
	playersTurn = irand(0,1);
	char keyStrokeName[2];
	keyStrokeName[1] = '\0';
	player1[0] = '\0';
	player2[0] = '\0';
	/*
		player1 name
		loop as long player did not press enter
	*/
	do {
		//check length
		if (strlen(player1)>=19)
			break;
		//buffer
		startBuffer(50);
		output("Please enter a name for Player 1: \n");
		output("> %s_\n", player1);
		//flush buffer
		flushBuffer();
		//wait for a new char and give it to var
		keyStrokeName[0] = getch();
		//check for special inputs
		if ((keyStrokeName[0] == '\b') && (strlen(player1)) > 0) {
			//if backspace was entered
			player1[strlen(player1)-1] = '\0'; //set nilbyte to pointer-1
		}
		else if (keyStrokeName[0] == '\r') {} //if enter do nothing
		else if ((keyStrokeName[0] == '\b') && (strlen(player1)) == 0) {} //if string empty and backspace entered do nothing
		else {
			keyStrokeName[0] = lower_to_upper(keyStrokeName[0]);
			strcat(player1, keyStrokeName);
		}
	} while(((keyStrokeName[0] != '\r') && (player1[0] != '\0') && !(strlen(player1)>15)) || (strlen(player1)<3));
	/*
		player2 name
		loop as long player did not press enter
	*/
	do {
		//check length
		if (strlen(player1)>=19)
			break;
		//buffer
		startBuffer(55);
		output("Please enter a name for Player 1: \n");
		output("%s\n\n", player1);
		output("Please enter a name for Player 2: \n");
		output("> %s_\n", player2);
		//flush buffer
		flushBuffer();
		//wait for a new char and give it to var
		keyStrokeName[0] = getch();
		//check for special inputs
		if ((keyStrokeName[0] == '\b') && (strlen(player2)) > 0) {
			//if backspace was entered
			player2[strlen(player2)-1] = '\0'; //set nilbyte to pointer-1
		}
		else if (keyStrokeName[0] == '\r') {} //if enter do nothing
		else if ((keyStrokeName[0] == '\b') && (strlen(player2)) == 0) {} //if string empty and backspace entered do nothing
		else {
			keyStrokeName[0] = lower_to_upper(keyStrokeName[0]);
			strcat(player2, keyStrokeName);
		}
	} while(((keyStrokeName[0] != '\r') && (player2[0] != '\0') && !(strlen(player2)>15)) || (strlen(player2)<3));
	//check that player1 and player2 names are not the same
	if (strcmp(player1, player2)==0) {
		player2[(strlen(player2))] = '1'; // add a symbolic 1 to the end of the name ;-)
		player2[(strlen(player2))+1] = '\0';
	}
	//start buffer for completion
	startBuffer(55);
	output("Thank you %s and %s! The game will start now.\n\nPlease press enter to continue...", player1, player2);
	flushBuffer();
	//wait for a key
	getch();
    //Loop till the game is done
    int winnerLine =NO_HIGHLIGHT;
    while(end == 0){
		// start the game flow
		startGame();
		//check for winners or draw
		if( victor == FIELD_PLAYER1){
			end = 1;
			moves =  (moves/2)+(moves%2);
			consoleClear();
			startBuffer(50);
			drawBoard(&gameField);
			winnerLine = updateSaveHoS(player1,player2,moves);
			//output victor
			output("%s has won!\n\n", player1);
			output("Press any key to continue to Hall of Shame...\n");
			//show all
			flushBuffer();
			//wait for any keystroke
			getch();
			//continue to hall of shame
			showHallOfShame(winnerLine,winnerLine-4);
		}
		else if( victor == FIELD_PLAYER2){
			end = 1;
			moves = (moves/2)+(moves%2);
			consoleClear();
			startBuffer(50);
			drawBoard(&gameField);
			winnerLine = updateSaveHoS(player2,player1,moves);
			//output victor
			output("%s has won!\n\n", player2);
			output("Press any key to continue to Hall of Shame...\n");
			//show all
			flushBuffer();
			//wait for any keystroke
			getch();
			//continue to hall of shame
			showHallOfShame(winnerLine, winnerLine-4);
		}
		if(checkDraw() == 0){
			end = 1;
			consoleClear();
			startBuffer(50);
			drawBoard(&gameField);
			//output draw
			output("Game ended with a draw...\n\n");
			output("Press any key to continue to Hall of Shame...\n");
			//show all
			flushBuffer();
			//wait for any keystroke
			getch();
			//continue to hall of shame
			showHallOfShame(NO_HIGHLIGHT,0);
		}
    }

    //free our game-board
    clearAll();
    return;
}

/**
* Clears all elements which are used within the gameflow
* Board, loop condition, positions
* @return no return because of void
*/
void clearAll() {
	//clear board
	clearBoard(&gameField);
	freeBoard(&gameField);
	end = 0;
	//reset some variables
	victor = '\0';
	gameFieldCreated = 0; //set to 0, because board was deleted
	playersTurn = 0; //player1 starts the game
	coinPosition = 1; //where the coin is actually placed
	return;
}

/**
* playerAction()
*	- checks which player's turn it is
*	- shows X or O for a game-chip
*		- player1 (X) or player2 (O) can move the coin to the left or right (check boundaries, also if row is full) and let it fall (space)
*		- stop coin at highest existing coin
*		- check if any user has won (function needs to be implemented)
* according to https://github.com/wagnst/4-gewinnt/issues/10
* @return no return because of void
*/
void playerAction() {
	int i = 0;
	char *spaceBetweenNames;
	spaceBetweenNames = malloc((gameFieldWidth * 3) * sizeof(char));
	//if alloc failed return
	if (spaceBetweenNames==NULL) {
		exit(EXITCODE_OUTOFMEMORY);
	}
	//check which players turn it is and sets the coin
	playersCoin = '\0';
	//output buffer
	startBuffer(50);
	if (playersTurn == 0) {
		playersCoin = FIELD_EMPTY;
		output("%s's turn\n\n", player1);
		playersCoin = FIELD_PLAYER1;
	}else{
		//set nilbyte
		spaceBetweenNames[0] = '\0';
		do{
			//as long as length of name and space not bigger than overall gamefield, add space before name
			if ((strlen(player2)+strlen(spaceBetweenNames))<gameFieldWidth*3)
				strcat(spaceBetweenNames, " ");
				i++;
		}while(i<=gameFieldWidth*3);

		output("%s%s's turn\n\n", spaceBetweenNames, player2);
		playersCoin = FIELD_PLAYER2;
	}
	//draw the coin
	drawCoin(coinPosition, playersCoin);
	//draw the board
	drawBoard(&gameField);
	//end buffer
	flushBuffer();
	userInput = getch();
	switch(userInput){
		//dummy for key left
		case 75: //left
			if (coinPosition > 1)
				coinPosition--;
			break;
		//dummy for key right
		case 77: //right
			if (coinPosition < gameFieldWidth)
				coinPosition++;
			break;
		case 27: //escape
			//go back to menu
			end = 1;
			break;
		//let coin fall
		case 13: //enter key
			throwCoin(coinPosition, playersCoin);
			moves++;
			break;
	}
	free(spaceBetweenNames);
}

/**
* Checks if a row is full, otherwise throw coin
* @param pos position of where coin should be placed (board begins at 0 and coinpos at 1!)
* @param player Char which contains X oder O according to the player
* @return no return because of void
*/
void throwCoin(int pos, char player) {
	int lowestCoin = 0, i;
	//get the lowest field
	// LOOP DOWN if found, set lowestCoin
	for(i = 0; i <= gameFieldHeigth-1; i++) {
		// if we found an empty field, leave this loop and set lowest coin
		// to the found field, so that game flow can set the next coin here
		if (getField(&gameField,pos-1,i) == FIELD_EMPTY){
			lowestCoin = i;
			break;
		}
	}
	//check if most upper field is filled with coin
	if (getField(&gameField,pos-1,gameFieldHeigth-1)==FIELD_PLAYER2 || getField(&gameField,pos-1,gameFieldHeigth-1)==FIELD_PLAYER1) {
		return;
	}else{
		//set the coin for player 1 or 2 to the lowest possible column
		if(player == FIELD_PLAYER1){
			setField(&gameField,pos-1,lowestCoin,FIELD_PLAYER1);
			//added looking for winner here
			victor = checkForWinner(pos-1, lowestCoin,FIELD_PLAYER1);
		}else if(player == FIELD_PLAYER2){ //if player 2
			setField(&gameField,pos-1,lowestCoin,FIELD_PLAYER2);
			victor = checkForWinner(pos-1, lowestCoin,FIELD_PLAYER2);
		}
	}
	//switch to player 2 or back to 1
	if (playersTurn == 1)
		playersTurn = 0;
	else playersTurn = 1;
	return;
}

/**
* Draws the Coin above the board
* @param pos which position should the coin be drawn to.
* @param coinType which coin should be drawn.
* @return no return because of void
*/
void drawCoin(int pos, char CoinType){
	int i;
	char *canvas;
	canvas = malloc((gameFieldWidth * 4) * sizeof(char));
	//if alloc failed return
	if (canvas==NULL) {
		exit(EXITCODE_OUTOFMEMORY);
	}
	//writing-to-canvas setup (clear string)
	canvas[0] = '\0';
	//keep boundaries
	if (pos < gameFieldWidth || pos > 1) {
		strcat(canvas,"(");
		for(i = 1; i <= gameFieldWidth; i++) {
			//if the coin should be placed draw it
			if (i == pos) {
				strcat(canvas," ");
				if(CoinType == FIELD_PLAYER1){
					strcat(canvas,"X");
				}else{
					strcat(canvas,"O");
				}

				strcat(canvas," ");
			}else{
				//draw empty
				strcat(canvas,"    ");
			}
		}
		strcat(canvas,")\n");
		//we're done, output the whole thing
		output("%s",canvas);
	}
	//free memory
	free(canvas);
	return;
}

/**
* Function will create a new Board, clears it and calls playerAction()
* @return no return because of void
*/
void startGame(){
	//checks if field already exists
	if (gameFieldCreated == 0) {
		//create new game board (includes clear)
		if (newBoard(&gameField,gameFieldWidth,gameFieldHeigth)) {
			//set gameFieldCreated to 1
			gameFieldCreated = 1;
		}
	}
	//call playerAction to let game begin
	playerAction();
}


/**
* Look for a winner of the current game.
* First vertically, then horizontally and then the 2 diagonal rows.
* lineCount is the number of Coins which are neighbours.
* @param x X-Position of last dropped coin.
* @param y Y-Position of last dropped coin.
* @param player The last coin which was dropped to the game, as the starting point of this algorithm.
* @return The winnig coin type is returned X or O.
*/
char checkForWinner(int x, int y, char player){
	 // horizontal check first right then left summarized together
	 int lineCount = 0;
	 lineCount = 1 + neighbourRow(x+1,y,+1,0,player) + neighbourRow(x-1,y,-1,0,player);
	 if(lineCount >= 4){
		return player;
	 }
	 else{
		lineCount=0;
	 }

	 // vertical check first up and then down summarized together
	 lineCount = 1 + neighbourRow(x,y+1,0,1,player) + neighbourRow(x,y-1,0,-1,player);
	 if(lineCount >= 4){
		return player;
	 }
	 else{
		lineCount=0;
	 }

	 // diagonal checks

	 // first variant /
	 lineCount = 1 + neighbourRow(x-1,y+1,-1,1,player) + neighbourRow(x+1,y-1,1,-1,player);
	 if(lineCount >= 4){
		return player;
	 }
	 else{
		lineCount=0;
	 }
	 //second variant
	 lineCount = 1 + neighbourRow(x+1,y+1,1,1,player) + neighbourRow(x-1,y-1,-1,-1,player);
	 if(lineCount >= 4){
		return player;
	 }
	 else{
		lineCount=0;
	 }
	return FIELD_EMPTY;

}
/**
* Recursive function to sum up the coins which are connected in a row.
* @param x X-Position of last dropped coin.
* @param y Y-Position of last dropped coin.
* @param xMovement This is used to build a "vector"
* @param yMovement This is used to build a "vector"
* @param player The cointype to count in a row.
* @return Number of coins which are connected.
*/
int neighbourRow(int x, int y ,int xMovement, int yMovement, char player){
	if (getField(&gameField,x,y) == player){
		return 1 + neighbourRow(x+xMovement,y+yMovement,xMovement,yMovement,player);
	}
	else{
		return 0;
	}
}

/**
* Checks if the board is full. Only possible if nobody has won earlier.
* @return 1 for game can go on - 0 for game ended with a draw
*/
int checkDraw(){
	int i =0;
	for(i=0;i<gameFieldWidth;i++){
		if(getField(&gameField,i,gameFieldHeigth-1) == FIELD_EMPTY){
			return 1;
		}
	}
	return 0;
}
/** Get random integer a<=x<=e
* @param a Lowest value for x.
* @param e Highest value for x.
* @return Random integer
*/
int irand( int a, int e){
    double r = e - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}


/**
*this Method animates a falling Coin by moving the coin one field lower than wait and repeat this until there's another coin or it reaches the end of the board
* This Method fully cleans the board up after finishing-->means: after execution the board will look like nothing ever happened. The animated coin is not saved permanetly saved on the board
* @param xPos the row in which the coin is going to fall
* @param currBoard the board with the current game state
* @param CoinType variable to determine if the current Player has 'X' or '0' as Coin
*/
void animateFalling(struct board* currBoard,unsigned int xPos,char CoinType){
	//determing which type of coin is going to fall
	char coin;
	if(CoinType == FIELD_PLAYER1){
		coin='X';
	}else{
		coin='O';
	}





	unsigned int currY=currBoard->height-1;
	char* old;
	//(getField(currBoard,xPos,currY)!=FIELD_EMPTY)&&
	while((currY!=0)){
		//no deletions possible at first run of loop
		if(currY!=currBoard->height-1){
			//delete coin one field above
			old=calcFieldAddress(currBoard,xPos,currY+1);
			old=&FIELD_EMPTY;
		}
		//setting coin one field lower
		char* curr=calcFieldAddress(currBoard,xPos,currY);
			curr=&coin;
		currY--;

		drawBoard(currBoard);
		//improvised wait Method
		int x=0;
		for(x=0;x<1000000;x++){
			//funny nothing will ever happen here :D
			x=x;
		};


	}
	/**final clean up
	*deleting the last coin
	*if this last part of the code will be deleted the last position of the coin will be permantely saved on the supplied board
	**/
	old=calcFieldAddress(currBoard,xPos,currY);
//	&old=FIELD_EMPTY;
	old=FIELD_EMPTY;
	//return;

}

