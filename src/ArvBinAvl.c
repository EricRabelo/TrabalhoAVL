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
void RotationLL(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->left;
    u->left = v->right;
    v->right = u;
    v->fatorBal = 0;
    u->fatorBal = 0;
    *node = v; 
}

//Funcao de Rotacao simples para a esquerda
void RotationRR(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->right;
    u->right = v->left;
    v->left = u;
    u->fatorBal = 0;
    v->fatorBal = 0;
    *node = v;
}

 //Funcao de Rotacao dupla para a direita
void RotationLR(NodeAvl **node){
    RotationRR(&(*node)->left);
    RotationLL(node);
}

 //Funcao de Rotacao dupla para a esquerda
void RotationRL(NodeAvl **node){
    RotationLL(&(*node)->right);
    RotationRR(node);
}

 //Funcao de Busca de um node (1)
NodeAvl* searchAvl(NodeAvl *node, int chave){
    if(!node) return NULL;
    if(node->chave == chave) return node;
    else{
        if(node->chave > chave){
            return searchAvl(node->left,chave);
        }else{
            return searchAvl(node->right,chave);
        }
    }
}

 //Funcao de Insercao da arvore
int insertAvl(NodeAvl **node, int chave){
    if(*node == NULL){
        (*node) = criaNode(chave);
        return 1;
    } 
    else{
        if((*node)->chave == chave) return 0;
        else{
            if((*node)->chave > chave){

                if(insertAvl(&(*node)->left, chave) == 1){
                    // if(labs(heightAvl((*node)->left) - heightAvl((*node)->right)) >= 2){
                    //     if(chave < (*node)->left->chave) RotationLL(node);
                    //     else RotationLR(node);
                    // }
                    switch((*node)->fatorBal){
                        case 1:
                            if((*node)->left->fatorBal == 1) RotationLL(node);
                            else RotationLR(node);
                            break;
                        case 0:
                            (*node)->fatorBal = 1;
                            break;
                        case -1:
                            (*node)->fatorBal = 0;
                            break;
                        default:
                            break;
                    }
                    return 1;
                }else return 0;
            }else{
                if((*node)->chave < chave){
                    if(insertAvl(&(*node)->right, chave) == 1){
                        // if(labs(heightAvl((*node)->left) - heightAvl((*node)->right)) >= 2){
                        //     if((*node)->right->chave < chave) RotationRR(node);
                        //     else RotationRL(node);
                        // }
                        switch ((*node)->fatorBal)
                        {
                        case 1:
                            (*node)->fatorBal = 0;
                            break;
                        case 0:
                            (*node)->fatorBal = -1;
                            break;
                        case -1:
                            if((*node)->right->fatorBal == -1) RotationRR(node);
                            else RotationRL(node);
                        default:
                            break;
                        }
                        return 1;
                    }
                }else return 0;
            }
            // if(heightAvl((*node)->left) > heightAvl((*node)->right)) (*node)->fatorBal = heightAvl((*node)->left) + 1;
            // else (*node)->fatorBal = heightAvl((*node)->right) + 1;
            return 0;
        }
    }
}

void printAVL(NodeAvl *node){
	if((!node)) return;
	printAVL(node->left);
	printf("%d ", node->chave);
	printAVL(node->right);
}