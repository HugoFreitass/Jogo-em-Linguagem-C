#include <stdio.h>
#include <stdlib.h>
#include "libtetris.h"

void imprimePeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef, int mod){
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);
    for(int l = linRef, j = 0; l < linRef + 4; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            if(pecaMatriz[j][k]>0 && fonte[l][c]>=0){
                fonte[l][c] = pecaMatriz[j][k]*mod;
            }
        }
    }
}

void limpaPeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef){
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);
    for(int l = linRef, j = 0; l < linRef + 4; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            if(pecaMatriz[j][k]>0 && fonte[l][c]>=0){
                fonte[l][c] = 0;
            }
        }
    }
}

// Gera a posicao inicial da peça
static peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois, int idPeca){
    peca pecaGerada;
    
    //1
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 8; c++){
            pecaGerada.grid1[l][c] = 0;
        }
    }
    for(int i = inicioLinUm ; i <= fimLinUm; i++){
        pecaGerada.grid1[1][i] = idPeca+2;
    }

    for(int i = inicioLinDois ; i <= fimLinDois; i++){
        pecaGerada.grid1[2][i] = idPeca+2;
    }
    for(int c = 0; c < 8; c++){      //corrigindo bug da peça 2
        pecaGerada.grid1[0][c] = 0;
    }
    
    //2
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 8; c++){
            pecaGerada.grid2[l][c] = 0;
        }
    }
    if(inicioLinUm>=0){
        for(int i = inicioLinUm/2 ; i <= fimLinUm/2; i++){
            for(int j=2;j<=3;j++){
                pecaGerada.grid2[i][j+2] = idPeca+2;
            }
        }
    }
    if(inicioLinDois>=0){
        for(int i = inicioLinDois/2 ; i <= fimLinDois/2; i++){
            for(int j=0;j<=1;j++){
                pecaGerada.grid2[i][j+2] = idPeca+2;
            }
        }
    }
    

    //3
    for(int l = 0; l < 4; l++){
        for(int c = 0; c < 8; c++){
            pecaGerada.grid3[l][c] = 0;
        }
    }
    int _num=0;
    if((pecaGerada.grid1[1][7]==0 && pecaGerada.grid1[2][7]==0) && !(pecaGerada.grid1[1][1]==0 && pecaGerada.grid1[2][1]==0)) _num=2; // se primeira coluna preenchida e últiima não, puxa para a esquerda
    for(int i = 7, j=0; i >= 0; i--, j++){
        pecaGerada.grid3[1][i-_num] = pecaGerada.grid1[2][j];
        pecaGerada.grid3[2][i-_num] = pecaGerada.grid1[1][j];
    }

    //4
    _num=0;
    if((pecaGerada.grid1[1][7]==0 && pecaGerada.grid1[2][7]==0) && !(pecaGerada.grid1[1][1]==0 && pecaGerada.grid1[2][1]==0)) _num=1; // se primeira coluna preenchida e últiima não, puxa para cima
    for(int k=0, l=3;k<4;k++,l--){
        for(int i = 7, j=0; i >= 0; i--, j++){
            pecaGerada.grid4[k-_num][i-(_num*2)] = pecaGerada.grid2[l][j];
            if(_num==1){
                if(k==3) pecaGerada.grid4[k][i] = 0;
                if(i==6||i==7) pecaGerada.grid4[k][i] = 0;
            }
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
void copiaMatriz(int l, int c, int matrizCopia[l][c], int matrizEnt[l][c]){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            matrizCopia[i][j] = matrizEnt[i][j];
        }
    }
}
int colisao(peca pecaAtual, int mov, int hor_ver, int matrizFonte[TAMANHO][TAMANHO], int yy, int xx){
    int colide=0;
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);
    if(hor_ver==0){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++){
                if(pecaMatriz[i][j]!=0 && (matrizFonte[yy+i][xx+j+mov]<0 || xx+j+mov>=TAMANHO || xx+j+mov<0)){
                    colide = 1;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++){
                if(pecaMatriz[i][j]!=0 && (matrizFonte[yy+i+mov][xx+j]<0 || yy+i+mov>=TAMANHO ||  yy+i+mov<0)){
                    colide = 1;
                }
            }
        }
    }
    return colide;
}
int colGiro(peca pecaAtual, int orientacao, int matrizFonte[TAMANHO][TAMANHO], int yy, int xx){
    int colide=0;
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, orientacao);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(pecaMatriz[i][j]!=0 && yy+i<0 || (yy+i>=TAMANHO || xx+j<0 || xx+j>=TAMANHO)){
                colide=1;
            }
            if(pecaMatriz[i][j]!=0 && matrizFonte[yy+i][xx+j]<0){
                colide = 1;
            }
        }
    }
    return colide;
}
void limpar(int matrizFonte[TAMANHO][TAMANHO]){
    int cheia;
    int linha;
    for(int linMax=0;linMax<4;linMax++){
        for(int l=TAMANHO-1;l>0;l--){
            cheia=1;
            for(int c=0;c<TAMANHO;c++){
                if(matrizFonte[l][c]==0){
                    cheia=0;
                    break;
                }
            }
            if(cheia==1){
                linha=l;
                break;
            }
        }
        if(cheia==1){
            for(int c=0;c<TAMANHO;c++){
                matrizFonte[linha][c]=0;
            }
            for(int l=linha;l>0;l--){
                for(int c=0;c<TAMANHO;c++){
                    matrizFonte[l][c]=matrizFonte[l-1][c];
                }
            }
        }
    }
}
void matrizProvisoria(peca pecaAtual, int pecaMatriz[4][8], int ord){
    switch(ord){
        case 1:
            copiaMatriz(4, 8, pecaMatriz, pecaAtual.grid1);
        break;
        case 2:
            copiaMatriz(4, 8, pecaMatriz, pecaAtual.grid2);
        break;
        case 3:
            copiaMatriz(4, 8, pecaMatriz, pecaAtual.grid3);
        break;
        case 4:
            copiaMatriz(4, 8, pecaMatriz, pecaAtual.grid4);
        break;
    }
}
int gameover(int matrizFonte[TAMANHO][TAMANHO]){
    for(int c=0;c<TAMANHO;c++){
        if(matrizFonte[0][c]<0){
            return 1;
        }
    }
    return 0;
}