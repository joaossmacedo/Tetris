#include <ncurses.h>
#include <stdio.h>
#include "colisoes.h"
#define PEDRA '*'
#define BRANCA 0
#define LARG 10
#define ALT 20

//imprime o menu
void imprimirMenu(long score, long highscore, int nivel){
  clear();
  //menu
  move(2,2);
  printw("TETRIS");
  move(3,2);
  printw("Feito por:");
  move(4,2);
  printw("Antonio");
  move(5,2);
  printw("Ademario Junior");
  move(6,2);
  printw("Danilo Felipe");
  move(7,2);
  printw("Francisco Guilherme");
  move(8,2);
  printw("Joao Macedo");
  move(17,49);
  printw("Para parar o jogo aperte P");
  move(19,49);
  printw("Para sair do jogo aperte Q");
  move(2,55);
  printw("Nivel %d", nivel);
  move(3,55);
  printw("SCORE");
  move(4,55);
  printw("%ld", score);
  move(6,55);
  printw("HIGHSCORE");
  move(7, 55);
  if (score > highscore)  printw("%ld", score);
  else printw("%ld", highscore);

  refresh();
}

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

//recebe o highscore
int recebeHighscore(FILE * myFile){
  long highscore;
  //abre o arquivo
  myFile = fopen("rank.txt", "r");

  //pega o valor que esta no arquivo e coloca na variavel highscore
  fscanf(myFile, "%ld", &highscore);    

  //fecha o arquivo
  fclose(myFile);

  return highscore;
}


//salva o highscore
void salvarHighscore(FILE * myFile, long score){
  long highscore;

  myFile = fopen("rank.txt", "r");

  fscanf(myFile, "%ld", &highscore);    

  fclose(myFile);

  if(score > highscore){
    myFile = fopen("rank.txt", "w");

    fprintf(myFile, "%ld", score);

    fclose(myFile);
  }
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

//impede a peca de sair pela direita do tabuleiro
int verificaD(char peca[4][4]){
  int dir, dir1, dir2, dir3, dir4, x, c;
  dir1 = dir2 = dir3 = dir4 =0;

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(peca[x][0] != PEDRA && c == 0) {
      dir1++;
    }else if(peca[x][0] == PEDRA && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(peca[x][1] != PEDRA && c == 0) {
      dir2++;
    }else if(peca[x][1] == PEDRA && c == 0){
      c++;
    }
  }
  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(peca[x][2] != PEDRA && c == 0) {
      dir3++;
    }else if(peca[x][2] == PEDRA && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 4 - 1; x >= 0; x--) {
    if(peca[x][3] != PEDRA && c == 0) {
      dir4++;
    }else if(peca[x][3] == PEDRA && c == 0){
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

//impede a peca de sair pela esquerda do tabuleiro
int verificaE(char peca[4][4]){
  int esq, esq1, esq2, esq3, esq4, x, c;
  esq1 = esq2 = esq3 = esq4 = 0;

  c = 0;
  for (x = 0; x < 4; x++) {
    if(peca[x][0] != PEDRA && c == 0) {
      esq1++;
    }else if(peca[x][0] == PEDRA && c == 0){
      c++;
    }
  }

  c = 0;
  for (x = 0; x < 4; x++) {
    if(peca[x][1] != PEDRA && c == 0) {
      esq2++;
    }else if(peca[x][1] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (x = 0; x < 4; x++) {
    if(peca[x][2] != PEDRA && c == 0) {
      esq3++;
    }else if(peca[x][2] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (x = 0; x < 4; x++) {
    if(peca[x][3] != PEDRA && c == 0) {
      esq4++;
    }else if(peca[x][3] == PEDRA && c == 0){
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

//impede a peca de sair por baixo do tabuleiro
int verificaI(char peca[4][4]){
  int inf, inf1, inf2, inf3, inf4, y, c;
  inf1 = inf2 = inf3 = inf4 = 0;

  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(peca[0][y] != PEDRA && c == 0) {
      inf1++;
    }else if(peca[0][y] == PEDRA && c == 0){
      c++;
    }
  }

  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(peca[1][y] != PEDRA && c == 0) {
      inf2++;
    }else if(peca[1][y] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(peca[2][y] != PEDRA && c == 0) {
      inf3++;
    }else if(peca[2][y] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0; 
  for (y = 4 - 1; y >= 0; y--) {
    if(peca[3][y] != PEDRA && c == 0) {
      inf4++;
    }else if(peca[3][y] == PEDRA && c == 0){
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

//diz onde posicionar uma peca que acabou de ser criada
int verificaS(char peca[4][4]){
  int sup, sup1, sup2, sup3, sup4, y, c;
  sup1 = sup2 = sup3 = sup4 = 0;

  c = 0;
  for (y = 0; y < 4; y++) {
    if(peca[0][y] != PEDRA && c == 0) {
      sup1++;
    }else if(peca[0][y] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(peca[1][y] != PEDRA && c == 0) {
      sup2++;
    }else if(peca[1][y] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(peca[2][y] != PEDRA && c == 0) {
      sup3++;
    }else if(peca[2][y] == PEDRA && c == 0){
      c++;
    }
  }
  
  c = 0;
  for (y = 0; y < 4; y++) {
    if(peca[3][y] != PEDRA && c == 0) {
      sup4++;
    }else if(peca[3][y] == PEDRA && c == 0){
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

//libera a peca pra descer
int libera(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  int x, y;

  for (y = 0; y  < 4; y++) {
    for (x = 0; x < 4; x++) {
      if(peca[x][y] == PEDRA && tabuleiro[x + eixoX][y + eixoY + 1] == PEDRA){
        return 1;
      }
    }
  }

  return 0;
}

//libera a peca girar
int liberaW(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  int repositorio[4][4];
  int x, y, libera;
  libera = 0;

  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      if (peca[y][3 - x] == PEDRA) repositorio[x][y] = peca[y][3 - x];
      else repositorio[x][y] = BRANCA;
    }
  }

  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      if(repositorio[x][y] == PEDRA && tabuleiro[x + eixoX][y + eixoY] == PEDRA)
        libera = 1;
    }
  }

  return libera;
}

//libera a peca a ser mover pra esquerda quando A for apertada
int liberaA(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  int a, b, libera;
  libera = 0;
  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(peca[a][b] == PEDRA && tabuleiro[a + eixoX - 1][b + eixoY] == PEDRA){
        libera = 1;
      }
    }
  }

  return libera;
}

//libera a peca descer mais rapido quando S for apertada
int liberaS(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  int a, b, libera;
  libera = 0;
  //libera a peca pra cair duas vezes
  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(peca[a][b] == PEDRA && (tabuleiro[a + eixoX][b + eixoY + 1] == PEDRA || tabuleiro[a + eixoX][b + eixoY + 2] == PEDRA)){
        libera = 1;
      }
    }
  }

  return libera;
}

//libera a peca a ser mover pra direita quando D for apertada
int liberaD(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY){
  int a, b, libera;
  libera = 0;
  //libera a peca pra ir para a direita
  for (b = 0; b  < 4; b++) {
    for (a = 0; a < 4; a++) {
      if(peca[a][b] == PEDRA && tabuleiro[a + eixoX + 1][b + eixoY] == PEDRA){
        libera = 1;
      }
    }
  }

  return libera;
}
