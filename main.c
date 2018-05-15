#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colisoes.h"
#define DOWN 258
#define UP 259
#define LEFT 260
#define RIGHT 261
#define PEDRA '*'
#define BRANCA 0
#define LARG 10
#define ALT 20

int main(){
  //opcao eh a opção escolhida pelo usuario
  //'x', 'y', 'a' e 'b' são variaveis que vivem mudando e sao usadas para o uso de for
  //eixoX e eixoY sao as coordenadas de onde a peca se encontra
  //desce, desceDois, direita e esquerda verificam se os movimentos podem ser feitos
  //inf eh o menor valor entre inf1, inf2, inf3 e inf4 e serve para impedir a peca de sair do limite da janela por baixo
  //dir eh o menor valor entre dir1, dir2, dir3 e dir4 e serve para impedir a peca de sair do limite da janela pela direita
  //esq eh o menor valor entre esq1, esq2, esq3 e esq4 e serve para impedir a peca de sair do limite da janela pela esquerda
  //limpaLinha verifica se a linha pode ser limpada
  //veloc eh o veloc de timeout para caso alguma tecla nao seja apertada ela ainda acaba o loop
  //contador é a variavel que fara o veloc de timeout variar
  //giro libera a peca pra girar
  //fim define quando o jogo acaba
  //randomico é o randomico que escolhe a peca
  //nivel é o nivel de velocidade do jogo
  //score é a pontuacao
  //highscore é a pontuacao maxima
  char tabuleiro[LARG][ALT], peca[4][4], temp[4][4];
  char limpaLinha, contador,  giro, fim, randomico, nivel;
  char inf, infTemp, sup, dir, dirTemp, esq, esqTemp;
  int opcao, x, y, a, b, eixoX, eixoY, desce, desceDois, direita, esquerda, veloc, velocProx;
  long score, highscore;
  FILE * myFile;

  //inicializa o randomico
  srand(time(NULL));
  //inicializa o ncurses
  initscr();
  //desativa o eco das palavras
  noecho();
  //desativa o buffer
  cbreak();
  //desativa o cursor
  curs_set(0);
  //cria as opcoes de cor
  start_color();
  //permite o uso das setinhas
  keypad(stdscr, TRUE);

  //inicializa o par de cores
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_YELLOW,COLOR_BLUE);

  //atribui a cor a janela padrao
  wbkgd(stdscr,COLOR_PAIR(2));

  //cria a janela win onde rodara o jogo
  WINDOW * win;
  //define o tamanho da janela
  win = newwin(ALT, LARG, 0, (COLS - LARG) / 2);
  //ativa teclas especiais como setinha
  keypad(win, TRUE);
  //atribui a cor a janela win
  wbkgd(win,COLOR_PAIR(1));  

  //esse eh o loop em que roda uma partida
  do{
    //recebe o highscore a partir do arquivo
    highscore = recebeHighscore(myFile);

    //faz com que o nivel inicie sempre em um
    nivel = 1;
    //faz com que ao comecar o jogo o score seja 0
    score = 0;
    contador = 0;
    //faz com que a velocidade inicial seja sempre 1000
    veloc = 1000;

    imprimirMenu(score, highscore, nivel);

    //limpa a matriz
    for (y = 0; y < ALT; y++) {
      for (x = 0; x < LARG; x++) {
        tabuleiro[x][y] = BRANCA;
      }
    }

    //pede que a tecla s seja apertada para que o jogo se inicie
    do{
      wmove(win, 5, 0);
      wprintw(win, "PARA JOGAR APERTE S");
      opcao = wgetch(win);
      wclear(win);

      if(opcao == 'Q' || opcao == 'q'){   //sai do jogo enquanto esta parado
        delwin(win);
        endwin();
        return 0;
      }
    }while(opcao != 'S' && opcao != 's');


    //esse eh o loop em que as peca sao criadas
    while (1) {
      randomico = rand() % 7;

      //limpa a peca e o temporario
      for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
          peca[x][y] = BRANCA;
          temp[x][y] = BRANCA;
        }
      }

      //faz a peca
      switch(randomico){
        case 0:
        // O
        peca[1][1] = PEDRA;
        peca[2][1] = PEDRA;
        peca[1][2] = PEDRA;
        peca[2][2] = PEDRA;
        break;
        case 1:
        // I
        peca[1][0] = PEDRA;
        peca[1][1] = PEDRA;
        peca[1][2] = PEDRA;
        peca[1][3] = PEDRA;
        break;
        case 2:
        // S
        peca[1][1] = PEDRA;
        peca[2][1] = PEDRA;
        peca[2][2] = PEDRA;
        peca[3][2] = PEDRA;
        break;
        case 3:
        // Z
        peca[1][1] = PEDRA;
        peca[2][1] = PEDRA;
        peca[0][2] = PEDRA;
        peca[1][2] = PEDRA;
        break;
        case 4:
        // T
        peca[2][1] = PEDRA;
        peca[1][2] = PEDRA;
        peca[2][2] = PEDRA;
        peca[3][2] = PEDRA;
        break;
        case 5:
        peca[1][1] = PEDRA;
        peca[1][2] = PEDRA;
        peca[2][2] = PEDRA;
        peca[3][2] = PEDRA;
        break;
        case 6:
        // J
        peca[3][1] = PEDRA;
        peca[1][2] = PEDRA;
        peca[2][2] = PEDRA;
        peca[3][2] = PEDRA;
        break;
      }

      //impede a peca de sair pelas laterais
      dir = verificaD(peca);
      esq = verificaE(peca);
      inf = verificaI(peca);
      //posiciona a pedra mais a cima possivel ao comecar
      sup = verificaS(peca);

      //define o eixo inicial
      eixoY = 0 - sup;
      eixoX = 4 - esq;

      //verifica se eh para a partida acabar ou nao
      fim = finalizar(peca, tabuleiro, eixoX, eixoY);

      //se finalizar retorna 1 fecha a partida
      if(fim == 1){
        for (y = 0; y < ALT; ++y){
          for (x = 0; x < LARG; ++x){
            if(tabuleiro[x][y] != PEDRA)
              tabuleiro[x][y] = ' ';
          }       
        }
        imprimirMenu(score, highscore, nivel);
        salvarHighscore(myFile, score);

        break;
      }

      //esse eh o loop em que as peca caem
      while (1) {
        //limpa a tela
        wclear(win);

        //imprime o tabuleiro e a peca
        imprimirJogo(win, tabuleiro, peca, eixoX, eixoY);

        //libera a peca girar
        giro = liberaW(peca, tabuleiro, eixoX, eixoY);
        //libera a peca a ser mover pra esquerda quando A for apertada
        esquerda = liberaA(peca, tabuleiro, eixoX, eixoY);
        //libera a peca descer mais rapido quando S for apertada
        desceDois = liberaS(peca, tabuleiro, eixoX, eixoY);
        //libera a peca a ser mover pra direita quando D for apertada
        direita = liberaD(peca, tabuleiro, eixoX, eixoY);


        //faz a peca cair se o getch nao for apertado
        wtimeout(win,veloc);
        opcao = wgetch(win);

        //como sair do jogo
        if(opcao == 'Q' || opcao == 'q'){
          salvarHighscore(myFile, score);
          delwin(win);
          endwin();
          return 0;
        }//pausa o jogo
        else if(opcao == 'P' || opcao == 'p'){ 
          move(15,56);
          printw("JOGO PAUSADO");
          move(17, 48);
          printw("Para voltar ao jogo aperte P");
          do{
            opcao = getch();

            if(opcao == 'Q' || opcao == 'q'){   //sai do jogo enquanto esta parado
              salvarHighscore(myFile, score);
              delwin(win);
              endwin();
              return 0;
            }
          }while(opcao != 'P' && opcao != 'p');

          imprimirMenu(score, highscore, nivel);

        }//move pra direita
        else if(opcao == RIGHT && eixoX < LARG - 4 + dir && direita != 1){ 
          eixoX++;
        }//move pra esquerda
        else if(opcao == LEFT && eixoX > 0 - esq && esquerda != 1){  
          eixoX--;
        }//desce mais rapido
        else if(opcao == DOWN && eixoY < ALT - 5 + inf && eixoY < ALT - 2 && desceDois != 1 ){ 
          eixoY++;
        }//gira a peca
        else if(opcao == UP && giro != 1){ 
          //coloca a peca ja gira num repositorio temporario
          for (b = 0; b < 4; b++) {
            for (a = 0; a < 4; a++) {
              temp[a][b] = peca[b][3 - a];
            }
          }
          //peca recebe repositorio
          for (b = 0; b < 4; b++) {
            for (a = 0; a < 4; a++) {
              peca[a][b] = temp[a][b];
            }
          }

          dirTemp = verificaD(peca);
          esqTemp = verificaE(peca);
          infTemp = verificaI(peca);
          
          //impede que se girar no limite mais a direita da tela saia da mesma
          if(dir > dirTemp && eixoX + 4 - dirTemp > LARG - 1){
            eixoX -= (dir - dirTemp);
          }
          dir = dirTemp;

          //impede que se girar no limite mais a esquerda da tela saia da mesma
          if(esq > esqTemp && eixoX + esqTemp < 0){
            eixoX += (esq - esqTemp);
          }
          esq = esqTemp;

          //impede que se girar no limite mais a baixo da tela saia da mesma
          if(inf > infTemp){
            eixoY -= (inf - infTemp);
          }
          inf = infTemp;
        }

        desce = libera(peca, tabuleiro, eixoX, eixoY);

        //faz a peca cair
        if(eixoY < ALT - 4 + inf && desce != 1){
          eixoY++;
        }else{
          break;
        }
      }
      score += 5;

      move(4, 55);
      printw("%ld", score);
      move (7, 55);
      if (score > highscore)  printw("%ld", score);
      refresh();

      //adicionar a peca a matriz
      for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
          if (peca[x][y] == PEDRA) {
            tabuleiro[eixoX + x][eixoY + y] = peca[x][y];
          }
        }
      }

      //limpa a linha se a mesma estiver cheia
      for (y = ALT - 1; y >= 0; y--) {
        for (x = 0; x < LARG; x++) {
          if (tabuleiro[x][y] == PEDRA) {
            limpaLinha++;
          }
          if (limpaLinha == LARG) {
            for (a = 0; a < LARG; a++) {
              tabuleiro[a][y] = 0;
            }
            for (b = y; b >= 1; b--) {
              for (a = 0; a < LARG; a++) {
                tabuleiro[a][b] = tabuleiro[a][b - 1];
              }
            }
            contador++;
            y++;
            score += 100;
            imprimirMenu(score, highscore, nivel);
          }
        }
        limpaLinha = 0;
      }

      //modifica a velocidade que a peca cai e indica o nivel
      nivel = modificaNivel(contador);
      velocProx = modificaVelocidade(contador);
      if (veloc != velocProx) imprimirMenu(score, highscore, nivel);
      veloc = velocProx;

      wrefresh(win);
    }

    move(15, 55);
    printw("FIM DE JOGO");
    move(17, 48);
    printw("Para jogar mais uma aperte R");
    imprimirJogo(win, tabuleiro, peca, eixoX, eixoY);


    do{
      opcao = getch();
    }while(opcao != 'R' && opcao != 'r' && opcao != 'Q' && opcao != 'q');

  }while(opcao == 'R' || opcao == 'r');

  delwin(win);

  endwin();

  return 0;
}

