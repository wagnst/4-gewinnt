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
int playersTurn = 0; //player1 starts the game
int coinPosition = 1; //where the coin is actually placed
char playersCoin[1]; //contains X or O

//game loop
void gameFunction(){

	_Bool end = 0;

	//check that names are not the same
	/*
		strcomp results:
		0 die Strings sind gleich
		1 das erste ungleiche Zeichen in str1 ist größer als in str2
		-1 das erste ungleiche Zeichen in str1 ist kleiner als in str2
	*/
	while (strcmp(player1, player2)==0) {
		//clear the console
		consoleClear();
		player1[0] = '\0';
		player2[0] = '\0';
		//Get names of the players
		fprintf(stdout, "Please enter a name for Player 1: \n");
		fscanf(stdin, "%s", &player1);
		fprintf(stdout, "Please enter a name for Player 2: \n");
		fscanf(stdin, "%s", &player2);
	}
    //Loop till the game is done
    while(end==0){
		startGame(); // start the game flow
    }

    consoleClear();
    //print the winner of the actual game
    //printf("Congratulations! %s you made the game and defeated %s. \nPress enter to enter the famous 'Hall of Shame'...", winner, looser);
    //Hall of shame update and print hall of shame
    //hallOfShame();
    return 0;
}

void clearAll() {
	//clear board
	clearBoard(&gameField);
	freeBoard(&gameField);
	//reset some variables
	gameFieldCreated = 0; //set to 0, because board was deleted
	playersTurn = 0; //player1 starts the game
	coinPosition = 1; //where the coin is actually placed
	//clear the arrays
	memset(player1, 0, sizeof player1);
	memset(player2, 0, sizeof player2);
	return 0;
}

/*
playerAction...
	- checks which player's turn it is
	- shows X or O for a game-chip
		- player1 (X) or player2 (O) can move the coin to the left or right (check boundaries, also if row is full) and let it fall (space)
		- stop coin at highest existing coin
		- check if any user has won (function needs to be implemented)
according to https://github.com/wagnst/4-gewinnt/issues/10

*/
void playerAction() {
	//clear the console
	consoleClear();
	//check which players turn it is and sets the coin
	playersCoin[0] = '\0';
	if (playersTurn == 0) {
		memset(playersCoin, 0, sizeof playersCoin);
		printf("%s's turn\n\n", player1);
		strcat(playersCoin,"X");
	}else{
		memset(playersCoin, 0, sizeof playersCoin);
		printf("%s's turn\n\n", player2);
		strcat(playersCoin,"O");
	}
	//draw the coin
	drawCoin(coinPosition, playersCoin);
	//draw the board
	drawBoard(&gameField);
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
			//clear gamestats
			clearAll();
			//go back to menu
			return mainMenu();
			break;
		//let coin fall
		case 13: //enter key
			throwCoin(coinPosition, playersCoin);
			break;
	}
	return 0;
}

/**
* Checks if a row is full, otherwise throw coin
* @param pos position of where coin should be placed (board begins at 0 and coinpos at 1!)
*/
void throwCoin(int pos, char player[1]) {
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
		return 0;
	}else{
		//set the coin for player 1 or 2 to the lowest possible column
		if(strcmp(player, "X") == 0 ){ //if strings same player 1
			setField(&gameField,pos-1,lowestCoin,FIELD_PLAYER1);
		}else if(strcmp(player,"O") == 0 ){ //if player 2
			setField(&gameField,pos-1,lowestCoin,FIELD_PLAYER2);
		}
	}
	//switch to player 2 or back to 1
	if (playersTurn == 1)
		playersTurn = 0;
	else playersTurn = 1;
}

/**
* Draws the Coin above the board
* @param pos which position should the coin be drawn to.
* @param coinType which coin should be drawn.
*/
void drawCoin(int pos, char CoinType[1]){
	char* canvas;
	int i;
	//allocate memory for coin output
	canvas = malloc((gameFieldWidth * 4) * sizeof(char));
	//if alloc failed return
	if (canvas==NULL) {
		printf("Memory allocation for graphics failed.");
		return;
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
				strcat(canvas,CoinType);
				strcat(canvas," ");
			}else{
				//draw empty
				strcat(canvas,"    ");
			}
		}
		strcat(canvas,")\n");
		//we're done, output the whole thing
		printf("%s",canvas);
	}
	return 0;
}

/*
Function will create a new Board, clears it, draws it and calls playerAction()
*/
void startGame(){
	//checks if field already exists
	if (gameFieldCreated == 0) {
		//create new game board
		if (newBoard(&gameField,gameFieldWidth,gameFieldHeigth)) {
			//clear Board
			clearBoard(&gameField);
			//draw the board
			drawBoard(&gameField);
			//set gameFieldCreated to 1
			gameFieldCreated = 1;
		}
	}
	//call playerAction to let game begin
	playerAction();
	return 0;
}
