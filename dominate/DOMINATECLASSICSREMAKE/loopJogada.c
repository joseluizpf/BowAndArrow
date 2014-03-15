#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "clicouEmQuadrado.h"
#include "arrumaVetor.h"

#define ESPACO_QUADRADO 10

//GLOBAL
volatile long int counterMiliSeg1 = 0;

//PROTOTIPOS
void delayMouse1(void);
void domina(int x, int y, char preenchidos[][8],char jogador);

//LOOP JOGADA
void loopJogada(char preenchidos[][8],int COORDquadrado[9],char jogador,int *apagarTileOrigem, int *xTroca, int *yTroca)
{
    int cliqueDentroQuadrado = 0, x, y, i, p;
    int finalWhile = 1;
    int coordMouse[2]; //coordMouse apenas do loopJogada

    LOCK_VARIABLE(counterMiliSeg1); //chama o dalyMouse a cada milisegundo
    LOCK_FUNCTION(delayMouse1);
    install_int(delayMouse1, 1);

printf("\n\nENTREI LOOP JOGADA\n\n");
do
{

     if(mouse_b & 1 && counterMiliSeg1 > 700) //se apertou o botao esquerdo do mouse
    {
        printf("\n\nCLIQUEI DENTRO LOOP\n\n");
        x = mouse_x;
        y = mouse_y; //guarda a posição do x e do y

        cliqueDentroQuadrado = clicouEmQuadrado(x, y, COORDquadrado, coordMouse, ESPACO_QUADRADO); //se clicou em algum quadrado

        x = coordMouse[1];
        y = coordMouse[0];

        if(cliqueDentroQuadrado)
        {

            if(preenchidos[y][x] == 'a') //se clicou em um adjacente
            {
                printf("ADJACENTE_LOOP\n");
                preenchidos[y][x] = jogador; //poe o char do jogador na matriz que controla o tabuleiro
                finalWhile = 0; //sai do loop
            }

            else if(preenchidos[y][x] == 'l') //se clicou em um longe
            {
                printf("longeLOOP\n");
                preenchidos[y][x] = jogador;
                *apagarTileOrigem = 1;
                finalWhile = 0;
            }

            else
            {
                if(preenchidos[y][x] == jogador)
                {
                    *xTroca = x;
                    *yTroca = y;
                    finalWhile = 0;
                }
            }

        }

        counterMiliSeg1 = 0; //zera para se precisar entrar de novo no loop
    }
}
while(finalWhile);

printf("SAILOOP\n");

arrumaVetor(preenchidos, 'a'); //apaga os 'a' do preenchidos
arrumaVetor(preenchidos, 'l'); //apaga os 'l' do preenchidos

if(*xTroca == 8 && *yTroca == 8)
    domina(x, y, preenchidos, jogador);

}

//=============================================================================================================
void delayMouse1(void) //cuida para que nao seja detectado mais de uma vez por segundo
{
    counterMiliSeg1++;
}
END_OF_FUNCTION(delayMouse);

//==============================================================================================================
void domina(int x, int y, char preenchidos[][8],char jogador)
{
    char adversario;
    int esquerda = 0, direita = 0;

    if(jogador == 'p') //verifica quem está jogando e poe um char pro adversario
        adversario = 'b';

    else
        adversario = 'p';

    //ESQUERDA
    if(x > 0) //verifica se tem espaço na esquerda
    {
        esquerda = 1;

        if(preenchidos[y][x-1] == adversario)
        {
            preenchidos[y][x-1] = jogador;
        }
    }

    //DIREITA
    if(x < 7) //verifica se tem espaço na direita
    {
        direita = 1;

        if(preenchidos[y][x+1] == adversario)
        {
            preenchidos[y][x+1] = jogador;
        }
    }

    //CIMA
    if(y > 0) //verifica se tem espaço em cima
    {
        if(preenchidos[y-1][x] == adversario) //verifica um acima
        {
            preenchidos[y-1][x] = jogador;
        }

        //DIAGONAL
        if(esquerda) //se tiver na esquerda e em cima pode ter diagonal
            if(preenchidos[y-1][x-1] == adversario)
            {
                preenchidos[y-1][x-1] = jogador;
            }

        if(direita) //se tiver na direita e em cima pode ter diagonal
            if(preenchidos[y-1][x+1] == adversario)
            {
                preenchidos[y-1][x+1] = jogador;
            }
    }

    //BAIXO
    if(y < 7)
    {
        if(preenchidos[y+1][x] == adversario)
        {
            preenchidos[y+1][x] = jogador;
        }

        //DIAGONAL
        if(esquerda) //se tiver esquerda e baixo pode ter diagonal
            if(preenchidos[y+1][x-1] == adversario)
            {
                preenchidos[y+1][x-1] = jogador;
            }

        if(direita)//se tiver esquerda e baixo pode ter diaonal
            if(preenchidos[y+1][x+1] == adversario)
            {
                preenchidos[y+1][x+1] = jogador;
            }
    }
}
