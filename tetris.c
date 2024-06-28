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


int main() {
    int ch, matrizFonte[TAMANHO][TAMANHO] = {0};
    char tabuleiro[TAMANHO][TAMANHO] = {0};
    peca pecas[8];

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
    int tempo = 550, pecaSorteada = 2, colidiu = 0;
    int linha = 0, coluna = 6;

    while (((ch = getch()) != 'q')) {

        delay_output(55);
        if(tempo <= 0 && colidiu){
            colidiu = 0;
            pecaSorteada = rand() % 7;
            linha = 0;
            coluna = 6;
            tempo = 550;
        }


        //derrubaPeca(matrizFonte, tabuleiro, pecas, pecaSorteada, 550, 7);

        //for(int i = 0; i <10 ; i++){
        //delay_output(55);
        tempo -= 55;

        switch (ch) {
            // case KEY_UP:
            //     // Gira
            //     printw("Tecla espaço pressionada\n");
                
            //     break;
            // case KEY_DOWN:
            //     // Acelera
            //     linha ++;
            //     limpaPeca(matrizFonte, pecas[pecaSorteada], linha-2, coluna);
     
            //     if(imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna) == -1){
            //         imprimePeca(matrizFonte, pecas[pecaSorteada], linha-2, coluna);
            //         linha--;
            //         colidiu = 1;
            //     }
            //     break;
            case KEY_LEFT:
                // Move a peça para a esquerda
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                coluna -= 2;
                if(imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna) == -1){
                    imprimePeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna-2);
                    coluna += 2;
                    colidiu = 1;
                }
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
            case KEY_RIGHT:
                // Move peça para a direita
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                coluna += 2;
                if(imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna) == -1){
                    imprimePeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna+2);
                    coluna -= 2;
                    colidiu = 1;
                }
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
            // case ' ':
            //     // Cai de uma vez
            //     printw("Tecla espaço pressionada\n"); //while imprime peca == 1 aumenta as linhas até colidir
                
            //     break;
            default:
                limpaPeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                if(imprimePeca(matrizFonte, pecas[pecaSorteada], linha, coluna) == -1){
                    imprimePeca(matrizFonte, pecas[pecaSorteada], linha-1, coluna);
                    colidiu = 1;
                }
                geraTabuleiro(matrizFonte, tabuleiro);
                mostraTabuleiro(tabuleiro);
                break;
        }
    
        if(colidiu){
            continue;
        }
        //}

        linha++;

    }

//---------------------------------------------------------------------
// Finalização

    endwin();             // Finaliza o ncurses
    return 0;
}
