#include <stdio.h>
#include <ncurses.h> // Biblioteca extra necessária para ncurses
#include "libtetris.h"

// gcc libtetris.h
// gcc -c libtetris.c -o libtetris.o
// gcc tetris.c -o tetris libtetris.o -lncurses
// ./tetris

int main() {
    int ch, matrizFonte[22][22];
    char tabuleiro[22][22] = {0};
    
    initscr();            // Inicia a janela ncurses
    cbreak();             // Desabilita o buffer da linha
    noecho();             // Não exibe a tecla pressionada
    keypad(stdscr, TRUE); // Habilita a captura de teclas especiais

    geraTabuleiro(matrizFonte, tabuleiro);

    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            printw("%c", tabuleiro[l][c]);
        }
        printw("\n");
    }
    refresh();


    // printw("Pressione qualquer tecla...\n");
    // refresh();            // Atualiza a tela

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
