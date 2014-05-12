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
//gamefunction.c
extern char name1[20];
extern char name2[20];
extern char winner[20];
extern char looser[20];
