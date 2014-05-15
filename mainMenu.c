#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

void drawMainMenu(int pPos){
    consoleClear();
 switch(pPos){
    case 0:
        printf("-->NEW GAME<--\nSETTINGS\nRULES\nHALL OF SHAME\nQUIT\n");
        break;
    case 1:
        printf("NEW GAME\n-->SETTINGS<--\nRULES\nHALL OF SHAME\nQUIT\n");
        break;
    case 2:
        printf("NEW GAME\nSETTINGS\n-->RULES<--\nHALL OF SHAME\nQUIT\n");
        break;
    case 3:
        printf("NEW GAME\nSETTINGS\nRULES\n-->HALL OF SHAME<--\nQUIT\n");
        break;
    case 4:
        printf("NEW GAME\nSETTINGS\nRULES\nHALL OF SHAME\n-->QUIT<--\n");
        break;
    default:
    	break;
 }
}

int mainMenu(){
    //describes where the cursor is, default location is 0(NEW GAME)
    pPos=0;
    //as long as this variable is one the loop won't finish
    con=1;
    // menu loop
	while(con){
		drawMainMenu(pPos);
		//Windows implementation:
		#ifdef _WIN32
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
				mainMenuReactToEnter();
				break;
			case 27: //escape
				exit(0);
		}
		//other systems
		#else
		scanf("%c", &userInput);
		switch(userInput){
			//dummy for key up
			case 'w':
				pPos--;
				break;
			//dummy for key down
			case 's':
				pPos++;
				break;
			//dummy for return key
			case 'e':
				mainMenuReactToEnter();
				break;
		}
		#endif
		if(pPos>4){
			//cursor is "below" the menu-->get him back
			pPos=0;
		} else if(pPos<0){
			//cursor is the "over" the menu-->get him back
			pPos=4;
		}
		printf("\n");
    }
}

void consoleClear(){
	//should clear the console on most plattforms
	#ifdef _WIN32
	//detected windows System (both 32 and 64bit)-->use windows clear
		system("CLS");
	#else
	//detected other (non windows) System-->unse Unix-clear
		system("clear");
	#endif

}

void mainMenuReactToEnter(){
	switch(pPos){
		case 0:
			consoleClear();
			//replace printf with corresponding call
			//printf("Starting new Game(Dummy)\nPress any key to return to main\n");
			gameFunction();
			con=0;
			break;
		case 1:
			 consoleClear();
			//replace printf with corresponding call
			printf("Settings Menu(Dummy)\nPress any key to return to main\n");
			break;
		case 2:
			 consoleClear();
			//replace printf with corresponding call
			printf("Rules (Dummy)\nPress any key to return to main\n");
			break;
		case 3:
			 consoleClear();
			//replace printf with corresponding call
		    //printf("Hall of Shame (Dummy)\nPress any key to return to main\n");
			showHallOfShame();
			con=0;
			break;
		case 4:
			//end game
			con=0;
			exit(0);
		}
}
