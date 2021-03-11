/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO
DATA CRIACAO: 11/03/2021
ARQUIVO: .c
*/

#include <stdio.h>
#include <stdlib.h>
#include "ArvBinAvl.h"

// Funcao que cria uma instancia do node
Node* criaNode(int chave){
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

//Funcao que retona a altura da raiz
int heightAvl(NodeAvl *raiz){
    if (raiz == NULL) {return 0;}
    if (*raiz == NULL) {return 0;}

    int alt_left = heightAvl(&((*raiz)->left));
    int alt_right = heightAvl(&((*raiz)->right));

    if(alt_left > alt_right){
        return (alt_left + 1);
    }
    else {
        return (alt_right + 1);
    }
}

