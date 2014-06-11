#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Insert variable declarations here:
#include "variables.h"
//Insert function signatures here:
#include "signatures.h"
//special character handling
#include "fancyfont.c"
//and include function files themselves:
#include "dummy.c"
//system functions
#include "system.c"
//main menu (new game,..)
#include "mainMenu.c"
//shows and updates highscores
#include "hallofshame.c"
//game-board logic (create, delete, setter, getter)
#include "board.c"
//gameflow itself (drawboard, drawcoins, input)
#include "gamefunction.c"
//shows gamerules
#include "rules.c"
//shows credits
#include "credits.c"

int main(int argc, char *argv[])
{
	FANCY_FONT = (argc>=2 && strcmp(argv[1],"FANCY")==0);
#ifdef DEBUG
	FANCY_FONT = 0;
#endif // DEBUG
	setFancy(FANCY_FONT);

	return mainMenu();
}

