#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include<stdio.h>

typedef struct peca{ // Guarda o grid de cada peça
    int orientacao;
    int grid[2][8];
}peca;

void geraTabuleiro(int v[22][22], char tabuleiro[22][22]);
void imprimePeca(int fonte[22][22], peca pecaAtual, int linRef, int colRef);
void limpaPeca(int fonte[22][22], peca pecaAtual, int linRef, int colRef);
static struct peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois);
void geraPecas(peca pecasGeradas[]);

#endif