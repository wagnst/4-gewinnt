//dummy.c
void HelloWorld();
//mainMenu.c
void drawMainMenu();
int mainMenu();
void consoleClear();
void mainMenuReactToEnter();
//hallofshame.c
void showHallOfShame();
void updateSaveHoS(char* victor,char* victim,int moves);
int extractMoves(char* line);
int getOldFileLength();
//board.c
int newBoard(struct board* target, unsigned int width, unsigned int height);
void clearBoard(struct board* target);
