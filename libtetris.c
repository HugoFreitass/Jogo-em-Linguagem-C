#include "libtetris.h"

void mostraTabuleiro(int fonteMatriz[TAMANHO][TAMANHO], int startPos, int startAlt, int pontos, int nivel, peca proxPeca, int trocar, peca trocarPeca, int highscore, int game){
    int cor;
    int distTitle=6;
    attron(COLOR_PAIR(6));
    mvaddstr(0+startAlt,  0+startPos-distTitle," ___ ");
    mvaddstr(1+startAlt,  0+startPos-distTitle,"|_ _|");
    mvaddstr(2+startAlt,  0+startPos-distTitle," | | ");
    mvaddstr(3+startAlt,  0+startPos-distTitle," |_| ");
    attron(COLOR_PAIR(4));
    mvaddstr(4+startAlt,  0+startPos-distTitle," ___ ");
    mvaddstr(5+startAlt,  0+startPos-distTitle,"| __>");
    mvaddstr(6+startAlt,  0+startPos-distTitle,"| _> ");
    mvaddstr(7+startAlt,  0+startPos-distTitle,"|___>");
    attron(COLOR_PAIR(2));
    mvaddstr(8+startAlt,  0+startPos-distTitle," ___ ");
    mvaddstr(9+startAlt,  0+startPos-distTitle,"|_ _|");
    mvaddstr(10+startAlt, 0+startPos-distTitle," | | ");
    mvaddstr(11+startAlt, 0+startPos-distTitle," |_| ");
    attron(COLOR_PAIR(7));
    mvaddstr(12+startAlt, 0+startPos-distTitle," ___ ");
    mvaddstr(13+startAlt, 0+startPos-distTitle,"| . \\");
    mvaddstr(14+startAlt, 0+startPos-distTitle,"|   /");
    mvaddstr(15+startAlt, 0+startPos-distTitle,"|_\\_\\");
    attron(COLOR_PAIR(3));
    mvaddstr(16+startAlt, 0+startPos-distTitle,"  _ ");
    mvaddstr(17+startAlt, 0+startPos-distTitle," | |");
    mvaddstr(18+startAlt, 0+startPos-distTitle," | | ");
    mvaddstr(19+startAlt, 0+startPos-distTitle," |_| ");
    attron(COLOR_PAIR(1));
    mvaddstr(20+startAlt, 0+startPos-distTitle," ___ ");
    mvaddstr(21+startAlt, 0+startPos-distTitle,"/ __>");
    mvaddstr(22+startAlt, 0+startPos-distTitle,"\\__ \\");
    mvaddstr(23+startAlt, 0+startPos-distTitle,"<___/");
    attroff(COLOR_PAIR(1));
    for(int l = 0; l < TAMANHO; l++){
        mvaddstr(l+1+startAlt, 0+startPos,"║");
        for(int c = 0; c < TAMANHO; c++){
            mvaddstr(0+startAlt, c+1+startPos,"═");
            int fonteNova=fonteMatriz[l][c];
            if(fonteNova<0){//Lida com as peças fixas, após cair
                cor=(fonteNova*-1)-1;
            }
            else{
                cor=fonteNova-1;
            }
            attron(COLOR_PAIR(cor));
            switch(fonteNova){
                case 0:
                mvaddstr(l+1+startAlt, c+1+startPos, " ");
                break;
                default:
                mvaddstr(l+1+startAlt, c+1+startPos, "█");
                if(fonteMatriz[l][c]<0){
                    if(game==1){
                        mvaddstr(l+1+startAlt, c+1+startPos, "▒");
                    }
                    else{
                        mvaddstr(l+1+startAlt, c+1+startPos, "♯");
                    }
                }
                if(fonteMatriz[l][c]==9){ // Identifica o preview
                    mvaddstr(l+1+startAlt, c+1+startPos, "░");
                }
                break;
            }
            attroff(COLOR_PAIR(cor));
            mvaddstr(TAMANHO+1+startAlt, c+1+startPos,"═");
        }
        printw("\n");
        mvaddstr(l+1+startAlt, TAMANHO+1+startPos,"║");
    }
    mvaddstr(0+startAlt, 0+startPos,"╔");
    mvaddstr(0+startAlt, TAMANHO+1+startPos,"╗");
    mvaddstr(TAMANHO+1+startAlt, TAMANHO+1+startPos,"╣");
    mvaddstr(TAMANHO+1+startAlt, 0+startPos,"╠");
    mvaddstr(TAMANHO+2+startAlt, 0+startPos, "║"); //Reposiciona o ponteiro
    mvprintw(TAMANHO+2+startAlt, 1+startPos," ► NÍVEL: %d", nivel);
    mvaddstr(TAMANHO+2+startAlt, TAMANHO+1+startPos,"║");
    mvaddstr(TAMANHO+3+startAlt, 0+startPos, "║");
    mvprintw(TAMANHO+3+startAlt, 1+startPos," ► PONTUAÇÃO: %d", pontos);
    mvaddstr(TAMANHO+3+startAlt, TAMANHO+1+startPos,"║");
    mvaddstr(TAMANHO+4+startAlt, 0+startPos, "╚");
    for(int c = 0; c < TAMANHO; c++){
        mvaddstr(TAMANHO+4+startAlt, c+1+startPos,"═");
    }
    mvaddstr(TAMANHO+4+startAlt, TAMANHO+1+startPos,"╝");
    mvaddstr(startAlt, TAMANHO+3+startPos,"╔");
    for(int c = 0; c < 10; c++){
        mvaddstr(startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(startAlt, TAMANHO+14+startPos,"╗");
    mvaddstr(1+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(1+startAlt, TAMANHO+4+startPos," PRÓXIMA▼ ");
    mvaddstr(1+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(2+startAlt, TAMANHO+3+startPos,"╠");
    for(int c = 0; c < 10; c++){
        mvaddstr(2+startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(2+startAlt, TAMANHO+14+startPos,"╣");
    mvaddstr(3+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(3+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(4+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(4+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(5+startAlt, TAMANHO+3+startPos,"╚");
    for(int c = 0; c < 10; c++){
        mvaddstr(5+startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(5+startAlt, TAMANHO+14+startPos,"╝");
    attron(COLOR_PAIR(cor));
    for(int l = 1; l < 3; l++){
            for(int c = 0; c < 8; c++){
                if(proxPeca.grid1[l][c]>0)
                {
                    cor=proxPeca.grid1[l][c]-1;
                    attron(COLOR_PAIR(cor));
                    mvaddstr(2+startAlt+l, TAMANHO+c+5+startPos,"█"); 
                    attroff(COLOR_PAIR(cor));
                }
                else{
                    mvaddstr(2+startAlt+l, TAMANHO+c+5+startPos," ");
                }
            }
        }
    //Hold
    startAlt+=6;
    mvaddstr(startAlt, TAMANHO+3+startPos,"╔");
    for(int c = 0; c < 10; c++){
        mvaddstr(startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(startAlt, TAMANHO+14+startPos,"╗");
    mvaddstr(1+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(1+startAlt, TAMANHO+4+startPos," TROCAR ▼ ");
    mvaddstr(1+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(2+startAlt, TAMANHO+3+startPos,"╠");
    for(int c = 0; c < 10; c++){
        mvaddstr(2+startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(2+startAlt, TAMANHO+14+startPos,"╣");
    mvaddstr(3+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(3+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(4+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(4+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(5+startAlt, TAMANHO+3+startPos,"╚");
    for(int c = 0; c < 10; c++){
        mvaddstr(5+startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(5+startAlt, TAMANHO+14+startPos,"╝");
    if(trocar==1){
        for(int l = 1; l < 3; l++){
            for(int c = 0; c < 8; c++){
                if(trocarPeca.grid1[l][c]>0)
                {
                    cor=trocarPeca.grid1[l][c]-1;
                    attron(COLOR_PAIR(cor));
                    mvaddstr(2+startAlt+l, TAMANHO+c+5+startPos,"█"); 
                    attroff(COLOR_PAIR(cor));
                }
                else{
                    mvaddstr(2+startAlt+l, TAMANHO+c+5+startPos," ");
                }
            }
        }
    }
    startAlt+=6;
    mvaddstr(startAlt, TAMANHO+3+startPos,"╔");
    for(int c = 0; c < 10; c++){
        mvaddstr(startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(startAlt, TAMANHO+14+startPos,"╗");
    mvaddstr(1+startAlt, TAMANHO+3+startPos,"║");
    mvaddstr(1+startAlt, TAMANHO+4+startPos," RECORDE▼ ");
    mvaddstr(1+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(2+startAlt, TAMANHO+3+startPos,"║");
    mvprintw(2+startAlt, TAMANHO+4+startPos," %d", highscore);
    mvaddstr(2+startAlt, TAMANHO+14+startPos,"║");
    mvaddstr(3+startAlt, TAMANHO+3+startPos,"╚");
    for(int c = 0; c < 10; c++){
        mvaddstr(3+startAlt, TAMANHO+c+4+startPos,"═");
    }
    mvaddstr(3+startAlt, TAMANHO+14+startPos,"╝");
    refresh();
}

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
    if((pecaGerada.grid1[1][7]==0 && pecaGerada.grid1[2][7]==0) && !(pecaGerada.grid1[1][1]==0 && pecaGerada.grid1[2][1]==0)) _num=2; // se primeira coluna preenchida e última não, puxa para a esquerda
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

static void copiaMatriz(int l, int c, int matrizCopia[l][c], int matrizEnt[l][c]){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            matrizCopia[i][j] = matrizEnt[i][j];
        }
    }
}

int colisao(peca pecaAtual, int mov, int hor_ver, int matrizFonte[TAMANHO][TAMANHO], int linRef, int colRef){
    int colide=0;
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);
    if(hor_ver==0){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++){
                if(pecaMatriz[i][j]!=0 && (matrizFonte[linRef+i][colRef+j+mov]<0 || colRef+j+mov>=TAMANHO || colRef+j+mov<0)){
                    return 1;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++){
                if(pecaMatriz[i][j]!=0 && (matrizFonte[linRef+i+mov][colRef+j]<0 || linRef+i+mov>=TAMANHO ||  linRef+i+mov<0)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int colGiro(peca pecaAtual, int orientacao, int matrizFonte[TAMANHO][TAMANHO], int linRef, int colRef){
    //return 1 == colidiu
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, orientacao);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(pecaMatriz[i][j]!=0){ //Ignora espacos vazios do grid da peca
                if(matrizFonte[linRef+i][colRef+j]<0){
                    return 1;
                }
                if((linRef+i<0 || linRef+i>=TAMANHO || colRef+j<0 || colRef+j>=TAMANHO)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int limpar(int matrizFonte[TAMANHO][TAMANHO]){
    int cheia;
    int linha;
    int linhasApagadas=0;
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
            linhasApagadas++;
        }
    }
    switch(linhasApagadas){
        case 1:
            return 100;
        break;
        case 2:
            return 300;
        break;
        case 3:
            return 500;
        break;
        case 4:
            return 800;
        break;
        default:
            return 0;
        break;
    }
}

static void matrizProvisoria(peca pecaAtual, int pecaMatriz[4][8], int orientacao){
    switch(orientacao){
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

void imprimePreview(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef){
    int yPrev=linRef;
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);//Copia o grid da orientação fornecida
    int colv=colisao(pecaAtual, 1, 1, fonte, yPrev, colRef);
    while(colv==0){
        colv=colisao(pecaAtual, 1, 1, fonte, yPrev, colRef);
        if(colv==0){
            yPrev++;
        }
    }
    for(int l = yPrev, j = 0; l < yPrev + 4; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            if(pecaMatriz[j][k]>0 && fonte[l][c]>=0){
                fonte[l][c] = 9;
            }
        }
    }
}
void limpaPreview(int fonte[TAMANHO][TAMANHO], peca pecaAtual, int linRef, int colRef){
    int yPrev=linRef;
    int pecaMatriz[4][8];
    matrizProvisoria(pecaAtual, pecaMatriz, pecaAtual.orientacao);
    int colv=colisao(pecaAtual, 1, 1, fonte, yPrev, colRef);
    while(colv==0){
        colv=colisao(pecaAtual, 1, 1, fonte, yPrev, colRef);
        if(colv==0){
            yPrev++;
        }
    }
    for(int l = yPrev, j = 0; l < yPrev + 4; l++, j++){
        for(int c = colRef, k = 0; c < colRef + 8; c++, k++){
            if(pecaMatriz[j][k]>0 && fonte[l][c]>=0){
                fonte[l][c] = 0;
            }
        }
    }
}