/*Este é o jogo BOW AND ARROW, que consiste em uma fase:
1ª: O arqueir0 deve acertar os baloes que sobem sem deixar as flechas acabarem.

Pontuação:

100 pontos por balao acertado
50 pontos por flecha na aljava no final da fase

Dimensões:

fase - 24linhasx80colunas
personagem - 4 linhas
orc(1 fase) - 3 linhas
orc (2ª fase) - 5 linhas

Controles:

W-S - move
ESPAÇO - atira
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//DEFINIÇÕES
#define TEMPOFASE 300
#define MATRIZ_LARGURA 81
#define HIGHSCOREX 14
#define ARROW_COUNTER 62
#define SCOREX 9
#define BALAOESQ 15
#define BALAODIR 75
#define ARQUEIROY 6
#define PONTADOARCOX 9
#define ULTIMA_LINHA_JOGAVEL 22
#define PRIMEIRA_LINHA_JOGAVEL 4
#define PONTUACAOFINAL_X 49

//ESTRUTURA

typedef struct tipo_jogador
{
    char nome[30];
    int score;
} TIPO_JOGADOR;

//global
char nomeArquivo[20] = "highscores.bin";

////////////////////////////////////////////////////////////////  PROTÓTIPOS

void telaPrincipal();
char opcaoMenu();
void fase1();
void gotoxy( int x, int y);
void printaMatriz(char telaFase1[][MATRIZ_LARGURA]);
void printaBalao(int y,int nroLinhas,char telaFase1[][MATRIZ_LARGURA]);
void baloes(int *controleLinha,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[]);
void printaArqueiro(int linhaArqueiro);
void estouraBalao(int auxFlecha,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[]);
void verificaTeclaMovimento1(int *posicArqueiro, int *pontadoarcoy,int *flechaNoAr,int *arrow_counterMOD);
int flecha(int *nroFlechas, int *flechax, int pontadoarcoy, int *flechaNoAr,int score,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[]);
int movimento1(int *score,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[]);
void instrucoes();
int pontuacaoFinal(int score, int nroFlechas);
void ordenaScore(int posicao,TIPO_JOGADOR highscores[],TIPO_JOGADOR newscore);
void mostraHighScores();

//////////////////////////////////////////////////////////////////*ROTINA PRINCIPAL*///////////////////////////////////////////////////////////////////////

int main(void)
{
    FILE *arqTopScores;
    char menuSelec;


    do
    {
        telaPrincipal();            //Printa a tela principal do jogo com as opcoes do Menu.

        menuSelec = opcaoMenu();   //Captura a opção selecionada pelo jogador.

        switch(menuSelec)          //Chama a função de acordo com a seleção escolhida (1-Novo jogo, 2-placares, 3-sair).
        {
        case '1':
            system("cls");
            instrucoes(); //printa as instruções do jogo
            getch();  //tem que apertar alguma tecla para sair das instruções

            system("cls");
            fase1();

            break;

        case '2':
            system("cls");
            mostraHighScores(&arqTopScores);
            break;

        case '3':
            return 0;

        }

        gotoxy(0, 0); //reseta o cursor para qunado voltar das funções

    }
    while(menuSelec != 3);
}

///////////////////////////////////////////////////////////////////////   telaPrincipal   //////////////////////////////////////////////////////////////////

void telaPrincipal()
{
    int i, p;

    char telaPrinc[24][81] =
    {
        {"  ____________________________________________________________________________ "},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|     |\x5c                                                                      |"},
        {"|     | \x5c                                                                     |"},
        {"|     | (   ___                         \x2f\x5c     __   __   ___                  |"},
        {"|     |  ) |   | \x5c   ^   \x2f             \x2f\x2f\x5c\x5c   |  ) |  ) |   | \x5c   ^   \x2f       |"},
        {"|     | <  |   |  \x5c \x2f \x5c \x2f      AND    \x2f\x2f==\x5c\x5c==|=<==|=<==|===|==\x5c=\x2f=\x5c=\x2f=====>  |"},
        {"|     |  ) |___|   v   v             \x2f\x2f    \x5c\x5c |  \x5c |  \x5c |___|   v   v         |"},
        {"|     | (                                                                     |"},
        {"|     | \x2f                                                                     |"},
        {"|     |\x2f                                                                      |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|     1 - NOVO JOGO                                                           |"},
        {"|                                                                             |"},
        {"|     2 - MAIORES PLACARES                                                    |"},
        {"|                                                                             |"},
        {"|     3 - SAIR                                                                |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|_____________________________________________________________________________|"},

    };

    printaMatriz(telaPrinc);
}
////////////////////////////////////////////////////////////////   instrucoes  /////////////////////////////////////////////////////////////////////////////////

void instrucoes()
{
    char telaInstrucoes[24][81] =
    {
        {"   _______________________-------------------                       `\x5c          "},
        {" \x2f:--__                                                              |          "},
        {"||< >|                                    ___________________________\x2f          "},
        {"| \x5c__\x2f_________________-------------------                         |            "},
        {"|    pressione alguma tecla                                         |          "},
        {" |                                                                  |          "},
        {" |                            INSTRUCOES                            |          "},
        {" |                                                                  |          "},
        {" |                    ACERTE TODOS OS BALOES COM O                  |         "},
        {"  |                  MENOR NUMERO DE FLECHAS POSSIVEL               |         "},
        {"  |                                                                  |         "},
        {"  |                           CONTROLES                              |         "},
        {"  |                                                                  |         "},
        {"  |                        W      -    CIMA                          |         "},
        {"  |                                                                  |         "},
        {"  |                        S      -    BAIXO                         |         "},
        {"  |                                                                  |         "},
        {"  |                     ESPACO    -    ATIRA FLECHA                  |         "},
        {"  |                                                                  |         "},
        {"  |                                              ____________________|         "},
        {"  |  ___________________-------------------------                      `\x5c       "},
        {"  |\x2f`--_                                                                 |      "},
        {"  ||[ ]||                                            ___________________\x2F       "},
        {"   \x5c===\x2f___________________--------------------------                           "}
    };

    printaMatriz(telaInstrucoes);
}

////////////////////////////////////////////////////////////////   opcaoMenu   //////////////////////////////////////////////////////////////////////////////////////////

char opcaoMenu()
{
    char opcao;

    do
    {
        fflush(stdin);
        opcao = getch();
    }
    while(opcao != '1' && opcao != '2' && opcao != '3');

    return opcao;
}

///////////////////////////////////////////////////////////////////////    fase1   //////////////////////////////////////////////////////////////////////////
void fase1()
{
    FILE *arqTopScores;

    //INICIALIZA A MATRIZ DA FASE E AS STRINGS COM OS BALOES
    char tempVazia[MATRIZ_LARGURA] =  "|                                                                             |";
    char tempBalao1[MATRIZ_LARGURA] = "|               \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c   |";
    char tempBalao2[MATRIZ_LARGURA] = "|               \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f   |";
    char tempBalao3[MATRIZ_LARGURA] = "|                $   $   $   $   $   $   $   $   $   $   $   $   $   $   $    |";

    char telaFase1[24][MATRIZ_LARGURA] = // a matriz foi montada com codigos hexadecimais usando o comando \x(codigo).
    {
        {" -------------------------------> BOW AND ARROW <----------------------------- "},
        {"| SCORE: 0                           LEVEL 1                                  |"},
        {"| HIGH SCORE:                     THE BALLOONS        ARROWS: ||||||||||||||| |"},
        {"|-----------------------------------------------------------------------------|"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|                                                                             |"},
        {"|               \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c \x2f~\x5c   |"},
        {"|               \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f \x5c_\x2f   |"},
        {"|                $   $   $   $   $   $   $   $   $   $   $   $   $   $   $    |"},
        {"|_____________________________________________________________________________|"}

    };

    int nroFlechas, posicao, abreOUfecha = 1; //abreOUfecha = 1 para abrir e ler, 0 para escrever e fechar
    int score = 0, scoreFinal;
    TIPO_JOGADOR highscores[5];
    TIPO_JOGADOR newscore;

    printaMatriz(telaFase1);

    //ABRE E LE O ARQUIVO
    if((arqTopScores=fopen(nomeArquivo,"r+b"))== NULL) //se der erro na abertura do arquivo ele tenta ler
    {
        system("cls");
        printf("erro na abertura do arquivo!\n");
        getch();
    }


    else
    {
        if((fread(highscores,sizeof(TIPO_JOGADOR), 5,arqTopScores)) != 5) //se der erro na leitura do arquivo ele ja sai da função e volta ao menu
        {
            system("cls");
            printf("Erro na leitura do arquivo!");
            getch();
        }

        else //se nao der erro de abertura nem de leitura o programa executa a fase1
        {
            //PRINTA HIGHSCORE
            gotoxy(HIGHSCOREX, 2); //vai para a posição do high score e printa o high score atual
            printf("%i", highscores[0].score); //printa o maior score gravado no arquivo.

            printaArqueiro(ARQUEIROY);

            //MOVIMENTO1
            nroFlechas = movimento1(&score, telaFase1, tempVazia, tempBalao1, tempBalao2, tempBalao3); //Função que cuida do loop de tudo que se move na fase

            //PONTUAÇÃO FINAL
            scoreFinal = pontuacaoFinal(score, nroFlechas); //mostra na tela a pontuação final do jogador

            newscore.score = scoreFinal;

            gotoxy(42, 16); //42 e 16 sao o X e Y de onde ele printa a frase abaixo (OBS: A MATRIZ DA PONTUAÇÃO ESTÁ NA TELA)
            printf("Insira seu nome:\n");
            gotoxy(42, 17);
            scanf("%s", &newscore.nome);

            posicao = compara_novo_score(highscores, newscore);

            if(posicao <= 4)
                ordenaScore(posicao, highscores, newscore);

            //ESCREVE E FECHA O ARQUIVO
            rewind(arqTopScores);

            if((fwrite(highscores, sizeof(TIPO_JOGADOR), 5, arqTopScores)) != 5)
            {
                system("cls");
                printf("Erro na escrita do arquivo!");
                getch();
            }

            fclose(arqTopScores);

        }
    }


}

/////////////////////////////////////////////////////////////// gotoxy //////////////////////////////////////////////////////////////////////////////////////////
void gotoxy( int x, int y)
{
    COORD coord = {0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

////////////////////////////////////////////////////////////////////// printaMatriz ////////////////////////////////////////////////////////////////////////////////
void printaMatriz(char matriz[][MATRIZ_LARGURA])
{
    int i, p;

    for(i = 0; i < 24; i++)
    {
        for(p = 0; p < MATRIZ_LARGURA; p++)
        {
            printf("%c", matriz[i][p]);
        }
        printf("\n");
    }
}

//////////////////////////////////////////////////////////////// printaArqueiro ///////////////////////////////////////////////////////////////////////////////////////
void printaArqueiro(int linhaArqueiro)
{
    gotoxy(0, linhaArqueiro);

    printf("|  \x2 |\x5c \n");
    printf("|  |=|->\n");
    printf("|  | |\x2f \n");
    printf("| \x2f \x5c   ");
}

///////////////////////////////////////////////////////////////////// movimento1 /////////////////////////////////////////////////////////////////////////////////////
int movimento1(int *score,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[])
{
    int controleLinha = ULTIMA_LINHA_JOGAVEL;
    int posicArqueiro = ARQUEIROY; //ARQUEIROY = posição inicial do arqueiro
    int y, x, pontadoarcoy;
    int flechaNoAr = 0;
    int flechax = PONTADOARCOX;
    int arrow_counterMOD = ARROW_COUNTER; //marca a posição X da tela onde as flechas devem ser apagadas
    int nroFlechas = 15; //determina aqui o numero de flechas e retona para a função fase1 fazer o cálculo!

    do
    {
        //VERIFICA SE O PLAYER APERTOU ALGUMA TECLA E FAZ OS AJUSTES NECESSÁRIOS
        verificaTeclaMovimento1(&posicArqueiro, &pontadoarcoy, &flechaNoAr, &arrow_counterMOD);

        //CHAMA A FUNÇÃO BALOES
        baloes(&controleLinha, telaFase1, tempVazia, tempBalao1, tempBalao2, tempBalao3);

        //PRINTA O ARQUEIRO E SUA POSSIVEL MUDANÇA DE POSIÇÃO
        printaArqueiro(posicArqueiro);

        //LOOP QUE ATIRA A FLECHA E FAZ OS AJUSTES NECESSÁRIOS
        *score = flecha(&nroFlechas, &flechax, pontadoarcoy, &flechaNoAr, *score, telaFase1, tempVazia, tempBalao1, tempBalao2, tempBalao3);

        controleLinha--;
        if(!flechaNoAr)
            Sleep(TEMPOFASE); //apenas dorme quando não há flecha no ar, pois se houver ele dormirá no while da flecha
    }
    while(nroFlechas > 0 && (strcmp(tempBalao1, tempVazia) != 0));

    if(nroFlechas > 0)
        nroFlechas--; //A flecha é reduzida quando chega ao final da tela, portanto tem de tirar mais uma caso estoure todos os balões

    return nroFlechas;
}

///////////////////////////////////////////////////////////////// verificaTeclaMovimento1 ////////////////////////////////////////////////////////////////////////////////////
void verificaTeclaMovimento1(int *posicArqueiro, int *pontadoarcoy,int *flechaNoAr,int *arrow_counterMOD)
{
    char c;

    if(kbhit())
    {
        c = getch();
        c = tolower(c);

        switch(c)
        {
        case 'w': //move o arqueiro para cima
            if(*posicArqueiro > PRIMEIRA_LINHA_JOGAVEL)
            {
                *posicArqueiro -= 2;
                gotoxy(0, *posicArqueiro+4); //posicArqueiro fica na cabeça do arqueiro, por isso tem que ter +4 e +5 para limpar onde ele estava
                printf("|          ");
                gotoxy(0, *posicArqueiro+5);
                printf("|          ");
            }

            break;

        case 's': //move o arqueiro para baixo
            if(*posicArqueiro < ULTIMA_LINHA_JOGAVEL-4)
            {
                *posicArqueiro += 2;
                gotoxy(0, *posicArqueiro-1);
                printf("|          ");
                gotoxy(0, *posicArqueiro-2);
                printf("|          ");
            }

            break;

        case ' ': //atira uma flecha
            if(!*flechaNoAr)
            {
                *flechaNoAr = 1; //avisa que tem flecha no ar, impedindo o sleep do loop de ser completado, fazendo apenas 1/8 de tempo
                *pontadoarcoy = *posicArqueiro + 1;

                gotoxy(*arrow_counterMOD, 2); //arrow_counterMOD = contador de flechas do topo
                printf(" ");
                *arrow_counterMOD = *arrow_counterMOD + 1; //soma mais um a variavel para que apague a proxima flecha na proxima vez
            }

            break;
        }
    }
}

////////////////////////////////////////////////////////////////// baloes /////////////////////////////////////////////////////////////////////////////////////
void baloes(int *controleLinha,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[])
{
    int raboDoBalao = *controleLinha;

    if(raboDoBalao > 6) //SE OS BALOES AINDA NAO CHEGARAM NO TOPO
    {
        strcpy(telaFase1[(raboDoBalao-3)], tempBalao1);//-3 pois ele está indo um espaço acima do topodo balao
        strcpy(telaFase1[(raboDoBalao-2)], tempBalao2);
        strcpy(telaFase1[(raboDoBalao-1)], tempBalao3);
        strcpy(telaFase1[raboDoBalao], tempVazia); //atribui uma string vazia em cima do raboDoBalao que subiu
    }

    else //SE OS BALOES CHEGARAM NO TOPO
    {
        raboDoBalao = PRIMEIRA_LINHA_JOGAVEL;
        strcpy(telaFase1[raboDoBalao], tempVazia); //ATRIBUI STRINGS VAZIAS NOS BALOES QUE CHEGARAM NO TOPO
        strcpy(telaFase1[raboDoBalao+1], tempVazia);
        strcpy(telaFase1[raboDoBalao+2], tempVazia);

        printaBalao(raboDoBalao, 3, telaFase1); //printa onde os baloes foram apagados.(3 é o numero de linhas que o balao ocupa)

        raboDoBalao = ULTIMA_LINHA_JOGAVEL;

        strcpy(telaFase1[(raboDoBalao-2)], tempBalao1);//-2 pois está apenas printando o balao na posição inicial
        strcpy(telaFase1[(raboDoBalao-1)], tempBalao2);
        strcpy(telaFase1[(raboDoBalao)], tempBalao3);

        *controleLinha = ULTIMA_LINHA_JOGAVEL+1; //ATRIBUI ESTE VALOR (+1) PORQUE O NO FINAL ELE TIRA 1 E VOLTA AO LOOP NORMAL
    }

    printaBalao(raboDoBalao-3, 4, telaFase1);
}

////////////////////////////////////////////////////////////////// flecha ///////////////////////////////////////////////////////////////////////////////////////
int flecha(int *nroFlechas, int *flechax, int pontadoarcoy, int *flechaNoAr,int score,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[])
{
    int x, i;
    int auxFlechaLoop; //guarda o valor para encerrar o loop

    if(*flechaNoAr)
    {
        auxFlechaLoop = *flechax+8; //guarda o valor para encerrar o loop quando a flecha andar 8

        do
        {
            //ATIRA A FLECHA

            gotoxy(*flechax, pontadoarcoy);
            printf("-->"); //printa a flecha

            if(telaFase1[pontadoarcoy][*flechax+2] == '~' || telaFase1[pontadoarcoy][*flechax+2]  == '_') //se acertou o balao
            {
                estouraBalao(*flechax+2, telaFase1, tempVazia, tempBalao1, tempBalao2, tempBalao3); //chama a função que apaga os baloes acertados

                score += 100; //soma 100 no score

                gotoxy(SCOREX, 1);
                printf("%i", score); //printa o score alterado
            }

            gotoxy(*flechax-2, pontadoarcoy);

            for(i = *flechax-2; i < *flechax; i++)
                printf("%c", telaFase1[pontadoarcoy][i]); //PRINTA MATRIZ POR ONDE A FLECHA PASSOU

            //PARA DE PRINTAR A FLECHA

            *flechax = *flechax + 1;
            Sleep(TEMPOFASE/8); //dorme 1/8 do tempo para cada +1 na flechax. Como ele vai até +8 dorme o tempo "inteiro"
        }
        while(*flechax < auxFlechaLoop && *flechax != MATRIZ_LARGURA-5);  //81-5=76, ou seja, tres espaços para flecha + o 80 que é |

        if(*flechax == MATRIZ_LARGURA-5) //chegou no fim
        {
            auxFlechaLoop = *flechax+3;
            for(x = *flechax; x < auxFlechaLoop; x++)
                printf(" "); //limpa a flecha que chegou no fim da tela
            *flechax = PONTADOARCOX;
            *flechaNoAr = 0;

            *nroFlechas = *nroFlechas-1;
        }
    }
    return score;
}

////////////////////////////////////////////////////////////////// estouraBalao ////////////////////////////////////////////////////////////////////////////////////////
void estouraBalao(int auxFlecha,char telaFase1[][MATRIZ_LARGURA],char tempVazia[],char tempBalao1[],char tempBalao2[],char tempBalao3[])
{
    int i;

    for(i = auxFlecha-1; i < (auxFlecha+2); i++) // os 3 espaços ocupados pelo balao
    {
        tempBalao1[i] = tempVazia[i];
        tempBalao2[i] = tempVazia[i];
        tempBalao3[i] = tempVazia[i];
    }
}

////////////////////////////////////////////////////////////////// printaBalao ////////////////////////////////////////////////////////////////////////////////////////
void printaBalao(int y,int nroLinhas,char telaFase1[][MATRIZ_LARGURA])
{
    int linha, limiteY;

    limiteY = y + nroLinhas;

    for(linha = y; linha < limiteY; linha++)
    {
        gotoxy(0, linha);
        printf("%s", telaFase1[linha]);
    }
}

/////////////////////////////////////////////////////////////////  telaFinal ///////////////////////////////////////////////////////////////////////////////////

int pontuacaoFinal(int score, int nroFlechas)
{
    int bonus, i, total; //bonus = flechas nao usadas*50;

    char telaFinal[24][MATRIZ_LARGURA] =
    {
        {" _____________________________________________________________________________ "},
        {"|  `@@@L                                                                      |"},
        {"|   `@@@z                                                                     |"},
        {"|    `-@@@_                                        PARABENS!                  |"},
        {"|      ]@@@_                                                                  |"},
        {"|       '@@@z                                   \x6 SUA PONTUACAO \x6             |"},
        {"|        `]@@L,                                                               |"},
        {"|          `@@@L                                                              |"},
        {"|           `@@@z,                        BALOES                              |"},
        {"|            `-@@@_                                                           |"},
        {"|              `@@@L                       BONUS                              |"},
        {"|               `@@@L    ]e                                                   |"},
        {"|                 ~@@b_  a@b                                                  |"},
        {"|                  `@@@e]@@L               TOTAL                              |"},
        {"|            -zzzz___@@@U@@@,                                                 |"},
        {"|              '~-@@@@@@@@@@@                                                 |"},
        {"|                 `~-@@@@@@@@L                                                |"},
        {"|                    '~-@@@@@@,                                               |"},
        {"|                       '~@@@@L                                               |"},
        {"|                         `~@@@e                                              |"},
        {"|                            ~@@_                                             |"},
        {"|                              ~@                                             |"},
        {"|                                                                             |"},
        {"|_____________________________________________________________________________|"}
    };

    gotoxy(0,0); //reseta o cursor
    printaMatriz(telaFinal);

    bonus = nroFlechas*50;

    gotoxy(PONTUACAOFINAL_X, 8); //printa o score dos baloes na tela
    printf("%i", score);

    for(i = 0; i <= bonus; i++)
    {
        gotoxy(PONTUACAOFINAL_X, 10); //printa o bonus das flechas na tela

        printf("%i", i);
        Sleep(10); //dorme para que os numeros do bonus vao sendo incrementados um por um
    }

    total = score+bonus;

    gotoxy(PONTUACAOFINAL_X, 13); // printa o total na tela
    printf("%i", total);

    return total;
}

////////////////////////////////////////////////////////// compara_novo_score /////////////////////////////////////////////////////////////////////////////
int compara_novo_score(TIPO_JOGADOR highscores[],TIPO_JOGADOR newscore)
{
    int ind, pos;
    int maior = 0;
    pos = -1;
    ind = 0;
    while (!maior && ind < 5)
    {
        if (newscore.score >= highscores[ind].score)
            maior = 1;
        ind++;
    }


    return ind;
}

///////////////////////////////////////////////////////// ordenaScore /////////////////////////////////////////////////////////////////////////////////////
void ordenaScore(int posicao,TIPO_JOGADOR highscores[],TIPO_JOGADOR newscore)
{
    switch (posicao)
    {
    case 0:
        highscores[4]=highscores[3];
        highscores[3]=highscores[2];
        highscores[2]=highscores[1];
        highscores[1]=highscores[0];
        highscores[0]= newscore;
        break;

    case 1:
        highscores[4]=highscores[3];
        highscores[3]=highscores[2];
        highscores[2]=highscores[1];
        highscores[1]=newscore;
        break;

    case 2:
        highscores[4]=highscores[3];
        highscores[3]=highscores[2];
        highscores[2]=newscore;
        break;

    case 3:
        highscores[4]=highscores[3];
        highscores[3]=newscore;
        break;

    case 4:
        highscores[4]=newscore;
        break;

    default:
        break;

    }
}

/////////////////////////////////////////////////////////////// mostraHighScores /////////////////////////////////////////////////////////////////////////
void mostraHighScores()
{
    FILE *arqTopScores;

    TIPO_JOGADOR highscores[5];
    int abreOUfecha = 1; //1 para abrir e ler arquivo
    int i;

    //ABRE E LE O ARQUIVO
    if((arqTopScores=fopen(nomeArquivo,"rb"))== NULL)
    {
        printf("erro na abertura do arquivo!\n");
        getch();
    }

    else
    {
        if((fread(highscores,sizeof(TIPO_JOGADOR), 5, arqTopScores)) != 5)
        {
            system("cls");
            printf("Erro na leitura do arquivo!");
            getch();
        }

        else
        {
            for(i = 0; i < 5; i++)
            {
                printf("\n   %s: %i \n", highscores[i].nome, highscores[i].score);
            }

            printf("\n   Pressione qualquer tecla para voltar ao menu.");

            fclose(arqTopScores);

            getch();
        }
    }


}
