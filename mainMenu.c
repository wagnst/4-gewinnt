#pragma once
void drawMainMenu(int pPos){
    consoleClear();
 switch(pPos){
    case 0:
        printf("-->NEW GAME<--\nSETTINGS\nRULES\nHALL OF SHAME\nQUIT\n");break;
    case 1:
        printf("NEW GAME\n-->SETTINGS<--\nRULES\nHALL OF SHAME\nQUIT\n");break;
    case 2:
        printf("NEW GAME\nSETTINGS\n-->RULES<--\nHALL OF SHAME\nQUIT\n");break;
    case 3:
        printf("NEW GAME\nSETTINGS\nRULES\n-->HALL OF SHAME<--\nQUIT\n");break;
    case 4:
        printf("NEW GAME\nSETTINGS\nRULES\nHALL OF SHAME\n-->QUIT<--\n");break;
    default:break;
 }
}
/**
void primitiveWait(){
 //primitive wait method
 char x;
 scanf("a %c",&x);
}
*/

int mainMenu(){
    //describes where the cursor is, default location is 0(NEW GAME)
    pPos=0;
    //as long as this variable is one the loop won't finish
    con=1;
	/**
        printf("Select mode f=fast,n=normal,c=custom\n");
        char mode;
        scanf("%c",&mode);
	*/
	while(con){
         drawMainMenu(pPos);
        userInput="";
        scanf("%c", &userInput);
        switch(userInput){
            //dummy for key up
            case 'u':
                pPos--;
                break;
            //dummy for key down
            case 'd':
                pPos++;
                break;
            //dummy for return key
            case 'e':
                switch(pPos){
                case 0:
                    consoleClear();
                    //replace printf with corresponding call
                    printf("Starting new Game(Dummy)\nPress any key to return to main\n");
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
                    printf("Hall of Shame (Dummy)\nPress any key to return to main\n");
                   //showHallOfShame();
                    break;
                case 4:
                     //end game
                     con=0;
                    break;
                }
                break;


        }

        if(pPos>4){
            //cursor is "below" the menu-->get him back
            pPos=0;
        } else if(pPos<0){
            //cursor is the "over" the menu-->get him back
            pPos=4;
        }
        printf("\n");
      //  system("clear");
    }
    printf("Programm ended \n");
}
void consoleClear(){
	//should clear the console on most plattforms
	#ifdef win32
	//detected windows System-->use windows clear
		system("CLS");
	#else
	//detected other (non windows) System-->unse Unix-clear
		system("clear");
	#endif

}

