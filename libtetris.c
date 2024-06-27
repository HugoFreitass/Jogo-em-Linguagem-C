#include <stdio.h>
#include <stdlib.h>
#include "libtetris.h"

/*
//#define bloco1 '\xe2\x96\x88'
#define bloco1 '\xFE' //'\xdb'; //09608; //\u2588'
#define bloco2 ' ' 


void geraTabuleiro(int fonte[22][22], char tabuleiro[22][22]){
    // Tabuleiro 20 x 10
    // Definir macros para facilitar mudanças de tamanho
    
    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && fonte[l][c] == 0) tabuleiro[l][c] = ' ';
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && fonte[l][c] != 0) tabuleiro[l][c] = '*';
            if((l == 0 || l == 21) && c != 0 && c!= 21) tabuleiro[l][c] = '-';
            if(c == 0 || c == 21) tabuleiro[l][c] = '|';
        }
    }
}
*/

void imprimePeca(int fonte[20][20], peca pecaAtual, int linRef, int colRef){

    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            fonte[l][c] = pecaAtual.grid1[j][k];
        }
    }

}

void limpaPeca(int fonte[20][20], peca pecaAtual, int linRef, int colRef){
    for(int l = linRef, j = 0; l < linRef + 2; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            fonte[l][c] = 0;
        }
    }
}

// Gera a posicao inicial da peça
static peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois, int idPeca){
    peca pecaGerada;

    //1
    for(int l = 0; l < 2; l++){
        for(int c = 0; c < 8; c++){
            pecaGerada.grid1[l][c] = 0;
        }
    }
    for(int i = inicioLinUm ; i <= fimLinUm; i++){
        pecaGerada.grid1[0][i] = idPeca+1;
    }

    for(int i = inicioLinDois ; i <= fimLinDois; i++){
        pecaGerada.grid1[1][i] = idPeca+1;
    }
    
    //2
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 4; c++){
            pecaGerada.grid2[l][c] = 0;
        }
    }
    if(inicioLinUm>=0){
        for(int i = inicioLinUm/2 ; i <= fimLinUm/2; i++){
            for(int j=2;j<=3;j++){
                pecaGerada.grid2[i][j] = idPeca+1;
            }
        }
    }
    if(inicioLinDois>=0){
        for(int i = inicioLinDois/2 ; i <= fimLinDois/2; i++){
            for(int j=0;j<=1;j++){
                pecaGerada.grid2[i][j] = idPeca+1;
            }
        }
    }
    

    //3
    for(int i = 7, j=0; i >= 0; i--, j++){
        pecaGerada.grid3[0][i] = pecaGerada.grid1[1][j];
        pecaGerada.grid3[1][i] = pecaGerada.grid1[0][j];
    }

    //4
    for(int k=0, l=3;k<4;k++,l--){
        for(int i = 3, j=0; i >= 0; i--, j++){
            pecaGerada.grid4[k][i] = pecaGerada.grid2[l][j];
        }
    }
    return pecaGerada;
}


void geraPecas(peca pecasGeradas[]){

    for(int idPeca = 0; idPeca < 7; idPeca++){
        peca pecaGerada;
        pecaGerada.orientacao = 1;

        switch (idPeca){
        case 0:
            //001100
            //111111

            //11
            //1111
            pecaGerada = configuraPeca(2, 3, 0, 5, idPeca);
            break;
        case 1:
            //  0000
            //  0000
            pecaGerada = configuraPeca(2, 5, 2, 5, idPeca);
            break;
        case 2:
            //
            //00000000
            pecaGerada = configuraPeca(-1, -1, 0, 7, idPeca);
            break;
        case 3:
            //    00
            //000000
            pecaGerada = configuraPeca(4, 5, 0, 5, idPeca);
            break;
        case 4:
            //00
            //000000
            pecaGerada = configuraPeca(0, 1, 0, 5, idPeca);
            break;
        case 5:
            //0000
            //  0000
            pecaGerada = configuraPeca(0, 3, 2, 5, idPeca);
            break;
        case 6:
            //  0000
            //0000
            pecaGerada = configuraPeca(2, 5, 0, 3, idPeca);
            break;
        }

        pecasGeradas[idPeca] = pecaGerada;
    }
}