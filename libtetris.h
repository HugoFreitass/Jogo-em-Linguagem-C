#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMANHO 20

typedef struct peca{ // Guarda o grid de cada peça
    int orientacao;
    int grid1[4][8];
    int grid2[4][8];
    int grid3[4][8];
    int grid4[4][8];
}peca;

void mostraTabuleiro(int fonteMatriz[TAMANHO][TAMANHO], int startPos, int startAlt, int pontos, int level, peca proxPeca, int trocar, peca trocarPeca, int highscore, int game);
void imprimePeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef, int mod);
void limpaPeca(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef);
static struct peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois, int idPeca);
void geraPecas(peca pecasGeradas[]);
static void copiaMatriz(int l, int c, int matrizCopia[l][c], int matrizEnt[l][c]);
int colisao(peca pecaAtual, int mov, int hor_ver, int matrizFonte[TAMANHO][TAMANHO], int linRef, int colRef);
int colGiro(peca pecaAtual, int orientacao, int matrizFonte[TAMANHO][TAMANHO], int linRef, int colRef);
int limpar(int matrizFonte[TAMANHO][TAMANHO]);
static void matrizProvisoria(peca pecaAtual, int pecaMatriz[4][8], int orientacao);
int gameover(int matrizFonte[TAMANHO][TAMANHO]);
void imprimePreview(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef);
void limpaPreview(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef);

#endif