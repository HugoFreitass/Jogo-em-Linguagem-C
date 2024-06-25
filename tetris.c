#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "libtetris.h"

int main() {
    int ch, matrizFonte[22][22] = {0};
    char tabuleiro[22][22] = {0};
    struct peca pecas[7];
    // CRIAR vetor para armazenar peças
    
    initscr();            // Inicia a janela ncurses
    cbreak();             // Desabilita o buffer da linha
    noecho();             // Não exibe a tecla pressionada
    keypad(stdscr, TRUE); // Habilita a captura de teclas especiais

    geraPecas(pecas);     // Gera e salva as peças no vetor

    imprimePeca(matrizFonte, pecas[6], 1, 4*2);

    geraTabuleiro(matrizFonte, tabuleiro);

    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            mvaddch(l, c, tabuleiro[l][c]);
        }
        printw("\n");
    }
   
    refresh();


    //Possível transformar em uma função movimento(tecla)
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_DOWN:
                // Acelera
                printw("Seta para baixo pressionada\n");

                break;
            case KEY_LEFT:
                // Rotaciona a peça para a esquerda
                printw("Seta para a esquerda pressionada\n");

                break;
            case KEY_RIGHT:
                // Rotaciona a peça para a direita
                printw("Seta para a direita pressionada\n");

                break;
            case ' ':
                // Cai de uma vez
                printw("Tecla espaço pressionada\n");
                
                break;
        }
        refresh();        
    }
    endwin();             // Finaliza o ncurses
    return 0;
}
