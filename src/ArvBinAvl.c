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

//Calcula o fator de balanço de um nó;
int balanceAVL(NodeAvl *avl){
	return labs(heightAvl(avl->left)-heightAvl(avl->right));
}

//Verifica qual dos inteiros é maior;
int maior (int x, int y){
	if (x>y) return x;
	else return y;
}

//Funcao de Rotacao simples para a direita
void RotationLL(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->left;
    u->left = v->right;
    v->right = u;
    v->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
    u->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
    *node = v; 
}

//Funcao de Rotacao simples para a esquerda
void RotationRR(NodeAvl **node){
    NodeAvl *u = *node;
    NodeAvl *v = u->right;
    u->right = v->left;
    v->left = u;
    u->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
    v->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
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
                    
                    if(balanceAVL(*node) >= 2){
                        if(chave < (*node)->left->chave){
                            RotationLL(node);
                        }else RotationLR(node);
                    }
                }
            }else{
                if((*node)->chave < chave){
                    if(insertAvl(&(*node)->right, chave) == 1){
                        
                        if(balanceAVL(*node) >= 2){
                            if(chave > (*node)->right->chave){
                                RotationRR(node);
                            }else RotationRL(node);
                        }
                    }
                }
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
            return 1;
        }
    }
}


void imprimeArvore(NodeAvl *T, int nivel){
    int i;
    if(T!=NULL){
        imprimeArvore(T->right, nivel+1);
        for(i=0; i<nivel; i++) printf("\t");
        printf("%d:%d\n",T->chave,T->fatorBal);
        imprimeArvore(T->left, nivel+1);
    }
}