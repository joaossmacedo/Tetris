#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "collision.h"
#define WIDTH 10
#define HEIGHT 20
#define BLOCK '#'
#define EMPTY 0

void printGame(WINDOW * win, char board[WIDTH][HEIGHT], char piece[4][4], int positionX, int positionY){
  int x, y;
  // prints the board in the window win
  for (y = 0; y < HEIGHT ; y++) {
    for (x = 0; x < WIDTH; x++) {
      wmove(win, y, x);
      wprintw(win, "%c", board[x][y]);
    }
  }

  // prints the piece in the window win
  for (y = positionY; y < positionY + 4; y++) {
    for (x = positionX; x < positionX + 4; x++) {
      wmove(win, y, x);
      wprintw(win, "%c", piece[x - positionX][y - positionY]);
    }
  }

  wrefresh(win);
}

void create_piece(char piece[4][4]){
  int i, j;

  for (j = 0; j < 4; j++) {
      for (i = 0; i < 4; i++) {
        piece[i][j] = EMPTY;
      }
    }

  char randomic = rand() % 7;

  switch(randomic){
    case 0:
      // O
      piece[1][1] = BLOCK;
      piece[2][1] = BLOCK;
      piece[1][2] = BLOCK;
      piece[2][2] = BLOCK;
      break;
    case 1:
      // I
      piece[1][0] = BLOCK;
      piece[1][1] = BLOCK;
      piece[1][2] = BLOCK;
      piece[1][3] = BLOCK;
      break;
    case 2:
      // S
      piece[1][1] = BLOCK;
      piece[2][1] = BLOCK;
      piece[2][2] = BLOCK;
      piece[3][2] = BLOCK;
      break;
    case 3:
      // Z
      piece[1][1] = BLOCK;
      piece[2][1] = BLOCK;
      piece[0][2] = BLOCK;
      piece[1][2] = BLOCK;
      break;
    case 4:
      // T
      piece[2][1] = BLOCK;
      piece[1][2] = BLOCK;
      piece[2][2] = BLOCK;
      piece[3][2] = BLOCK;
      break;
    case 5:
      //L
      piece[1][1] = BLOCK;
      piece[1][2] = BLOCK;
      piece[2][2] = BLOCK;
      piece[3][2] = BLOCK;
      break;
    case 6:
      // J
      piece[3][1] = BLOCK;
      piece[1][2] = BLOCK;
      piece[2][2] = BLOCK;
      piece[3][2] = BLOCK;
      break;
  }
}

int destroyLine(char board[WIDTH][HEIGHT], int * score){
  /* score is passed as a pointer so i can modify it's value, i didn't return it
     because the return is already used to return the number of destroyed lines */
  int x, y, a, b;
  int canDestroyLine = 0; 
  int countDestroiedLines = 0;


  for (y = HEIGHT - 1; y >= 0; y--) {
    for (x = 0; x < WIDTH; x++) {
      if (board[x][y] == BLOCK) {
        canDestroyLine++;
      }
      if (canDestroyLine == WIDTH) {
        for (a = 0; a < WIDTH; a++) {
          board[a][y] = 0;
        }
        for (b = y; b >= 1; b--) {
          for (a = 0; a < WIDTH; a++) {
            board[a][b] = board[a][b - 1];
          }
        }
        countDestroiedLines++;
        y++;
        *score += 100;
      }
    }
    canDestroyLine = 0;
  }

  return countDestroiedLines;
}

int modifySpeed(int countDestroiedLines){
  if (countDestroiedLines < 5)       return 1000;
  else if(countDestroiedLines < 15)  return 800;
  else if(countDestroiedLines < 25)  return 700;
  else if(countDestroiedLines < 35)  return 600;
  else if(countDestroiedLines < 45)  return 500;
  else if(countDestroiedLines < 55)  return 400;
  else if(countDestroiedLines < 65)  return 325;
  else if(countDestroiedLines < 75)  return 250;
  else if(countDestroiedLines < 85)  return 200;
  else if(countDestroiedLines < 95)  return 150;
  else                      return 100;
}

int modifyLevel(int countDestroiedLines){
  if (countDestroiedLines < 5)       return 1;
  else if(countDestroiedLines < 15)  return 2;
  else if(countDestroiedLines < 25)  return 3;
  else if(countDestroiedLines < 35)  return 4;
  else if(countDestroiedLines < 45)  return 5;
  else if(countDestroiedLines < 55)  return 6;
  else if(countDestroiedLines < 65)  return 7;
  else if(countDestroiedLines < 75)  return 8;
  else if(countDestroiedLines < 85)  return 9;
  else if(countDestroiedLines < 95)  return 10;
  else                    return 11;
}

// check if it's an end game situation
int checkEndGame(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  char y, x;
  for (y = 0; y < 4; ++y){
    for (x = 0; x < 4; ++x){
      if(board[positionX + x][positionY + y] == BLOCK && piece[x][y] == BLOCK){
        return 1;
      }
    }
  }

  return 0;
}

