/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: main.c
VERSAO: 1.0
*/

#include <stdlib.h>
#include "ArvBinAvl.c"

int main(int argc, char const *argv[])
{
    Avl *avl = criaAvl();

    //Apresentando o MENU PRINCIPAL
    menu(avl);

    destroyAvl(avl);
    printf("\n");
    return 0;
}
