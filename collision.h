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

int canFall(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int canSpin(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int canMoveRight(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int canFallTwice(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);

int canMoveLeft(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY);



#endif /* collision_h */