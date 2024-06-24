#include <stdio.h>

//#define bloco1 '\xe2\x96\x88'
#define bloco1 "\u2588";
#define bloco2 ' ' 

typedef struct{ // Guarda o grid de cada peça
    int orientacao;
    int grid[2][8];
}peca;

void geraTabuleiro(int v[22][22], char tabuleiro[22][22]){
    // Tabuleiro 20 x 10
    // Definir macros para facilitar mudanças de tamanho
    
    for(int l = 0; l < 22; l++){
        for(int c = 0; c < 22; c++){
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && v[l][c] == 0) tabuleiro[l][c] = bloco2;
            if(l != 0 && l != 21 &&  c != 0 && c!= 21 && v[l][c] == 2) tabuleiro[l][c] = *bloco1;
            if((l == 0 || l == 21) && c != 0 && c!= 21) tabuleiro[l][c] = '-';
            if(c == 0 || c == 21) tabuleiro[l][c] = '|';
        }
    }
}

// Gera a posicao inicial da peça
peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois){
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


peca geraPecas(int idPeca){
    // switch para selecionar a peça
    peca pecaGerada;
    pecaGerada.orientacao = 1;
    switch (idPeca){
    case 1:
        //  00
        //000000
        pecaGerada = configuraPeca(2, 3, 0, 5);
        break;
    case 2:
        //  0000
        //  0000
        pecaGerada = configuraPeca(2, 5, 2, 5);
        break;
    case 3:
        //
        //00000000
        pecaGerada = configuraPeca(-1, -1, 0, 7);
        break;
    case 4:
        //    00
        //000000
        pecaGerada = configuraPeca(4, 5, 0, 5);
        break;
    case 5:
        //00
        //000000
        pecaGerada = configuraPeca(0, 1, 0, 5);
        break;
    case 6:
        //0000
        //  0000
        pecaGerada = configuraPeca(0, 3, 2, 5);
        break;
    case 7:
        //  0000
        //0000
        pecaGerada = configuraPeca(2, 5, 0, 3);
        break;
    default:
        pecaGerada = configuraPeca(-1, -1, -1, -1); // Talvez seja desnecessário
        break;
    }

    return pecaGerada;
}