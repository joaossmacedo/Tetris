#include <ncurses.h>
#include <stdio.h>

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
