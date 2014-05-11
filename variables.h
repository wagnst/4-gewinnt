//dummy.c
extern int testerVariable;
//mainMenu.c
int pPos;
int con;
unsigned char userInput;
//board.c
const char FIELD_EMPTY = '.';
const char FIELD_PLAYER1 = 'X';
const char FIELD_PLAYER2 = 'O';
struct board {
	unsigned int width;
	unsigned int height;
	unsigned int numberOfFields;
	char* content;
};
extern struct board myBoard;
//added by momoXD007:
int fieldX;
int fieldY;
