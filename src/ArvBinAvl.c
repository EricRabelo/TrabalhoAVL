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

 //Funcao que retona a altura da raiz
int heightAvl(NodeAvl *raiz){
    if(!raiz) return -1;

    int tam_esq, tam_dir;

    tam_esq = 1 + heightAvl(raiz->left);
    tam_dir = 1 + heightAvl(raiz->right);

    if(tam_dir > tam_esq) return tam_dir;
    else return tam_esq;
}

//Funcao de Rotacao simples para a direita
void simple_RightRotation(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->left;
    u->left = v->right;
    v->right = u;
    v->fatorBal = 0;
    u->fatorBal = 0;
    *node = v; 
}

//Funcao de Rotacao simples para a esquerda
void simple_LeftRotation(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->right;
    u->right = v->left;
    v->left = u;
    u->fatorBal = 0;
    v->fatorBal = 0;
    *node = v;
}

 //Funcao de Rotacao dupla para a direita
void double_RightRotation(NodeAvl **node){
    simple_LeftRotation(&(*node)->left);
    simple_RightRotation(node);
}

 //Funcao de Rotacao dupla para a esquerda
void double_LeftRotation(NodeAvl **node){
    simple_RightRotation(&(*node)->right);
    simple_LeftRotation(node);
}