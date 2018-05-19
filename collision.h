#ifndef collision_h
#define collision_h

#include <ncurses.h>
#include <stdio.h>
#define WIDTH 10
#define HEIGHT 20


int minDistanceRight(char piece[4][4]);

int minDistanceLeft(char piece[4][4]);

int minDistanceBottom(char piece[4][4]);

int minDistanceTop(char piece[4][4]);

int fallAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int spinAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int moveLeftAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int fallTwiceAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int moveRightAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);



#endif /* collision_h */