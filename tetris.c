#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include "libtetris.h"
#define COLOR_ORANGE 8
int ch=0;
int game=1;
void mostraTabuleiro(int fonteMatriz[TAMANHO][TAMANHO]){
    int cor;
    init_color(COLOR_ORANGE, 1000, 350, 0);
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_ORANGE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);

    for(int l = 0; l < TAMANHO; l++){
        mvaddstr(l+1, 0,"║");
        for(int c = 0; c < TAMANHO; c++){
            mvaddstr(0, c+1,"═");
            int fonteN=fonteMatriz[l][c];
            if(fonteN<0){
                cor=(fonteN*-1)-1;
            }
            else{
                cor=fonteN -1;
            }
            attron(COLOR_PAIR(cor));
            switch(fonteN){
                case 0:
                mvaddstr(l+1, c+1, " ");
                break;
                default:
                mvaddstr(l+1, c+1, "█");
                if(fonteMatriz[l][c]<0){
                    if(game==1){
                        mvaddstr(l+1, c+1, "▒");
                    }
                    else{
                        mvaddstr(l+1, c+1, "♯");
                    }
                }
                break;
            }
            attroff(COLOR_PAIR(cor));
            mvaddstr(TAMANHO+1, c+1,"═");
        }
        printw("\n");
        mvaddstr(l+1, TAMANHO+1,"║");
    }
    mvaddstr(0, 0,"╔");
    mvaddstr(0, TAMANHO+1,"╗");
    mvaddstr(TAMANHO+1, TAMANHO+1,"╝");
    mvaddstr(TAMANHO+1, 0,"╚");
    mvaddstr(TAMANHO+2, 0,""); //Reposiciona o ponteiro
    refresh();
}
int main() {
    int matrizFonte[TAMANHO][TAMANHO] = {0};
    peca pecas[8];
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();              // Inicia a janela ncurses
    start_color();         
    cbreak();               // Desabilita o buffer da linha
    noecho();               // Não exibe a tecla pressionada
    keypad(stdscr, TRUE);   // Habilita a captura de teclas especiais
    geraPecas(pecas);       // Gera e salva as peças no vetor
    int pecaSorteada = 2, colh = 0, colv =0, colg=0, nextOr=2, counter=0, delayPad=500, delay=delayPad, delayFast=delayPad/20;
    int xpad = 6, ypad = -1;
    int x = xpad, y = ypad;
    int xinicial, yinicial;
    while(game==1) {
        counter=0;
        imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
        mostraTabuleiro(matrizFonte);
        while(1){
            delay=delayPad;
            timeout(1);
            ch = getch();
            switch(ch){
                case KEY_LEFT:
                    // Move a peça para a esquerda
                    colh=colisao(pecas[pecaSorteada], -2, 0, matrizFonte, y, x);
                    if(colh==0){
                        limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                        x-=2;
                    }
                break;
                case KEY_RIGHT:
                    // Move peça para a direita
                    colh=colisao(pecas[pecaSorteada], 2, 0, matrizFonte, y, x);
                    if(colh==0){
                        limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                        x+=2;
                    }
                break;
                case KEY_UP:
                    //gira a peça
                    nextOr=(pecas[pecaSorteada].orientacao+1)%5;
                    if(nextOr==0) nextOr=1;
                    colg=colGiro(pecas[pecaSorteada], nextOr, matrizFonte, y, x);
                    if(colg==0 && y>=0){
                        limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                        pecas[pecaSorteada].orientacao=nextOr;
                    }
                break;
                case KEY_DOWN:
                    delay=delayFast;
                break;
                case ' ':
                    xinicial=x;
                    yinicial=y;
                    colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                    while(colv==0){
                        colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                        if(colv==0){
                            y++;
                        }
                    }
                    limpaPeca(matrizFonte, pecas[pecaSorteada], yinicial, xinicial);
                    delay=0;
                break;
            }
            imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
            mostraTabuleiro(matrizFonte);
            sleep(0.001);
            counter+=1;
            if(counter>=delay){
                break;
            }
        }
        if(colv==1){
            colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
            if(colv==1){
                imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, -1);
                limpar(matrizFonte);
                game=!gameover(matrizFonte);
                if(game==0) break;
                pecaSorteada = rand() % 7;
                pecas[pecaSorteada].orientacao=1;
                x = xpad;
                y = ypad;
                colh = 0;
                colv = 0;
                colg = 0;
                continue;
            }
        }
        colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
        if(colv==0){
            limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
            y++;
            imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
        }
        mostraTabuleiro(matrizFonte);
    }
    while(game==0){
        mostraTabuleiro(matrizFonte);
    }
//---------------------------------------------------------------------
// Finalização

    endwin();             // Finaliza o ncurses
    return 0;
}
//---------------------------------------------------------------------