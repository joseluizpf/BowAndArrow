#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

void arrumaVetor(char preenchidos[][8],char novoChar)
{
    int i,p;

    for(i = 0; i < 8; i++)
        for(p = 0; p < 8; p++)
        {
            if(preenchidos[i][p] == novoChar)
                preenchidos[i][p] = 'v';
        }
}
