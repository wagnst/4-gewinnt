/***Global variable declaration file***/
//dummy.c
extern int testerVariable;
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
extern struct board gameField;
extern int gameFieldWidth;
extern int gameFieldHeigth;
extern int gameFieldCreated;
extern int playersTurn; //player1 starts the game
extern int coinPosition; //where the coin is actually placed
extern char playersCoin[1]; //contains X or O

