/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO
DATA CRIACAO: 11/03/2021
ARQUIVO: .c
*/

#include "ArvBinAvl.h"

// Funcao que cria uma instancia do node
NodeAvl* criaNode(int chave){
    NodeAvl *novo;
    novo = (NodeAvl*)malloc(sizeof(NodeAvl));

    if(novo == NULL){
        printf("Erro na alocacao!");
        exit(1);
    }

    novo->chave = chave;
    novo->fatorBal = 0;
    novo->right = novo->left = NULL;

    return novo;
}

//Funcao que inicializa a arvore
Avl* criaAvl(){
    Avl *ptr;
    ptr = (Avl*)malloc(sizeof(Avl));

    if(ptr == NULL){
        printf("Erro na alocacao!");
        exit(1);
    }

    ptr->raiz = NULL;
    return ptr;
}

//Funcao que imprime a arvore no formato em-ordem
void printAvl(NodeAvl *node){
    if (!node) return;

    printAvl(node->left);
    printf(" %d ", node->chave);
    printAvl(node->right);
}

 //Funcao de Busca de um node
NodeAvl* searchAvl(NodeAvl *node, int bool, int chave){
    if(!node) return NULL;

    if (chave < node->chave) return searchAvl(node->left, 1, chave);
    else if (chave > node->chave) return searchAvl(node->right, 1, chave);
    else return node;
}

 //Funcao que retona a altura da raiz
int heightAvl(NodeAvl *raiz){
    if(!raiz) return -1;

    int tam_esq, tam_dir;

    tam_esq = 1 + heightAvl(raiz->left);
    tam_dir = 1 + heightAvl(raiz->right);

    if(tam_dir > tam_esq) return tam_dir;
    else return tam_esq;
}