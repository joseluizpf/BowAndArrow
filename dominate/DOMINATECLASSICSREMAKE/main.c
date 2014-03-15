/*This is a windows 3.1 dominate remake */
//@joseluizpf

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "abreAllegro.h"
#include "fechaAllegro.h"
#include "localMPloop.h"

/* OBS:
Para as coordenadas de x e y dos quadrados (armazenados no vetor COORDQuadrados), o calculo segue abaixo:
//x1 = [i]+ESPACO_QUADRADO
//x2 = [i+1]

//y1 = [p]+ESPACO_QUADRADO                             ...x1 e y1 sao as coordenadas do primeiro vértice e x2,y2 do último
//y2 = [p+1] */



//===============================================//ROTINA PRINCIPAL//=====================================================//

int main()
{
    if (!abreAllegro())
    {
        fechaAllegro();
    }

    localMPloop();

    fechaAllegro();
    return 0;
}
END_OF_MAIN();

