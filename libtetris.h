#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include<stdio.h>

typedef struct peca{ // Guarda o grid de cada peça
    int orientacao;
    int grid1[4][8];
    int grid2[4][8];
    int grid3[4][8];
    int grid4[4][8];
}peca;

void imprimePeca(int fonte[20][20], peca pecaAtual, int linRef, int colRef);
void limpaPeca(int fonte[20][20], peca pecaAtual, int linRef, int colRef);
static struct peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois, int idPeca);
void geraPecas(peca pecasGeradas[]);

#endif