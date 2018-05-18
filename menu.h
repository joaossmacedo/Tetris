#ifndef menu_h
#define menu_h

//imprime o menu
void imprimirMenu(long score, long highscore, int nivel);
//recebe o highscore
int recebeHighscore(FILE * myFile);
//salva o highscore
void salvarHighscore(FILE * myFile, long score);



#endif /* menu_h */