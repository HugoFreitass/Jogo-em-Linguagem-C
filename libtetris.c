#include <stdio.h>
#include <stdlib.h>
#include "libtetris.h"

//#define bloco1 '\xe2\x96\x88'
#define bloco1  '\xFE' //'\xdb'; //09608; //\u2588'
#define bloco2 ' ' 


void geraTabuleiro(int fonte[22][22], char tabuleiro[22][22]){
    // Tabuleiro 20 x 10
    // Definir macros para facilitar mudanças de tamanho
    
    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && fonte[l][c] == 0) tabuleiro[l][c] = bloco2;
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && fonte[l][c] == 2) tabuleiro[l][c] = bloco1;
            if((l == 0 || l == 21) && c != 0 && c!= 21) tabuleiro[l][c] = '-';
            if(c == 0 || c == 21) tabuleiro[l][c] = '|';
        }
    }
}

void imprimePeca(int fonte[22][22], peca pecaAtual, int linRef, int colRef){

    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            fonte[l][c] = pecaAtual.grid[j][k];
        }
    }

}

void limpaPeca(int fonte[22][22], peca pecaAtual, int linRef, int colRef){
    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            fonte[l][c] = 0;
        }
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


void geraPecas(peca pecasGeradas[]){

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