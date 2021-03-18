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
    i = insertAvl(&(avl->raiz),29);
    i = insertAvl(&(avl->raiz),30);
    i = insertAvl(&(avl->raiz),31);
    i = insertAvl(&(avl->raiz),32);
    i = insertAvl(&(avl->raiz),33);

    //Procurar um noh
    // NodeAvl *ptr = searchAvl(&(*(avl->raiz)),19);
    // printf(" %d \n",avl->raiz->chave);

    //Imprime
    // printAVL(avl->raiz);
    // printf(" %d ", heightAvl(avl->raiz));

    imprimeArvore(avl->raiz,heightAvl(avl->raiz));

    printf("\n");
    return 0;
}
