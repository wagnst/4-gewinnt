﻿/***Global variable declaration file***/
//EXITCODES
const int EXITCODE_OUTOFMEMORY = 13;
const int EXITCODE_BUFFERERROR = 17;
const int EXITCODE_WINDOWERROR = 23;
//dummy.c
extern int testerVariable;
//fancyfont.c
/*for font constants see file*/
extern int FANCY_FONT;
//system.c
struct LineItem {
	int length;
	int byteSize;
	int align;
	struct LineItem* prev;
	struct LineItem* next;
	char* text;
};
struct OutBuffer {
	struct LineItem* first;
	struct LineItem* last;
	int maxTextLength;
	int lineCount;
	int vAlign;
	int hAlign;
};
const int OUTPUT_MAXBUFFER = 4096;
extern struct OutBuffer display;
const int UTF_MULTIPLIER = 8;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;
extern int consoleBufferWidth;
extern int consoleBufferHeight;
//mainMenu.c
int con;
unsigned char userInput;
//board.c
const char FIELD_EMPTY = '.';
const char FIELD_PLAYER1 = 'X';
const char FIELD_PLAYER2 = 'O';
const char FIELD_OUTOFBOUNDS = '\0';

struct board {
	unsigned int width;
	unsigned int height;
	unsigned int numberOfFields;
	char* content;
};
extern struct board myBoard;
//gamefunction.c
extern char name1[20];
extern char name2[20];
extern char winner[20];
extern char looser[20];
extern char victor;
extern struct board gameField;
extern int gameFieldWidth;
extern int gameFieldHeigth;
extern int gameFieldCreated;
extern int playersTurn; //player1 starts the game
extern int coinPosition; //where the coin is actually placed
extern char playersCoin; //contains X or O
extern int moves;
extern int end;
//HallOfShame.c
const int  HOS_LINES = 10;
const int  NO_HIGHLIGHT = -1;
