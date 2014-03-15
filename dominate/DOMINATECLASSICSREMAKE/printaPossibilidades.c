#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#define ESPACO_QUADRADO 10
#define VERDE_ADJ 255
#define VERDE_PULO 90

void printaPossibilidades(int coordMouse[2],int COORDQuadrado[9], char preenchidos[][8], BITMAP *buffer) //printa o retorno de quadrados com as possibilidades
{
    int x, y;

    y = coordMouse[0]; // 0 = y
    x = coordMouse[1]; //1 = x
    int esquerda = 0, direita = 0;

//verifica se tem espaço na esquerda para printar as possibilidades
    if(x > 0)
    {
        esquerda = 1;

        if(preenchidos[y][x-1] == 'v')
        {
            rect(buffer, COORDQuadrado[x-1], COORDQuadrado[y], COORDQuadrado[x]-ESPACO_QUADRADO, COORDQuadrado[y+1]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
            preenchidos[y][x-1] = 'a'; //'a' DE ADJACENTE - POSSIBILIDADE
        }

        if(x > 1)
        {
            if(preenchidos[y][x-2] == 'v')
            {
                rect(buffer, COORDQuadrado[x-2], COORDQuadrado[y], COORDQuadrado[x-1]-ESPACO_QUADRADO, COORDQuadrado[y+1]-ESPACO_QUADRADO, makecol(0,VERDE_PULO,0));
                preenchidos[y][x-2] = 'l'; //l DE LONGE - POSSIBILIDADE
            }

        }
    }
//verifica se tem espaço na direita
    if(x < 7)
    {
        direita = 1;

        if(preenchidos[y][x+1] == 'v')
        {
            rect(buffer, COORDQuadrado[x+1], COORDQuadrado[y], COORDQuadrado[x+2]-ESPACO_QUADRADO, COORDQuadrado[y+1]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
            preenchidos[y][x+1] = 'a';
        }

        if(x < 6)
        {
            if(preenchidos[y][x+2] == 'v')
            {
                rect(buffer, COORDQuadrado[x+2], COORDQuadrado[y], COORDQuadrado[x+3]-ESPACO_QUADRADO, COORDQuadrado[y+1]-ESPACO_QUADRADO, makecol(0,VERDE_PULO,0));
                preenchidos[y][x+2] = 'l';
            }
        }

    }

//verifica se tem espaço em cima
    if(y > 0)
    {
        if(preenchidos[y-1][x] == 'v')
        {
            rect(buffer, COORDQuadrado[x], COORDQuadrado[y-1], COORDQuadrado[x+1]-ESPACO_QUADRADO, COORDQuadrado[y]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
            preenchidos[y-1][x] = 'a';
        }

        if(y > 1)//se tem 2 espacos em cima
        {
            if(preenchidos[y-2][x] == 'v')
            {
                rect(buffer, COORDQuadrado[x], COORDQuadrado[y-2], COORDQuadrado[x+1]-ESPACO_QUADRADO, COORDQuadrado[y-1]-ESPACO_QUADRADO, makecol(0,VERDE_PULO,0));
                preenchidos[y-2][x] = 'l';
            }

        }

        if(esquerda)//se tem espaco na esquerda para diagonal
        {
            if(preenchidos[y-1][x-1] == 'v')
            {
                rect(buffer, COORDQuadrado[x-1], COORDQuadrado[y-1], COORDQuadrado[x]-ESPACO_QUADRADO, COORDQuadrado[y]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
                preenchidos[y-1][x-1] = 'a';
            }
        }
        if(direita) //se tem espaco na direita para a diagonal
        {
            if(preenchidos[y-1][x+1] == 'v')
            {
                rect(buffer, COORDQuadrado[x+1], COORDQuadrado[y-1], COORDQuadrado[x+2]-ESPACO_QUADRADO, COORDQuadrado[y]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
                preenchidos[y-1][x+1] = 'a';
            }
        }
    }

//verifica de tem espaço em baixo
    if(y < 7)
    {
        if(preenchidos[y+1][x] == 'v')//se o quadrado de baixo esta vazio
        {
            rect(buffer, COORDQuadrado[x], COORDQuadrado[y+1], COORDQuadrado[x+1]-ESPACO_QUADRADO, COORDQuadrado[y+2]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
            preenchidos[y+1][x] = 'a';
        }

        if(y < 6)//se tem 2 espacos
        {
            if(preenchidos[y+2][x] == 'v')
            {
                rect(buffer, COORDQuadrado[x], COORDQuadrado[y+2], COORDQuadrado[x+1]-ESPACO_QUADRADO, COORDQuadrado[y+3]-ESPACO_QUADRADO, makecol(0,VERDE_PULO,0));
                preenchidos[y+2][x] = 'l';
            }
        }

        if(esquerda)//se tiver espaço na esquerda para a diagonal
        {
            if(preenchidos[y+1][x-1] == 'v')
            {
                rect(buffer, COORDQuadrado[x-1], COORDQuadrado[y+1], COORDQuadrado[x]-ESPACO_QUADRADO, COORDQuadrado[y+2]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
                preenchidos[y+1][x-1] = 'a';
            }
        }
        if(direita)//se tem espaco na direita para diagonal
        {
            if(preenchidos[y+1][x+1] == 'v')
            {
                rect(buffer, COORDQuadrado[x+1], COORDQuadrado[y+1], COORDQuadrado[x+2]-ESPACO_QUADRADO, COORDQuadrado[y+2]-ESPACO_QUADRADO, makecol(0,VERDE_ADJ,0));
                preenchidos[y+1][x+1] = 'a';
            }
        }

    }

    scare_mouse();
    draw_sprite(screen, buffer, 0, 0); //desenha o buffer na tela
    unscare_mouse();
}
