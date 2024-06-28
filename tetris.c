#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include "libtetris.h"


void mostraTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){
    
    for(int l = 0; l < TAMANHO; l++){
        mvaddstr(l+1, 0,"║");
        for(int c = 0; c < TAMANHO; c++){
            mvaddstr(0, c+1,"═");
            mvaddch(l+1, c+1, tabuleiro[l][c]);
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


// Precisa colocar restrição: só executar se não tiver bloco no caminho
    // *Coluna sempre deve ser ímpar, para respeitar a config. do tabuleiro
    // *É possível diminuir os argumentos dessa função declarando variáveis globais, verificar implicações
void derrubaPeca(int fonte[TAMANHO][TAMANHO], char tabuleiro[TAMANHO][TAMANHO], peca pecas[7], int pecaAtual, int delay, int coluna){

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
    int ch, matrizFonte[TAMANHO][TAMANHO] = {0};
    char tabuleiro[TAMANHO][TAMANHO] = {0};
    peca pecas[7];

//----------------------------------------------------------------------
//Inicialização
    setlocale(LC_ALL, "");// Define o conjunto de caracteres para UTF-8
    srand(time(NULL));    // Inicializa o gerador de números aleatórios com a semente baseada no tempo atual
    initscr();            // Inicia a janela ncurses
    //cbreak();           // Desabilita o buffer da linha
    halfdelay(1);       // Décimos de segundo entre uma entrada e outra      
    noecho();             // Não exibe a tecla pressionada
    keypad(stdscr, TRUE); // Habilita a captura de teclas especiais

    geraPecas(pecas);     // Gera e salva as peças no vetor
    geraTabuleiro(matrizFonte, tabuleiro);
    mostraTabuleiro(tabuleiro);


//----------------------------------------------------------------------
// Processos

    //derrubaPeca(matrizFonte, tabuleiro, pecas, 3, 550, 7);
    //pecaSorteada = rand() % 7;
    int tempo = 550, pecaSorteada = 2;
    int linha = 0, coluna = 6;

    while (((ch = getch()) != 'q')) {

        delay_output(55);
        if(tempo <= 0 && linha == 19){
            pecaSorteada = 6;
            linha = 0;
            coluna = 6;
            tempo = 550;
        }


        //derrubaPeca(matrizFonte, tabuleiro, pecas, pecaSorteada, 550, 7);

        //for(int i = 0; i <10 ; i++){
        //delay_output(55);
        tempo -= 55;

        switch (ch) {
            case KEY_UP:
                // Gira
                printw("Tecla espaço pressionada\n");
                
                break;
            case KEY_DOWN:
                // Acelera
                printw("Seta para baixo pressionada\n");

                break;
            case KEY_LEFT:
                // Move a peça para a esquerda
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                coluna -= 2;
                imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna);
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
            case KEY_RIGHT:
                // Move peça para a direita
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                coluna += 2;
                imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna);
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
            case ' ':
                // Cai de uma vez
                printw("Tecla espaço pressionada\n");
                
                break;
            default:
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna);// Imprime na matriz de referência, mudar nome -> alocaPeca()
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
        }

        limpaPeca(matrizFonte, pecas[pecaSorteada], linha, coluna);

        imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna);// Imprime na matriz de referência, mudar nome -> alocaPeca()

        geraTabuleiro(matrizFonte, tabuleiro);

        mostraTabuleiro(tabuleiro);
        //}

        linha ++;

    }

//---------------------------------------------------------------------
// Finalização

    endwin();             // Finaliza o ncurses
    return 0;
}
