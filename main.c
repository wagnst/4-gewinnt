﻿#include <stdio.h>
#include <stdlib.h>

//Insert variable declarations here:
#include "variables.h"
//Insert function signatures here:
#include "signatures.h"
//and include function files themselves:
#include "dummy.c"
#include "system.c"
#include "mainMenu.c"
#include "hallofshame.c"
#include "board.c"
#include "gamefunction.c"

int main()
{
	initBuffer(42);
	return mainMenu();
}

