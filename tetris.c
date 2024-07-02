#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "libtetris.h" //biblioteca própria

//cores personalizadas para o ncurses
#define COLOR_ORANGE 8
#define COLOR_GRAY 9

int main() {
    int matrizFonte[TAMANHO][TAMANHO] = {0}; //matriz do tabuleiro
    peca pecas[8]; //array de structs das peça
    srand(time(NULL)); //randomiza a seed de acordo co o tempo
    setlocale(LC_ALL, "");  //permite o uso de caracteres especiais
    initscr();              // Inicia a janela ncurses
    curs_set(0); //esconde o cursor

    //configuração das cores
    start_color();
    init_color(COLOR_ORANGE, 1000, 350, 0);
    init_color(COLOR_GRAY, 300, 300, 300);
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_ORANGE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_GRAY, COLOR_BLACK);

    cbreak();               // Desabilita o buffer da linha
    noecho();               // Não exibe a tecla pressionada
    keypad(stdscr, TRUE);   // Habilita a captura de teclas especiais
    geraPecas(pecas);       // Gera e salva as peças no vetor

    int game=-1, fechar=0; //controle de estados do jogo
    int ch=0; //tecla pressionada
    
    //declaração das peças
    int pecaSorteada = rand() % 7; 
    int proxPeca =  rand() % 7;       
    int temTroca=0;              
    int trocarPeca = 0;            
    int ativarTroca=1;              
    int tempPeca;   

    //controle das peças
    int nextOr=2, contador=0;
    int xpad = 6, ypad = -1;
    int x = xpad, y = ypad;
    int xinicial, yinicial;

    //colisões
    int colh = 0, colv =0, colg=0;

    //pontuação
    int pontos=0, level=1, pontosPorLevel=1000;
    int highscore=0, novoHigh=0;

    //delay
    int delayPad=300/level, delay=delayPad, delayFast=delayPad/20;

    //posições para imprimir na tela
    int meio = stdscr->_maxx/2;
    int startPos=meio-11; //posicão x inicial do tabuleiro
    int fonteAltDiff=15; 
    int startAlt=((meio*2)/1.7)/4-fonteAltDiff; //posicão y inicial do tabuleiro
    int titleAlt=5;
    int titlePos=meio-40;

    //controle das cores no menu inicial
    int colors[7]={1,5,3,7,2,4,6};
    int colorMod=0;
    int reset=1;

    //repetição principal
    while(fechar==0){
        //alteração de estados do jogo de acordo com a variável game
        switch(game){

            //menu
            case -1:
                //título e texto
                titlePos=meio-40;
                titleAlt=((meio*2)/1.7)/4-15;
                attron(COLOR_PAIR(colors[(0+colorMod)%7]));
                mvaddstr(0+titleAlt,  0+titlePos,"     ___           ___        ___           ___                       ___     ");
                attron(COLOR_PAIR(colors[(1+colorMod)%7]));
                mvaddstr(1+titleAlt,  0+titlePos,"    /\\  \\         /\\  \\      /\\  \\         /\\  \\          ___        /\\  \\");
                attron(COLOR_PAIR(colors[(2+colorMod)%7]));
                mvaddstr(2+titleAlt,  0+titlePos,"    \\:\\  \\       /::\\  \\     \\:\\  \\       /::\\  \\        /\\  \\      /::\\  \\   ");
                attron(COLOR_PAIR(colors[(3+colorMod)%7]));
                mvaddstr(3+titleAlt,  0+titlePos,"     \\:\\  \\     /:/\\:\\  \\     \\:\\  \\     /:/\\:\\  \\       \\:\\  \\    /:/\\ \\  \\  ");
                attron(COLOR_PAIR(colors[(4+colorMod)%7]));
                mvaddstr(4+titleAlt,  0+titlePos,"     /::\\  \\   /::\\~\\:\\  \\    /::\\  \\   /::\\~\\:\\  \\      /::\\__\\  _\\:\\~\\ \\  \\ ");
                attron(COLOR_PAIR(colors[(5+colorMod)%7]));
                mvaddstr(5+titleAlt,  0+titlePos,"    /:/\\:\\__\\ /:/\\:\\ \\:\\__\\  /:/\\:\\__\\ /:/\\:\\ \\:\\__\\  __/:/\\/__/ /\\ \\:\\ \\ \\__\\");
                attron(COLOR_PAIR(colors[(6+colorMod)%7]));
                mvaddstr(6+titleAlt,  0+titlePos,"   /:/  \\/__/ \\:\\~\\:\\ \\/__/ /:/  \\/__/ \\/_|::\\/:/  / /\\/:/  /    \\:\\ \\:\\ \\/__/");
                attron(COLOR_PAIR(colors[(7+colorMod)%7]));
                mvaddstr(7+titleAlt,  0+titlePos,"  /:/  /       \\:\\ \\:\\__\\  /:/  /         |:|::/  /  \\::/__/      \\:\\ \\:\\__\\  ");
                attron(COLOR_PAIR(colors[(8+colorMod)%7]));
                mvaddstr(8+titleAlt,  0+titlePos,"  \\/__/         \\:\\ \\/__/  \\/__/          |:|\\/__/    \\:\\__\\       \\:\\/:/  /  ");
                attron(COLOR_PAIR(colors[(9+colorMod)%7]));
                mvaddstr(9+titleAlt,  0+titlePos,"                 \\:\\__\\                   |:|  |       \\/__/        \\::/  /   ");
                attron(COLOR_PAIR(colors[(10+colorMod)%7]));
                mvaddstr(10+titleAlt, 0+titlePos,"                  \\/__/                    \\|__|                     \\/__/    ");
                attroff(COLOR_PAIR(colors[(10+colorMod)%7]));
                titlePos=meio-20;
                mvaddstr(13+titleAlt, 0+titlePos,"► Pressione a tecla espaço para iniciar ◄");
                titlePos=meio-17;
                mvaddstr(15+titleAlt, 0+titlePos,"► Pressione a tecla esc para sair ◄");
                attron(COLOR_PAIR(4));
                titlePos=meio-7;
                mvaddstr(19+titleAlt, 0+titlePos,"♦ Controles: ♦");
                attroff(COLOR_PAIR(4));
                titlePos=meio-9;
                mvaddstr(20+titleAlt, 0+titlePos,"← & →: Movimentação");
                titlePos=meio-9;
                mvaddstr(21+titleAlt, 0+titlePos,"↑: Rotacionar peça");
                titlePos=meio-7;
                mvaddstr(22+titleAlt, 0+titlePos,"↓: Queda suave");
                titlePos=meio-10;
                mvaddstr(23+titleAlt, 0+titlePos,"Espaço: Queda brusca");
                titlePos=meio-8;
                mvaddstr(24+titleAlt, 0+titlePos,"'C': Trocar peça");
                titlePos=meio-16;
                mvaddstr(26+titleAlt, 0+titlePos,"Por: Arthur Davel e Hugo Freitas");
                mvaddstr(27+titleAlt, 0+titlePos,"");//reposiciona o ponteiro
                refresh();
                usleep(300*1000); //taxa de atualização
                if(meio!=stdscr->_maxx/2){ //recalcula a posição de impressão na tela se o tamanho da janela for alterada
                    clear();
                    meio = stdscr->_maxx/2;
                    startPos=meio-11;
                    startAlt=((meio*2)/1.7)/4-fonteAltDiff;
                }
                colorMod++;
                colorMod%=7;
                //opções
                timeout(1);
                ch = getch();
                switch(ch){
                    case ' ':
                        clear();
                        refresh();
                        game=1;
                        break;
                    break;
                    case 27:
                        clear();
                        refresh();
                        fechar=1;
                        break;
                    break;
                }
            break;

            //jogo
            case 1:
                if(reset==0){   //reseta o tabuleiro
                    for(int lin=0;lin<TAMANHO;lin++){
                        for(int col=0;col<TAMANHO;col++){
                            matrizFonte[lin][col] = 0;
                        }
                    }
                    pecaSorteada = rand() % 7,
                    proxPeca =  rand() % 7;
                    pecas[pecaSorteada].orientacao=1;
                    x=xpad;
                    y=ypad;
                    ativarTroca=1;
                    temTroca = 0;
                    pontos=0, level=1, pontosPorLevel=1000;
                    delayPad=300/level, delay=delayPad, delayFast=delayPad/20;
                    meio = stdscr->_maxx/2;
                    startPos=meio-11;
                    startAlt=((meio*2)/1.7)/4-fonteAltDiff;
                    reset=1;
                }
                contador=0;
                imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
                mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);
                while(1){
                    timeout(1);
                    ch = getch();
                    switch(ch){
                        case KEY_LEFT:
                            // Move a peça para a esquerda
                            colh=colisao(pecas[pecaSorteada], -2, 0, matrizFonte, y, x);
                            if(colh==0){
                                limpaPreview(matrizFonte, pecas[pecaSorteada], y, x);
                                limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                                x-=2;
                            }
                        break;
                        case KEY_RIGHT:
                            // Move peça para a direita
                            colh=colisao(pecas[pecaSorteada], 2, 0, matrizFonte, y, x);
                            if(colh==0){
                                limpaPreview(matrizFonte, pecas[pecaSorteada], y, x);
                                limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                                x+=2;
                            }
                        break;
                        case KEY_UP:
                            //gira a peça
                            nextOr=(pecas[pecaSorteada].orientacao+1)%5;
                            if(nextOr==0) nextOr=1;
                            colg=colGiro(pecas[pecaSorteada], nextOr, matrizFonte, y, x);
                            if(colg==0 && y>=0){
                                limpaPreview(matrizFonte, pecas[pecaSorteada], y, x);
                                limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                                pecas[pecaSorteada].orientacao=nextOr;
                            }
                        break;
                        case KEY_DOWN:
                            delay=delayFast;
                        break;
                        case ' ':
                            xinicial=x;
                            yinicial=y;
                            colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                            while(colv==0){
                                colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                                if(colv==0){
                                    y++;
                                    pontos++;
                                }
                            }
                            limpaPreview(matrizFonte, pecas[pecaSorteada], y, x);
                            limpaPeca(matrizFonte, pecas[pecaSorteada], yinicial, xinicial);
                            delay=0;
                        break;
                        case 'c':
                            if(ativarTroca==1){
                                limpaPreview(matrizFonte, pecas[pecaSorteada], y, x);
                                limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                                if(temTroca==0){
                                    trocarPeca=pecaSorteada;
                                    pecaSorteada=proxPeca;
                                    proxPeca=rand()%7;
                                    temTroca=1;
                                }
                                else{
                                    tempPeca=trocarPeca;
                                    trocarPeca=pecaSorteada;
                                    pecaSorteada=tempPeca;
                                }
                                pecas[pecaSorteada].orientacao=1;
                                x=xpad;
                                y=ypad;
                                ativarTroca=0;
                            }
                        break;
                    }
                    imprimePreview(matrizFonte, pecas[pecaSorteada], y, x);
                    imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
                    mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);
                    sleep(0.001);
                    contador+=1;
                    if(contador>=delay){
                        break;
                    }
                }
                if(colv==1){
                    colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                    if(colv==1){
                        delay=delayPad;
                        imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, -1);
                        pontos+=limpar(matrizFonte);
                        game=!gameover(matrizFonte);
                        if(game==0) break;
                        pecaSorteada = proxPeca;
                        proxPeca = rand() % 7;
                        ativarTroca=1;
                        pecas[pecaSorteada].orientacao=1;
                        x = xpad;
                        y = ypad;
                        colh = 0;
                        colv = 0;
                        colg = 0;
                        continue;
                    }
                }
                colv=colisao(pecas[pecaSorteada], 1, 1, matrizFonte, y, x);
                if(colv==0){
                    limpaPeca(matrizFonte, pecas[pecaSorteada], y, x);
                    y++;
                    if(delay==delayFast){
                        pontos++;
                    }
                    imprimePeca(matrizFonte, pecas[pecaSorteada], y, x, 1);
                }    
                delayPad=300/level;
                level=1+pontos/pontosPorLevel;
                delayFast=delayPad/20;
                delay=delayPad;
                if(meio!=stdscr->_maxx/2){
                    mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);
                    clear();
                    meio = stdscr->_maxx/2;
                    startPos=meio-11;
                    startAlt=((meio*2)/1.7)/4-fonteAltDiff;
                }
                mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);   
            break;

            //acabou de perder
            case 0:
                if(meio!=stdscr->_maxx/2){
                    mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);
                    clear();
                    meio = stdscr->_maxx/2;
                    startPos=meio-11;
                    startAlt=((meio*2)/1.7)/4-fonteAltDiff;
                }
                mostraTabuleiro(matrizFonte, startPos, startAlt, pontos, level, pecas[proxPeca], temTroca, pecas[trocarPeca], highscore, game);
                if(pontos>highscore){
                    highscore=pontos;
                    novoHigh=1;
                }
                sleep(3);
                clear();
                refresh();
                reset=0;
                game=2;
            break;

            //game over
            case 2:
                titlePos=meio-31;
                titleAlt=((meio*2)/1.7)/4-6;
                attron(COLOR_PAIR(6));
                mvaddstr(0+titleAlt,  0+titlePos,"  _____          __  __ ______    ______      ________ _____  ");
                mvaddstr(1+titleAlt,  0+titlePos," / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
                mvaddstr(2+titleAlt,  0+titlePos,"| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
                mvaddstr(3+titleAlt,  0+titlePos,"| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ");
                mvaddstr(4+titleAlt,  0+titlePos,"| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
                mvaddstr(5+titleAlt,  0+titlePos," \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
                attroff(COLOR_PAIR(6));
                titlePos=meio-9;
                mvprintw(8+titleAlt, 0+titlePos,"♦ PONTUAÇÃO: %d ♦", pontos);
                if(novoHigh==1){
                    titlePos=meio-8;
                    mvaddstr(10+titleAlt, 0+titlePos,"» Novo recorde! «");
                }
                titlePos=meio-22;
                mvaddstr(12+titleAlt, 0+titlePos,"► Pressione a tecla R para retornar ao menu ◄");
                mvaddstr(23+titleAlt, 0+titlePos,"");
                refresh();
                usleep(300*1000);
                if(meio!=stdscr->_maxx/2){
                    clear();
                    meio = stdscr->_maxx/2;
                    startPos=meio-11;
                    startAlt=((meio*2)/1.7)/4-fonteAltDiff;
                }
                timeout(1);
                ch = getch();
                if(ch=='r'){
                    clear();
                    refresh();
                    novoHigh=0;
                    game=-1;
                    break;
                }
            break;
        }                   //fecha o switch
    }                       //fecha o while
    endwin();               // Finaliza o ncurses
    return 0;
}                           //fecha a main