#ifndef game_h
#define game_h

#include <ncurses.h>
#define WIDTH 10
#define HEIGHT 20


void printGame(WINDOW * win, char board[WIDTH][HEIGHT], char piece[4][4], int positionX, int positionY);

void create_piece(char piece[4][4], char auxPiece[4][4]);

int destroyLine(char board[WIDTH][HEIGHT], long * score);

int modifySpeed(int countDestroiedLines);

int modifyLevel(int countDestroiedLines);

int endGame(char peca [4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);



#endif /* game_h */