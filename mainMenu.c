#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

void drawMainMenu(int pPos){
	emptyBuffer();
	switch(pPos){
		case 0:
			output("-->NEW GAME<--\nSETTINGS\nRULES\nHALL OF SHAME\nQUIT\n");
			break;
		case 1:
			output("NEW GAME\n-->SETTINGS<--\nRULES\nHALL OF SHAME\nQUIT\n");
			break;
		case 2:
			output("NEW GAME\nSETTINGS\n-->RULES<--\nHALL OF SHAME\nQUIT\n");
			break;
		case 3:
			output("NEW GAME\nSETTINGS\nRULES\n-->HALL OF SHAME<--\nQUIT\n");
			break;
		case 4:
			output("NEW GAME\nSETTINGS\nRULES\nHALL OF SHAME\n-->QUIT<--\n");
			break;
		default:
			break;
	}
	flushBuffer();
}

int mainMenu(){
    //describes where the cursor is, default location is 0(NEW GAME)
    int pPos=0;
    //as long as this variable is one the loop won't finish
    con=1;
    // menu loop
	while(con){
		drawMainMenu(pPos);
		switch(getch()) {
			case 72:    // key up
				pPos--;
				break;
			case 80:    // key down
				pPos++;
				break;
			case 77:    // key right
				break;
			case 75:    // key left
				break;
			case 13: // key enter
				mainMenuReactToEnter(pPos);
				break;
			case 27: //escape
				exit(0);
		}
		fflush(stdin);
		if(pPos>4){
			//cursor is "below" the menu-->get him back
			pPos=0;
		} else if(pPos<0){
			//cursor is the "over" the menu-->get him back
			pPos=4;
		}
		output("\n");
    }
    return 0;
}

void mainMenuReactToEnter(int pPos){
	emptyBuffer();
	switch(pPos){
		case 0:
			gameFunction();
			con=0;
			break;
		case 1:
			//replace printf with corresponding call
			output("Settings Menu(Dummy)\nPress any key to return to main\n");
			flushBuffer();
			getch();
			break;
		case 2:
			//replace printf with corresponding call
			output("Rules (Dummy)\nPress any key to return to main\n");
			flushBuffer();
			getch();
			break;
		case 3:
			showHallOfShame();
			break;
		case 4:
			//end game
			con=0;
			exit(0);
	}
}
