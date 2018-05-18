#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LARG 10
#define ALT 20
#define PEDRA '*'
#define BRANCA 0


//imprime a peca e o tabuleiro
void imprimirJogo(WINDOW * win, char tabuleiro[LARG][ALT], char peca[4][4], int eixoX, int eixoY){
  int x, y;
  //imprime a matriz na janela win
  for (y = 0; y < ALT ; y++) {
    for (x = 0; x < LARG; x++) {
      //move o cursor na janela win
      wmove(win, y, x);
      wprintw(win, "%c", tabuleiro[x][y]);
    }
  }

  //imprime a peca na janela win
  for (y = eixoY; y < eixoY + 4; y++) {
    for (x = eixoX; x < eixoX + 4; x++) {
      wmove(win, y, x);
      wprintw(win, "%c", peca[x - eixoX][y - eixoY]);
    }
  }

  wrefresh(win);
}

//modifica a velocidade com que a pedra cai
int modificaVelocidade(int contador){
  if (contador < 5)       return 1000;
  else if(contador < 15)  return 800;
  else if(contador < 25)  return 700;
  else if(contador < 35)  return 600;
  else if(contador < 45)  return 500;
  else if(contador < 55)  return 400;
  else if(contador < 65)  return 325;
  else if(contador < 75)  return 250;
  else if(contador < 85)  return 200;
  else if(contador < 95)  return 150;
  else                    return 100;
}

//modifica o nivel
int modificaNivel(int contador){
  if (contador < 5)       return 1;
  else if(contador < 15)  return 2;
  else if(contador < 25)  return 3;
  else if(contador < 35)  return 4;
  else if(contador < 45)  return 5;
  else if(contador < 55)  return 6;
  else if(contador < 65)  return 7;
  else if(contador < 75)  return 8;
  else if(contador < 85)  return 9;
  else if(contador < 95)  return 10;
  else                    return 11;
}

//verifica se a peca pode ser criada
int finalizar(char peca [4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  char y, x;
  for (y = 0; y < 4; ++y){
    for (x = 0; x < 4; ++x){
      if(tabuleiro[eixoX + x][eixoY + y] == PEDRA && peca[x][y] == PEDRA){
        return 1;
      }
    }
  }

  return 0;
}

//cria a peca
void criar_peca(char piece[4][4]){
  int i, j;
  char randomico = rand() % 7;

  switch(randomico){
    case 0:
      // O
      piece[1][1] = PEDRA;
      piece[2][1] = PEDRA;
      piece[1][2] = PEDRA;
      piece[2][2] = PEDRA;
      break;
    case 1:
      // I
      piece[1][0] = PEDRA;
      piece[1][1] = PEDRA;
      piece[1][2] = PEDRA;
      piece[1][3] = PEDRA;
      break;
    case 2:
      // S
      piece[1][1] = PEDRA;
      piece[2][1] = PEDRA;
      piece[2][2] = PEDRA;
      piece[3][2] = PEDRA;
      break;
    case 3:
      // Z
      piece[1][1] = PEDRA;
      piece[2][1] = PEDRA;
      piece[0][2] = PEDRA;
      piece[1][2] = PEDRA;
      break;
    case 4:
      // T
      piece[2][1] = PEDRA;
      piece[1][2] = PEDRA;
      piece[2][2] = PEDRA;
      piece[3][2] = PEDRA;
      break;
    case 5:
      //L
      piece[1][1] = PEDRA;
      piece[1][2] = PEDRA;
      piece[2][2] = PEDRA;
      piece[3][2] = PEDRA;
      break;
    case 6:
      // J
      piece[3][1] = PEDRA;
      piece[1][2] = PEDRA;
      piece[2][2] = PEDRA;
      piece[3][2] = PEDRA;
      break;
  }
}
