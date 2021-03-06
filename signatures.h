﻿//dummy.c
void HelloWorld();
//fancyfont.c
void setFancy();
//system.c
void initBuffer();
void startBuffer(int maxTextLength);
void flushBuffer();
int copyChar(char* src, char* dst);
int output(const char* input, ...);
struct LineItem* insertNewLineItem(struct LineItem* prev, struct LineItem* next, int maxTextLength);
void deleteLineItem(struct LineItem* line, int deleteAllBelow);
void setLineAlign(int align);
void consoleClear();
void printfBanner(int width, int startAt);
void animateBanner(int slideIn);
void printEmptyBox(int w, int h);
void animateBox(int wFrom, int hFrom, int wTo, int hTo);
void strcatRepeat(char* target, const char* source, unsigned int howOften);
char lower_to_upper(char ch1);
//mainMenu.c
void drawMainMenu();
int mainMenu();
void mainMenuReactToEnter(int pPos);
void drawLeftArrow(char* menu,int pPos);
void drawRightArrow(char* menu,int pPos);
//hallofshame.c
void showHallOfShame(int highlight,int startFrom);
int updateSaveHoS(char* victor,char* victim,int moves);
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
void drawCoin(int pos, char CoinType);
void throwCoin(int pos, char player);
void startGame();
int neighbourRow(int x, int y ,int xMovement, int yMovement, char player);
char checkForWinner(int x, int y, char player);
void clearAll();
int checkDraw();
int irand( int a, int e);
void animateFalling(struct board* currBoard,unsigned int yPos,char CoinType);
//rules.c
void showRules();
//credits.c
void showCredits();
int isChar(char toCheck);
