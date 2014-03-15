#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#define ESPACO_QUADRADO 10

int clicouEmQuadrado(int x, int y, int COORDQuadrado[9],int coordMouse[2],int espacoEntreQuadrados)
{
    int i = 0,p = 0;
    int achou = 0; //começa como falso


    while(achou == 0 && p != 8)
    {
        if(x > COORDQuadrado[p] && x < COORDQuadrado[p+1]-espacoEntreQuadrados) //se o x está entre as coordenadas x de um quadrado
        {
            while(achou == 0 && i != 8) //só entra aqui se achou o i já
            {

                if(y > COORDQuadrado[i] && y < COORDQuadrado[i+1]-espacoEntreQuadrados)
                {
                    achou = 1;

                    coordMouse[0] = i; // 0 = y
                    coordMouse[1] = p; //1 = x
                }
                i++;
            }
        }
        p++;
    }

    return achou;
}
