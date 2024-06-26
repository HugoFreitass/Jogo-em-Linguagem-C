#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "libtetris.h"

//#define TAMANHO 22

void mostraTabuleiro(char tabuleiro[22][22]){
    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            mvaddch(l, c, tabuleiro[l][c]);
        }
        printw("\n");
    }
    refresh();
}


// Precisa colocar restrição: só executar se não tiver bloco no caminho
    // *Coluna sempre deve ser ímpar, para respeitar a config. do tabuleiro
    // *É possível diminuir os argumentos dessa função declarando variáveis globais, verificar implicações
void derrubaPeca(int fonte[22][22], char tabuleiro[22][22], peca pecas[7], int pecaAtual, int delay, int coluna){

    for(int i = 1; i < 20; i++){
        //delay = delay != 0? delay : 550;
        delay_output(delay);
        
        limpaPeca(fonte, pecas[pecaAtual], i-1, coluna);

        imprimePeca(fonte, pecas[pecaAtual], i, coluna);// Imprime na matriz de referência, mudar nome -> alocaPeca()

        geraTabuleiro(fonte, tabuleiro);

        mostraTabuleiro(tabuleiro);
    }

}

int main() {
    int ch, matrizFonte[22][22] = {0};
    char tabuleiro[22][22] = {0};
    peca pecas[7];

//----------------------------------------------------------------------
//Inicialização
    
    initscr();            // Inicia a janela ncurses
    cbreak();             // Desabilita o buffer da linha
    noecho();             // Não exibe a tecla pressionada
    keypad(stdscr, TRUE); // Habilita a captura de teclas especiais

    geraPecas(pecas);     // Gera e salva as peças no vetor
    geraTabuleiro(matrizFonte, tabuleiro);
    mostraTabuleiro(tabuleiro);


//----------------------------------------------------------------------
// Processos

    derrubaPeca(matrizFonte, tabuleiro, pecas, 3, 550, 7);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// Transformar em uma função -> movimento(tecla)

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_DOWN:
                // Acelera
                printw("Seta para baixo pressionada\n");

                break;
            case KEY_LEFT:
                // Move a peça para a esquerda
                printw("Seta para a esquerda pressionada\n");

                break;
            case KEY_RIGHT:
                // Move peça para a direita
                printw("Seta para a direita pressionada\n");

                break;

                // Adicionar tecla para rotacionar

            case ' ':
                // Cai de uma vez
                printw("Tecla espaço pressionada\n");
                
                break;
        }
        refresh();        
    }

//---------------------------------------------------------------------
// Finalização

    endwin();             // Finaliza o ncurses
    return 0;
}
