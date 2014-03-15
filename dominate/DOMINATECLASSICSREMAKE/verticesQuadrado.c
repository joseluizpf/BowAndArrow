#include <stdio.h>
#include <stdlib.h>

//Esta função guarda em um vetor as coordenadas dos vértices dos quadrados de um tabuleiro de tamanho "numeroDeQuadrados"
void verticesQuadrado(int COORDQuadrado[9], int ladoQuadrado, int espacoEntreQuadrado)
{
    int i;

    for(i = 0; i < 9; i++)
    {
        COORDQuadrado[i] = (i*ladoQuadrado)+espacoEntreQuadrado;
    }

}
