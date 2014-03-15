/*Windows 3.1 dominate remake and adapted for local multiplayer.*/
//@joseluizpf

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "verticesQuadrado.h"
#include "printaPossibilidades.h"
#include "clicouEmQuadrado.h"
#include "arrumaVetor.h"
#include "loopJogada.h"

#define LADO_QUADRADO 75
#define ESPACO_QUADRADO 10
#define MAX_X 800
#define MAX_Y 600
#define CAIXA_CONTAGEM_X 180
#define CAIXA_CONTAGEM_Y 180

//GLOBAL
volatile long int counterMiliSeg = 0;

//PROTÓTIPOS
void contadorTiles(char preenchidos[][8], int *nroPreto, int *nroBranco);
void printaTabuleiro(int COORDQuadrado[9],int espacoEntreQuadrado,BITMAP *buffer);
int validezQuadrado(int coordMouse[2],char jogador,char preenchidos[][8]);
void printaTiles(int COORDQuadrado[9],char preenchidos[][8],BITMAP *buffer,BITMAP *player1,BITMAP *player2);
void delayMouse(void);

//===============================================================================================================================
void localMPloop(void)
{
    // Declarações de variáveis
    BITMAP *player1;
    BITMAP *player2;
    BITMAP *buffer;

    int COORDQuadrado[9], i = 0, p = 0;
    char preenchidos[8][8];
    int coordMouse[2];
    int x,y, valido = 0;
    int rodada = 0; //se for par é o jogador 'b' e ímpar é o 'p'.
    char jogador;
    int cliqueDentroQuadrado;
    int apagarTileOrigem;
    int fimDoTabuleiroX;
    int xTroca = 8, yTroca = 8; //8 pois o 7 é a ultima posição valida do tabuleiro para o x e y;
    int nroPreto= 2,nroBranco = 2; //usado para guardar o numero de preto e brancos em cada rodada;

//PREPARAÇÃO
    buffer = create_bitmap(MAX_X, MAX_Y);

    //PREENCHENDO A VARIAVEL PREENCHIDOS
    for(i = 0; i < 8; i++) //torna todos os quadrados vazios
        for(p = 0; p < 8; p++)
        {
            preenchidos[i][p] = 'v';
        }

    fimDoTabuleiroX = (LADO_QUADRADO)*8+ESPACO_QUADRADO;

    verticesQuadrado(COORDQuadrado, LADO_QUADRADO, ESPACO_QUADRADO); //preenche as coordenadas do vértice dos quadrados

    //CARREGANDO AS IMAGENS DOS PLAYERS
    player1 = load_bitmap("imagens\\player1.bmp",NULL); //cria os modelos de quadrados
    player2 = load_bitmap("imagens\\player2.bmp",NULL);

    //INICIALIZANDO AS POSIÇÕES
    preenchidos[0][0] = 'b'; //poe na array os chars correspondentes a cor do quadrado preenchido
    preenchidos[7][7] = 'b';
    preenchidos[0][7] = 'p';
    preenchidos[7][0] = 'p';

    //PREPARANDO O DELAYMOUSE
    LOCK_VARIABLE(counterMiliSeg); //chama o delayMouse a cada milisegundo
    LOCK_FUNCTION(delayMouse);
    install_int(delayMouse, 1);

    //PRINTA TABULEIRO E TILES NO BUFFER E DEPOIS NA SCREEN
    textprintf_ex(buffer,font, fimDoTabuleiroX, ESPACO_QUADRADO, makecol(255,0,0),-1, "P: %i    B: %i", nroPreto, nroBranco);
    printaTabuleiro(COORDQuadrado, ESPACO_QUADRADO,buffer); //printa o tabuleiro no buffer
    printaTiles(COORDQuadrado, preenchidos, buffer, player1, player2); //printa os tiles no buffer
    blit(buffer, screen,0,0,0,0,MAX_X,MAX_Y); //printa o buffer na screen (double buffering)

// LOOP DO JOGO
    do
    {
        printaTabuleiro(COORDQuadrado, ESPACO_QUADRADO,buffer); //printa o tabuleiro no buffer de novo para printar apenas uma vez
        //no loop o buffer na screen!
        printaTiles(COORDQuadrado, preenchidos, buffer, player1, player2); //printa os tiles no buffer

        //JOGADORES
        if(rodada%2) //se a rodada for par ou impar atribui o char de quem joga (começa com o branco)
            jogador = 'p';
        else
            jogador = 'b';


        show_mouse(screen); //mostra o mouse na tela

        if(mouse_b & 1 && counterMiliSeg > 700) //se apertou o botao esquerdo e já se passaram 1/2seg desde a ultima vez que pressionou
        {
            printf("\n\n CLIQUEI FORA LOOP \n\n");

            x = mouse_x; //guarda a posição do mouse no instante do clique
            y = mouse_y;

            cliqueDentroQuadrado = clicouEmQuadrado(x, y, COORDQuadrado, coordMouse, ESPACO_QUADRADO); //verifica se está em algum quadrado e armazena as coord do quadrado no coordMouse


            if(cliqueDentroQuadrado)
            {
                valido = validezQuadrado(coordMouse, jogador, preenchidos); //verifica se foi clicado no quadrado branco ou preto

                if(valido)
                {
                    do{
                       if(xTroca == 8 && yTroca == 8)
                       {
                           printf("printeiPossibilidade;");
                            printaPossibilidades(coordMouse, COORDQuadrado, preenchidos, buffer);
                       }
                        else
                        {
                            printf("\n\nprinteiNovasPossibilidades\n\n");
                            coordMouse[0] = yTroca;
                            coordMouse[1] = xTroca;

                            /*Se trocou tem que printar tudo de novo na tela para apagar as possibilidades antigas*/
                            textprintf_ex(buffer,font, fimDoTabuleiroX, ESPACO_QUADRADO, makecol(255,0,0),-1, "P: %i    B: %i", nroPreto, nroBranco);
                            printaTabuleiro(COORDQuadrado, ESPACO_QUADRADO,buffer); //printa o tabuleiro no buffer de novo para printar apenas uma vez
                            //no loop o buffer na screen!
                            printaTiles(COORDQuadrado, preenchidos, buffer, player1, player2); //printa os tiles no buffer
                            printaPossibilidades(coordMouse, COORDQuadrado, preenchidos, buffer);

                            xTroca = 8;
                            yTroca = 8;
                        }

                    loopJogada(preenchidos, COORDQuadrado, jogador, &apagarTileOrigem, &xTroca, &yTroca); //chama o loop que faz as verificações necessárias e printa o tile escolhido pelo jogador

                    }while(xTroca != 8 || yTroca != 8); //se o player ficar trocando de opção deve se repetir o processo

                    if(apagarTileOrigem)
                    {
                        preenchidos[coordMouse[0]][coordMouse[1]] = 'v';
                        apagarTileOrigem = 0;
                    }

                    rodada++;
                }
            }
            counterMiliSeg = 0;
        }

        if(valido)
        {
        contadorTiles(preenchidos, &nroPreto, &nroBranco);

        //rectfill(buffer, fimDoTabuleiroX, ESPACO_QUADRADO, fimDoTabuleiroX+CAIXA_CONTAGEM_X, ESPACO_QUADRADO+CAIXA_CONTAGEM_Y, makecol(255,0,0 ) );
        }

        valido = 0;

        //sempre printa na tela o numero de pretos e brancos (mesmo que nao alterados)
        textprintf_ex(buffer,font, fimDoTabuleiroX, ESPACO_QUADRADO, makecol(255,0,0),-1, "P: %i    B: %i", nroPreto, nroBranco);


        //DOUBLE BUFFERING:
        scare_mouse(); //função que tira o mouse pra poder printar coisas na tela
        blit(buffer, screen,0,0,0,0,MAX_X,MAX_Y); //printa o buffer na screen
        unscare_mouse(); //poe o mouse de volta
        clear(buffer); //limpa o buffer para ser escrito novamente

        if (key[KEY_ESC])	break;
    }
    while(1);

}

//=============================================================================================================================================
/* Esta função pega as coordenadas dos vértices dos quadrados (que sao as coordenadas do x2 e y2) a partir do index 1.
    E somando ESPACO_QUADRADO temos o x1 e y1, a partir do index 0. */
void printaTabuleiro(int COORDQuadrado[9],int espacoEntreQuadrado,BITMAP *variavel)
{
    int i,p;

    for(i = 0; i < 8; i++)
    {
        for(p = 0; p < 8; p++)
        {
            rectfill(variavel, COORDQuadrado[i], COORDQuadrado[p], COORDQuadrado[i+1]-espacoEntreQuadrado, COORDQuadrado[p+1]-espacoEntreQuadrado, makecol(28,28,28));
            //faz o grid dos quadrados (+1 no x2 e y2 pois precisa acessar o valor do ultimo vértice que fica um index a frente)
        }
    }
}

//=============================================================================================================================================
int validezQuadrado(int coordMouse[2],char jogador,char preenchidos[][8])
{
    int i, p;
    int retorno = 0;

    i = coordMouse[0]; //i = linha de quadrados em que o mouse foi clicado, p = coluna;
    p = coordMouse[1];


    if(preenchidos[i][p] == jogador) //verifica se o quadrado clicado tem o char de jogador correto
        retorno = 1;


    return retorno;
}

//=============================================================================================================================
void printaTiles(int COORDQuadrado[9],char preenchidos[][8],BITMAP *buffer,BITMAP *player1,BITMAP *player2)
{
    int i = 0,p = 0;

    for(i = 0; i < 8; i++)
        for(p = 0; p < 8; p++)
        {
            if(preenchidos[i][p] == 'p')
            {
                draw_sprite(buffer, player2, COORDQuadrado[p], COORDQuadrado[i]);
            }

            if(preenchidos[i][p] == 'b')
            {
                draw_sprite(buffer, player1, COORDQuadrado[p], COORDQuadrado[i]);
            }
        }
}
//====================================================================================================================
void delayMouse(void) //cuida para que nao seja detectado mais de uma vez por segundo
{
    counterMiliSeg++;
}
END_OF_FUNCTION(delayMouse);

//====================================================================================================================

void contadorTiles(char preenchidos[][8], int *nroPreto, int *nroBranco)
{
    int i,p, preto = 0, branco = 0;

    for(i = 0; i < 8; i++) //loop que conta os pretos e brancos do tabuleiro
    {
        for(p = 0; p < 8; p++)
        {
            if(preenchidos[i][p] == 'p')
            {
                preto++;
            }

            else if(preenchidos[i][p] == 'b')
            {
                branco++;
            }
        }
    }

    *nroPreto = preto; //atualiza as variaveis
    *nroBranco = branco;
}
