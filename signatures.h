//dummy.c
void HelloWorld();
//mainMenu.c
void drawMainMenu();
int mainMenu();
void consoleClear();
void mainMenuReactToEnter(int pPos);
//hallofshame.c
void showHallOfShame();
void updateSaveHoS(char* victor,char* victim,int moves);
int extractMoves(char* line);
int getOldFileLength();
//board.c
int newBoard(struct board* target, unsigned int width, unsigned int height);
void clearBoard(struct board* target);
char* calcFieldAddress(struct board* target, int x, int y);
char getField(struct board* target, int x, int y);
void setField(struct board* target, int x, int y, char value);
void freeBoard(struct board* target);
void drawBoard(struct board* target);
// gamefunction.c
void gameFunction();
void playerAction();
void drawCoin(int pos, char CoinType[1]);
void startGame();
