#include <stdio.h>
#include <stdlib.h>
#include "libtetris.h"

#define bloco1  '\xFE' 
#define bloco2 ' ' 

void geraTabuleiro(int fonte[TAMANHO][TAMANHO], char tabuleiro[TAMANHO][TAMANHO]){
    // Tabuleiro 20 x 10
    // Definir macros para facilitar mudanças de tamanho

    for(int l = 0; l < TAMANHO; l++){
        for(int c = 0; c < TAMANHO; c++){
            if(fonte[l][c] == 0) tabuleiro[l][c] = bloco2;
            if(fonte[l][c] == 2) tabuleiro[l][c] = bloco1;
        }
    }
}

void imprimePeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef){
    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            if(l >= 0 && c >= 0 && l < TAMANHO && c < TAMANHO){
            fonte[l][c] = pecaAtual.grid[j][k]; 
            }
        }       
    }
}

void limpaPeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef){
    for(int l = linRef, j = 0; l < (linRef + 2); l++, j++){
        for(int c = colRef, k = 0; c < (colRef + 8); c++, k++){
            if(l >= 0 && c >= 0 && l < TAMANHO && c < TAMANHO){// Garante que está dentro do tabuleiro antes de tentar acessar
                if(pecaAtual.grid[j][k] != 0){
                    fonte[l][c] = 0;
                }
            }    
        }
    }
}

int movePeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef, int compensa){
    limpaPeca(fonte, pecaAtual, linRef-1, colRef);//

    int conta = 0;
    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef+compensa, k = 0; c < colRef + 8; c++, k++){
            if(l >= 0 && c >= 0 && l < TAMANHO && c < TAMANHO){
                if(fonte[l][c] == 0 && pecaAtual.grid[j][k] != 0){
                conta++;
                } 
            }
        }
    }

    // Verificação para saber se a peça pode ser movida
    if(conta == 8){
        imprimePeca(fonte, pecaAtual, linRef, colRef+compensa);//erro
        return 1;
    } else {
        imprimePeca(fonte, pecaAtual, linRef-1, colRef);
        return -1;
    }
}


// Gera a posicao inicial da peça
static peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois){
    peca pecaGerada;

    for(int l = 0; l < 2; l++){
        for(int c = 0; c < 8; c++){
            pecaGerada.grid[l][c] = 0;
        }
    }

    for(int i = inicioLinUm ; i <= fimLinUm; i++){
        pecaGerada.grid[0][i] = 2;
    }

    for(int i = inicioLinDois ; i <= fimLinDois; i++){
        pecaGerada.grid[1][i] = 2;
    }

    return pecaGerada;
}


void geraPecas(peca pecasGeradas[8]){

    for(int idPeca = 0; idPeca <= 6; idPeca++){
        peca pecaGerada;
        pecaGerada.orientacao = 1;

        switch (idPeca){
        case 0:
            //  00
            //000000
            pecaGerada = configuraPeca(2, 3, 0, 5);
            break;
        case 1:
            //  0000
            //  0000
            pecaGerada = configuraPeca(2, 5, 2, 5);
            break;
        case 2:
            //
            //00000000
            pecaGerada = configuraPeca(-1, -1, 0, 7);
            break;
        case 3:
            //    00
            //000000
            pecaGerada = configuraPeca(4, 5, 0, 5);
            break;
        case 4:
            //00
            //000000
            pecaGerada = configuraPeca(0, 1, 0, 5);
            break;
        case 5:
            //0000
            //  0000
            pecaGerada = configuraPeca(0, 3, 2, 5);
            break;
        case 6:
            //  0000
            //0000
            pecaGerada = configuraPeca(2, 5, 0, 3);
            break;
        }

        pecasGeradas[idPeca] = pecaGerada;
    }
}