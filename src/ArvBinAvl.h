/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: .h
*/

#ifndef ARVBINAVL_H
#define ARVBINAVL_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*------------------------------------------ Estrutura dos nohs da arvore ------------------------------------*/

typedef struct nodeAvl{
    void *info;
    void *chave;
    int fatorBal;
    struct nodeAvl *right, *left;
}NodeAvl;

/*------------------------------------------ Estrutura da raiz da arvore -------------------------------------*/
typedef struct radixAvl{
    NodeAvl *raiz;
}Avl;

/*------------------------------------------ Assinaturas das funcoes -----------------------------------------*/
NodeAvl* criaNode(); //Funcao que cria uma instancia do node
Avl* criaAvl(); //Funcao que inicializa a arvore


void RotationLL(NodeAvl **node); //Funcao de Rotacao simples para a direita
void RotationRR(NodeAvl **node); //Funcao de Rotacao simples para a esquerda
void RotationLR(NodeAvl **node); //Funcao de Rotacao dupla para a direita
void RotationRL(NodeAvl **node); //Funcao de Rotacao dupla para a esquerda

/*As funcoes de Inserir, Remover e Buscar na arvore, utilizam como parametros, alem do nó usado,
uma chave generica e uma funcao de compara valores genericas que e definidada pelo programador usuario*/

int insertAvl(NodeAvl **node, NodeAvl *novo, int (compararValores)(void*,void*)); //Funcao de Insercao da arvore
NodeAvl* searchAvl(NodeAvl *node, void *chave, int (comparaValores)(void*,void*)); //Funcao de Busca de um node

/*Funcao Remover recebe como parametro a funcao generica freeInfo para 
remocao da informacao do no a ser removido*/
NodeAvl* deleteAvl(NodeAvl **node, void *chave, int (compararValores)(void*,void*), void freeInfo(NodeAvl* node)); //Funcao de Remocao de um node

int heightAvl(NodeAvl *raiz); //Funcao que retona a altura do nó

/*Essa funcao recebe uma funcao genérica para impressao*/
void printAvl(NodeAvl *raiz, int nivel,void (imprimeNo)(void*,void*)); //Funcao que imprime uma arvore

/*Demais funcoes*/
void limparTela(); //Limpa a tela para melhor visualizaçao
void destroyAvl(Avl *avl); //Destroi a arvore
void auxDestroyAvl(NodeAvl *node) ;//Auxiliar de 'destroyAvl' que libera nó por nó

#endif //ARVBINAVL_H