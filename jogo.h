#ifndef jogo_h
#define jogo_h

#include <ncurses.h>
#define LARG 10
#define ALT 20



//imprime o jogo
void imprimirJogo(WINDOW *win, char tabuleiro[LARG][ALT], char peca[4][4], int eixoX, int eixoY);
//modifica a velocidade com que a pedra cai
int modificaVelocidade(int contador);
//modifica o nivel do jogo
int modificaNivel(int contador);
//verifica se a pedra pode ser criada
int finalizar(char peca [4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);
//cria a peca
void criar_peca(char piece[4][4]);


#endif /* jogo_h */