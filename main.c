#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "coordinates.h"
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
  // position.x and position.y are the coordinates of the piece
  // inferiorLimit is the minimum distance between the piece and the bottom of the board
  // rightLimit is the minimum distance between the piece and the right side of the board
  // leftLimit is the minimum distance between the piece and the left side of the board
  int userInput;
  char board[WIDTH][HEIGHT], piece[4][4];
  char countDestroiedLines, level;
  char inferiorLimit, superiorLimit, rightLimit, leftLimit;
  unsigned char i, j;
  int score, highscore, speed;
  
  struct Coordinates position;
  position.x = 0;
  position.y = 0;

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
    highscore = getHighscore();
    
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
      position.y = 0 - superiorLimit;
      position.x = 4 - leftLimit;

      if(checkEndGame(piece, board, position) == 1){
        for (j = 0; j < HEIGHT; ++j){
          for (i = 0; i < WIDTH; ++i){
            if(board[i][j] != BLOCK)
              board[i][j] = EMPTY;
          }       
        }

        printMenu(score, highscore, level);
        saveHighscore(score);

        break;
      }

      while (1) {
        wclear(win);

        printGame(win, board, piece, position);

        wtimeout(win,speed);
        userInput = wgetch(win);

        if(userInput == 'Q' || userInput == 'q'){  // possible quit game
          
          saveHighscore(score);
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
              saveHighscore(score);
              delwin(win);
              endwin();
              return 0;
            }
          }while(userInput != 'P' && userInput != 'p');

          printMenu(score, highscore, level);

        }else if(userInput == RIGHT && position.x < WIDTH - 4 + rightLimit
                 && canMoveRight(piece, board, position) != 1){ // move right 
          
          position.x++;

        }else if(userInput == LEFT && position.x > 0 - leftLimit 
                && canMoveLeft(piece, board, position) != 1){ // move left 
          
          position.x--;

        }else if(userInput == DOWN && position.y < HEIGHT - 5 + inferiorLimit && position.y < HEIGHT - 2 
                && canFallTwice(piece, board, position) != 1 ){ // fall twice
          
          position.y++;

        }else if(userInput == UP && canSpin(piece, board, position) != 1){ // spin the piece
          position = spinPiece(board, piece, position);

          rightLimit = minDistanceRight(piece);
          leftLimit = minDistanceLeft(piece);
          inferiorLimit = minDistanceBottom(piece);

        }

        if(position.y < HEIGHT - 4 + inferiorLimit && canFall(piece, board, position) != 1){ // piece fall
          position.y++;
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
            board[position.x + i][position.y + j] = piece[i][j];
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
    printGame(win, board, piece, position);


    do{
      userInput = getch();
    }while(userInput != 'R' && userInput != 'r' && userInput != 'Q' && userInput != 'q');

  }while(userInput == 'R' || userInput == 'r');

  delwin(win);

  endwin();

  return 0;
}