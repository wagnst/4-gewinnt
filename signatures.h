//dummy.c
void HelloWorld();
//system.c
void initBuffer(int maxTextLength);
void printBuffer();
void emptyBuffer();
int copyChar(char* src, char* dst);
int output(const char* input, ...);
struct LineItem* insertNewLineItem(struct LineItem* prev, struct LineItem* next, int align, int maxTextLength);
void deleteLineItem(struct LineItem* line, int deleteAllBelow);
void consoleClear();
//mainMenu.c
void drawMainMenu();
int mainMenu();
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
void throwCoin(int pos, char player[1]);
void startGame();
int neighbourRow(int x, int y ,int xMovement, int yMovement, char player);
char checkForWinner(int x, int y, char player);
