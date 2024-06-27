#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include<stdio.h>

#define TAMANHO 20

typedef struct peca{ // Guarda o grid de cada peça
    int orientacao;
    int grid[2][8];
}peca;

void geraTabuleiro(int v[TAMANHO][TAMANHO], char tabuleiro[TAMANHO][TAMANHO]);
void imprimePeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef);
void limpaPeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef);
static struct peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois);
void geraPecas(peca pecasGeradas[]);

#endif