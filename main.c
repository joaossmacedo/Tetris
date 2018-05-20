#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "collision.h"
#include "menu.h"
#include "game.h"
#define DOWN 258
#define UP 259
#define LEFT 260
#define RIGHT 261
#define BLOCK '#'
#define EMPTY 0
#define WIDTH 10
#define HEIGHT 20

int main(){
  // positionX and positionY are the coordinates of the piece
  // inferiorLimit is the minimum distance between the piece and the bottom of the board
  // rightLimit is the minimum distance between the piece and the right side of the board
  // leftLimit is the minimum distance between the piece and the left side of the board
  int userInput;
  char board[WIDTH][HEIGHT], piece[4][4], auxPiece[4][4];
  char positionX, positionY, countDestroiedLines, level;
  char inferiorLimit, superiorLimit, rightLimit, leftLimit;
  char i, j;
  int score, highscore, speed;
  
  FILE * highscoreFile;

  srand(time(NULL));

  initscr();

  noecho();  // deactivate the echo

  cbreak();  // deactivate the buffer

  curs_set(0);  // deactivate the cursor

  start_color();

  keypad(stdscr, TRUE);  // allow the use of arrow keys

  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_YELLOW,COLOR_BLUE);

  wbkgd(stdscr,COLOR_PAIR(2));

  WINDOW * win;  // create window win where the game will happen

  win = newwin(HEIGHT, WIDTH, 0, (COLS - WIDTH) / 2);

  keypad(win, TRUE);  // allow the use of arrow keys in win

  wbkgd(win,COLOR_PAIR(1));  

  do{
    highscore = getHighscore(highscoreFile);
    
    // sets initial values
    level = 1;
    score = 0;
    countDestroiedLines = 0;
    speed = 1000;

    printMenu(score, highscore, level);

    // cleans the board
    for (j = 0; j < HEIGHT; j++) {
      for (i = 0; i < WIDTH; i++) {
        board[i][j] = EMPTY;
      }
    }

    do{
      wmove(win, 5, 0);
      wprintw(win, "PRESS S TO PLAY");
      userInput = wgetch(win);
      wclear(win);

      if(userInput == 'Q' || userInput == 'q'){
        delwin(win);
        endwin();
        return 0;
      }
    }while(userInput != 'S' && userInput != 's');


    while (1) {  // game loop

      createPiece(piece);

      rightLimit = minDistanceRight(piece);
      leftLimit = minDistanceLeft(piece);
      inferiorLimit = minDistanceBottom(piece);
      superiorLimit = minDistanceTop(piece);

      // sets the initial position
      positionY = 0 - superiorLimit;
      positionX = 4 - leftLimit;

      if(checkEndGame(piece, board, positionX, positionY) == 1){
        for (j = 0; j < HEIGHT; ++j){
          for (i = 0; i < WIDTH; ++i){
            if(board[i][j] != BLOCK)
              board[i][j] = EMPTY;
          }       
        }

        printMenu(score, highscore, level);
        saveHighscore(highscoreFile, score);

        break;
      }

      while (1) {
        wclear(win);

        printGame(win, board, piece, positionX, positionY);

        wtimeout(win,speed);
        userInput = wgetch(win);

        if(userInput == 'Q' || userInput == 'q'){  // possible quit game
          
          saveHighscore(highscoreFile, score);
          delwin(win);
          endwin();
          return 0;
        
        }else if(userInput == 'P' || userInput == 'p'){  // stop the game
          
          move(15,56);
          printw("PAUSED GAME");
          move(17, 49);
          printw("Press P to unpause the game");
          
          do{
            userInput = getch();
            if(userInput == 'Q' || userInput == 'q'){  // possible quit game while stopped
              saveHighscore(highscoreFile, score);
              delwin(win);
              endwin();
              return 0;
            }
          }while(userInput != 'P' && userInput != 'p');

          printMenu(score, highscore, level);

        }else if(userInput == RIGHT && positionX < WIDTH - 4 + rightLimit
                 && canMoveRight(piece, board, positionX, positionY) != 1){ // move right 
          
          positionX++;

        }else if(userInput == LEFT && positionX > 0 - leftLimit 
                && canMoveLeft(piece, board, positionX, positionY) != 1){ // move left 
          
          positionX--;

        }else if(userInput == DOWN && positionY < HEIGHT - 5 + inferiorLimit && positionY < HEIGHT - 2 
                && canFallTwice(piece, board, positionX, positionY) != 1 ){ // fall twice
          
          positionY++;

        }else if(userInput == UP && canSpin(piece, board, positionX, positionY) != 1){ // spin the piece
          spinPiece(board, piece, &positionX, &positionY);

          rightLimit = minDistanceRight(piece);
          leftLimit = minDistanceLeft(piece);
          inferiorLimit = minDistanceBottom(piece);

        }

        // piece fall
        if(positionY < HEIGHT - 4 + inferiorLimit && canFall(piece, board, positionX, positionY) != 1){
          positionY++;
        }else{
          break;
        }
      }

      score += 5;

      move(4, 55);
      printw("%d", score);
      move (7, 55);
      if (score > highscore){  
        printw("%d", score);
      }
      refresh();

      // add the piece to the board
      for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
          if (piece[i][j] == BLOCK) {
            board[positionX + i][positionY + j] = piece[i][j];
          }
        }
      }

      countDestroiedLines += destroyLine(board, &score);
      printMenu(score, highscore, level);

      level = modifyLevel(countDestroiedLines);

      speed = modifySpeed(countDestroiedLines);

      wrefresh(win);
    }

    move(15, 55);
    printw("END GAME");
    move(17, 49);
    printw("Press R to play again  ");
    printGame(win, board, piece, positionX, positionY);


    do{
      userInput = getch();
    }while(userInput != 'R' && userInput != 'r' && userInput != 'Q' && userInput != 'q');

  }while(userInput == 'R' || userInput == 'r');

  delwin(win);

  endwin();

  return 0;
}

