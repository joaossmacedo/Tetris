#ifndef menu_h
#define menu_h


void printMenu(int score, int highscore, int level);

int getHighscore(FILE * highscoreFile);

void saveHighscore(FILE * highscoreFile, int score);


#endif /* menu_h */