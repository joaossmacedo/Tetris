#ifndef collision_h
#define collision_h

#include "coordinates.h"
#define WIDTH 10
#define HEIGHT 20


int minDistanceRight(char piece[4][4]);

int minDistanceLeft(char piece[4][4]);

int minDistanceBottom(char piece[4][4]);

int minDistanceTop(char piece[4][4]);

int canFall(char piece[4][4], char board[WIDTH][HEIGHT], struct Coordinates position);

int canSpin(char piece[4][4], char board[WIDTH][HEIGHT], struct Coordinates position);

int canMoveRight(char piece[4][4], char board[WIDTH][HEIGHT], struct Coordinates position);

int canFallTwice(char piece[4][4], char board[WIDTH][HEIGHT], struct Coordinates position);

int canMoveLeft(char piece[4][4], char board[WIDTH][HEIGHT], struct Coordinates position);



#endif /* collision_h */