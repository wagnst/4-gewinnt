//dummy.c
extern int testerVariable;
//mainMenu.c
int pPos;
int con;
unsigned char userInput;
//board.c
struct board {
	unsigned int width;
	unsigned int height;
	unsigned int numberOfFields;
	char* content;
};
extern struct board myBoard;
