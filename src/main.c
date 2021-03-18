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
    i = insertAvl(&(avl->raiz),1);
    i = insertAvl(&(avl->raiz),4);
    i = insertAvl(&(avl->raiz),7);
    i = insertAvl(&(avl->raiz),10);
    i = insertAvl(&(avl->raiz),13);
    i = insertAvl(&(avl->raiz),16);
    i = insertAvl(&(avl->raiz),19);
    i = insertAvl(&(avl->raiz),22);
    i = insertAvl(&(avl->raiz),25);
    i = insertAvl(&(avl->raiz),28);

    NodeAvl *ptr = searchAvl(&(*(avl->raiz)),19);
    printf(" %d \n",ptr->chave);

    printAVL(avl->raiz);

    printf("\n");
    return 0;
}
