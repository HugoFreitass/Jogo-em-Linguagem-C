#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include<stdio.h>

void geraTabuleiro(int v[22][22], char tabuleiro[22][22]);
struct peca configuraPeca(int inicioLinUm, int fimLinUm, int inicioLinDois, int fimLinDois);
struct peca geraPecas(int idPeca);

#endif