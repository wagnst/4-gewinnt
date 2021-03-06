﻿#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
/**
*This method manipulates the array so the left arrow (to indicate the cursor position) is added to the array.
*@param menu contains the pointer to the char-array containing main menu in it's current status
*@param pPos contains the cursor Position of the cursor
*/
void drawLeftArrow(char* menu,int pPos){
#ifndef DEBUG
			if (pPos>1) pPos--;
#endif // DEBUG
			menu[pPos*20]='-';
			menu[pPos*20+1]='>';
			menu[pPos*20+2]=' ';
}
/**
*This method manipulates the array so the right arrow (to indicate the cursor position) is added to the array.
*@param menu contains the pointer to the char-array containing main menu in it's current status
*@param pPos contains the cursor Position of the cursor
*/
void drawRightArrow(char* menu,int pPos){
#ifndef DEBUG
			if (pPos>1) pPos--;
#endif // DEBUG
			menu[(pPos+1)*20-2]='-';
			menu[(pPos+1)*20-3]='<';
			menu[(pPos+1)*20-4]=' ';
}

/**
*This method is responsible for drawing the mainMenu
*The raw form of the menu is defined here-->it can not be changed easily because the array size is dependent on the length of the String
*@param pPos current position of cursor within mainMenu
*@param mainMenu the char Array containing the mainMenu
*/
void drawMainMenu(int pPos){
	startBuffer(25);
	setLineAlign(0);
	/**
	*every Menu gets 21 Chars-->each entry starts with 3 spaces followed by the menu entry followed by some spaces to fill up the array till the end and then the line break("\n")
	*/
#ifndef DEBUG
	char mainMenu[] = "   NEW GAME        \n   RULES           \n   HALL OF SHAME   \n   CREDITS         \n   QUIT            ";
#else
	char mainMenu[] = "   NEW GAME        \n   SETTINGS        \n   RULES           \n   HALL OF SHAME   \n   CREDITS         \n   QUIT            ";
#endif // DEBUG

			drawLeftArrow(mainMenu,pPos);
			drawRightArrow(mainMenu,pPos);
			output("\n%s\n",mainMenu);

	flushBuffer();
}
/**
*
*@param con
*@param pPos
*/
int mainMenu(){
    //describes where the cursor is, default location is 0(NEW GAME)
    int pPos=0;
    //as long as this variable is one the loop won't finish
    con=1;
    animateBanner(1);
    animateBox(1,1,25,8);
    // menu loop
	while(con){
		drawMainMenu(pPos);
		switch(getch()) {
			case 72:    // key up
				pPos--;
#ifndef DEBUG
				if (pPos==1) pPos--; //settings temporarily disabled
#endif // DEBUG
				break;
			case 80:    // key down
				pPos++;
#ifndef DEBUG
				if (pPos==1) pPos++; //settings temporarily disabled
#endif // DEBUG
				break;
			case 77:    // key right
				break;
			case 75:    // key left
				break;
			case 13: // key enter
				mainMenuReactToEnter(pPos);
				break;
			case 27: //escape
			//	exit(0);
				con=0;
				break;
		}
		fflush(stdin);
		if(pPos>5){
			//cursor is "below" the menu-->get him back
			pPos=0;
		} else if(pPos<0){
			//cursor is the "over" the menu-->get him back
			pPos=5;
		}

    }
	animateBox(25,8,1,1);
    animateBanner(0);
    return 0;
}
/**
*this method handles the game flow by calling the function corresponding to the cursor posotion within the menu
*@param pPos contains the current position (0:Top,4:bottom)
*/
void mainMenuReactToEnter(int pPos){
	switch(pPos){
		case 0:
			gameFunction();
			break;
		case 1:
			startBuffer(60);
			output("Settings Menu(Dummy)\nPress any key to return to main\n");
			flushBuffer();
			getch();
			break;
		case 2:
			showRules();
			break;
		case 3:
			showHallOfShame(NO_HIGHLIGHT,0);
			break;
		case 4:
			showCredits();
			break;
		case 5:
			//end game
			con=0;
			//exit(0);
	}
}
