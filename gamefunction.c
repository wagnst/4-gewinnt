#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// global variables Inga
char name1[20];
char name2[20];
char winner[20];
char looser[20];

//global variables Steffen
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
	while (strcmp(name1, name2)==0) {
		//clear the console
		consoleClear();
		name1[0] = '\0';
		name2[0] = '\0';
		//Get names of the players
		fprintf(stdout, "Please enter a name for Player 1: \n");
		fscanf(stdin, "%s", &name1);
		fprintf(stdout, "Please enter a name for Player 2: \n");
		fscanf(stdin, "%s", &name2);
	}
    //Loop till the game is done
    while(end==0){
		startGame(); // start the game flor
		//animation(); -> animation();-> Bewege Pfeil, Abwurf
		//Setze Variablen winner und looser
    }

    consoleClear();
    printf("Congratulations! %s you made the game and defeated %s. \nPress enter to enter the famous 'Hall of Shame'...", winner, looser);
    //getch();
    //hallOfShame();
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
		printf("%s's turn\n\n", name1);
		strcat(playersCoin,"X");
	}else{
		printf("%s's turn\n\n", name2);
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
		//let coin fall
		case 13: //enter key
			//Todo
			//if row not full -> coin fall
			//check if user has won
			//switch to other player
			break;
	}
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
}
