#ifndef game_h
#define game_h

#include <ncurses.h>
#define WIDTH 10
#define HEIGHT 20


void printGame(WINDOW * win, char board[WIDTH][HEIGHT], char piece[4][4], int positionX, int positionY);

void createPiece(char piece[4][4]);

void spinPiece(char board[WIDTH][HEIGHT], char piece[4][4], char * positionX, char * positionY);

int destroyLine(char board[WIDTH][HEIGHT], int * score);

int modifySpeed(int countDestroiedLines);

int modifyLevel(int countDestroiedLines);

int checkEndGame(char peca [4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);



#endif /* game_h */