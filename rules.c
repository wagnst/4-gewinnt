﻿#pragma once
/**
*This method adds a frame around the passed String
*is never used in current version of game
*/
void addFrame(char* word){
	//25Chars+1line break per line
	//3lines needed 3*26+1(null byte)=
	char* framePart = calloc(79,sizeof(char));
	if(framePart==NULL){

		framePart="________________________\n";
		framePart=strcat("|",word);
		//framePart=strcat(framePart);


		framePart[51]='|';
		framePart[52]='\n';
		framePart[53]='\0';
		//framePart+53="________________________\n\0";

	}else{
		//malloc failed-->fallback approach just output the supplied String without any formating
		output("%s",word);
	}

	//clean up
	flushBuffer();
	free(framePart);
}

/**
*Method to show the rules.User can leave this screen by pressing any key
*/
void showRules(){
	startBuffer(70);
	setLineAlign(0);
	output("[ RULES ]\n\n");
	setLineAlign(-1);
	output("This a implementation of the famous two player game \"Connect Four\".\nSo you'll need a friend to play this game :) To win you simply have to\nconnect four of your chips in a row. This row can be horizontal,\nvertical or diagonal,it doesn't matter as long as there are no \"enemy\"\nchips between your chips.\nThe game will automatically end if one you won and take you to the\n\"Hall of Shame\"\n\n");
	setLineAlign(0);
	output("[ Press any key to return to main menu ]\n");
	flushBuffer();
	getch();
}
