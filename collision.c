#include <ncurses.h>
#include <stdio.h>
#include "collision.h"
#define BLOCK '#'
#define EMPTY 0
#define WIDTH 10
#define HEIGHT 20



//returs the minimum distance between the piece and the right side of the board
int minDistanceRight(char piece[4][4]){
  int dir, dir1, dir2, dir3, dir4, x, c;
  dir1 = dir2 = dir3 = dir4 = 0;

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(piece[x][0] != BLOCK && c == 0) {
      dir1++;
    }else if(piece[x][0] == BLOCK && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(piece[x][1] != BLOCK && c == 0) {
      dir2++;
    }else if(piece[x][1] == BLOCK && c == 0){
      c++;
    }
  }
  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(piece[x][2] != BLOCK && c == 0) {
      dir3++;
    }else if(piece[x][2] == BLOCK && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(piece[x][3] != BLOCK && c == 0) {
      dir4++;
    }else if(piece[x][3] == BLOCK && c == 0){
      c++;
    }
  }

  if(dir1 > dir2){
    if (dir2 > dir3){
      if(dir3 > dir4) return dir4;
      else return dir3;
    }else{
      if (dir2 > dir4) return dir4;
      else return dir2;
    }
  }else{
    if (dir1 > dir3){
      if(dir3 > dir4) return dir4;
      else return dir3;
    }else{
      if (dir1 > dir4) return dir4;
      else return dir1;
    }
  }
}

//returs the minimum distance between the piece and the left side of the board
int minDistanceLeft(char piece[4][4]){
  int esq, esq1, esq2, esq3, esq4, x, c;
  esq1 = esq2 = esq3 = esq4 = 0;

  c = 0;
  for (x = 0; x < 4; x++) {
    if(piece[x][0] != BLOCK && c == 0) {
      esq1++;
    }else if(piece[x][0] == BLOCK && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 0; x < 4; x++) {
    if(piece[x][1] != BLOCK && c == 0) {
      esq2++;
    }else if(piece[x][1] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (x = 0; x < 4; x++) {
    if(piece[x][2] != BLOCK && c == 0) {
      esq3++;
    }else if(piece[x][2] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (x = 0; x < 4; x++) {
    if(piece[x][3] != BLOCK && c == 0) {
      esq4++;
    }else if(piece[x][3] == BLOCK && c == 0){
      c++;
    }
  }

  if(esq1 > esq2){
    if (esq2 > esq3){
      if(esq3 > esq4) return esq4;
      else return esq3;
    }else{
      if (esq2 > esq4) return esq4;
      else return esq2;
    }
  }else{
    if (esq1 > esq3){
      if(esq3 > esq4) return esq4;
      else return esq3;
    }else{
      if (esq1 > esq4) return esq4;
      else return esq1;
    }
  }
}

//returs the minimum distance between the piece and the bottom of the board
int minDistanceBottom(char piece[4][4]){
  int inf, inf1, inf2, inf3, inf4, y, c;
  inf1 = inf2 = inf3 = inf4 = 0;

  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(piece[0][y] != BLOCK && c == 0) {
      inf1++;
    }else if(piece[0][y] == BLOCK && c == 0){
      c++;
    }
  }

  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(piece[1][y] != BLOCK && c == 0) {
      inf2++;
    }else if(piece[1][y] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(piece[2][y] != BLOCK && c == 0) {
      inf3++;
    }else if(piece[2][y] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(piece[3][y] != BLOCK && c == 0) {
      inf4++;
    }else if(piece[3][y] == BLOCK && c == 0){
      c++;
    }
  }

  if(inf1 > inf2){
    if (inf2 > inf3){
      if(inf3 > inf4) return inf4;
      else return inf3;
    }else{
      if (inf2 > inf4) return inf4;
      else return inf2;
    }
  }else{
    if (inf1 > inf3){
      if(inf3 > inf4) return inf4;
      else return inf3;
    }else{
      if (inf1 > inf4) return inf4;
      else return inf1;
    }
  }
}

//returs the minimum distance between the piece and the top of the board
int minDistanceTop(char piece[4][4]){
  int sup, sup1, sup2, sup3, sup4, y, c;
  sup1 = sup2 = sup3 = sup4 = 0;

  c = 0;
  for (y = 0; y < 4; y++) {
    if(piece[0][y] != BLOCK && c == 0) {
      sup1++;
    }else if(piece[0][y] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(piece[1][y] != BLOCK && c == 0) {
      sup2++;
    }else if(piece[1][y] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(piece[2][y] != BLOCK && c == 0) {
      sup3++;
    }else if(piece[2][y] == BLOCK && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(piece[3][y] != BLOCK && c == 0) {
      sup4++;
    }else if(piece[3][y] == BLOCK && c == 0){
      c++;
    }
  }

  if(sup1 > sup2){
    if (sup2 > sup3){
      if(sup3 > sup4) return sup4;
      else return sup3;
    }else{
      if (sup2 > sup4) return sup4;
      else return sup2;
    }
  }else{
    if (sup1 > sup3){
      if(sup3 > sup4) return sup4;
      else return sup3;
    }else{
      if (sup1 > sup4) return sup4;
      else return sup1;
    }
  }
}

//check if the piece can fall
int fallAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  int x, y;

  for (y = 0; y  < 4; y++) {
    for (x = 0; x < 4; x++) {
      if(piece[x][y] == BLOCK && board[x + positionX][y + positionY + 1] == BLOCK){
        return 1;
      }
    }
  }

  return 0;
}

//check if the piece can spin
int spinAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  int repositorio[4][4];
  int x, y, libera;
  libera = 0;

  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      if (piece[y][3 - x] == BLOCK) repositorio[x][y] = piece[y][3 - x];
      else repositorio[x][y] = EMPTY;
    }
  }

  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      if(repositorio[x][y] == BLOCK && board[x + positionX][y + positionY] == BLOCK)
        libera = 1;
    }
  }

  return libera;
}

//check if the piece can move left
int moveLeftAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  int a, b, libera;
  libera = 0;
  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(piece[a][b] == BLOCK && board[a + positionX - 1][b + positionY] == BLOCK){
        libera = 1;
      }
    }
  }

  return libera;
}

//check if the piece can fall twice
int fallTwiceAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  int a, b, libera;
  libera = 0;

  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(piece[a][b] == BLOCK && (board[a + positionX][b + positionY + 1] == BLOCK || board[a + positionX][b + positionY + 2] == BLOCK)){
        libera = 1;
      }
    }
  }

  return libera;
}

//check if the piece can move right
int moveRightAllowed(char piece[4][4], char board[WIDTH][HEIGHT], int positionX, int positionY){
  int a, b, libera;
  libera = 0;
  //libera a piece pra ir para a direita
  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(piece[a][b] == BLOCK && board[a + positionX + 1][b + positionY] == BLOCK){
        libera = 1;
      }
    }
  }

  return libera;
}
