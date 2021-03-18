/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO
DATA CRIACAO: 11/03/2021
ARQUIVO: main.c
VERSAO: 1.0
*/

#include "ArvBinAvl.c"

int main(int argc, char const *argv[])
{
    Avl *avl = criaAvl();
    int i;
    i = insertAvl(&(avl->raiz),15);
    i = insertAvl(&(avl->raiz),3);
    i = insertAvl(&(avl->raiz),4);
    i = insertAvl(&(avl->raiz),5);
    i = insertAvl(&(avl->raiz),6);

    printAVL(avl->raiz);

    printf("\n");
    return 0;
}
