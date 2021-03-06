#include <ncurses.h>
#include <stdio.h>
#include "menu.h"

void printMenu(int score, int highscore, int level){
  clear();

  move(2,2);
  printw("TETRIS");
  move(4,2);
  printw("Made by:");
  move(5,2);
  printw("Antonio");
  move(6,2);
  printw("Ademario Junior");
  move(7,2);
  printw("Danilo Felipe");
  move(8,2);
  printw("Guilherme Francsico");
  move(9,2);
  printw("Joao Macedo");
  move(17,49);
  printw("Press P to pause the game");
  move(19,49);
  printw("Press Q to leave the game");
  move(2,55);
  printw("Level %d", level);
  move(3,55);
  printw("SCORE");
  move(4,55);
  printw("%d", score);
  move(6,55);
  printw("HIGHSCORE");
  move(7, 55);
  if (score > highscore){
    printw("%d", score);
  }else {
    printw("%d", highscore);
  }
  refresh();
}

int getHighscore(void){
  FILE * highscoreFile; 

  int highscore;
  
  if ((highscoreFile = fopen("rank.txt", "r"))){
    fscanf(highscoreFile, "%d", &highscore);    

    fclose(highscoreFile);
  } else {
    highscore = 0;
  }

  return highscore;
}

void saveHighscore(int score){
  FILE * highscoreFile;
  int highscore;

  if ((highscoreFile = fopen("rank.txt", "r"))){
    fscanf(highscoreFile, "%d", &highscore);    

    fclose(highscoreFile);
  } else {
    highscore = 0;
  }

  if(score > highscore){
    highscoreFile = fopen("rank.txt", "w");

    fprintf(highscoreFile, "%d", score);

    fclose(highscoreFile);
  }
}
