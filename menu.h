#ifndef menu_h
#define menu_h


void printMenu(long score, long highscore, int level);

int getHighscore(FILE * highscoreFile);

void saveHighscore(FILE * highscoreFile, long score);


#endif /* menu_h */