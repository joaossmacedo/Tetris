#ifndef colisoes_h
#define colisoes_h

#include <ncurses.h>
#include <stdio.h>
#define LARG 10
#define ALT 20


//impede a peca de sair pela direita do tabuleiro
int verificaD(char peca[4][4]);
//impede a peca de sair pela esquerda do tabuleiro
int verificaE(char peca[4][4]);
//impede a peca de sair por baixo do tabuleiro
int verificaI(char peca[4][4]);
//diz onde posicionar uma peca que acabou de ser criada
int verificaS(char peca[4][4]);

//libera a peca pra descer
int libera(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);
//libera a peca girar
int liberaW(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);
//libera a peca a ser mover pra esquerda quando A for apertada
int liberaA(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);
//libera a peca descer mais rapido quando S for apertada
int liberaS(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);
//libera a peca a ser mover pra direita quando D for apertada
int liberaD(char peca[4][4], char tabuleiro[LARG][ALT], int eixoX, int eixoY);



#endif /* colisoes_h */