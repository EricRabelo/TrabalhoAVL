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
    int fatorBal;
    int chave;
    struct nodeAvl *right, *left;
}NodeAvl;

/*------------------------------------------ Estrutura da raiz da arvore -------------------------------------*/
typedef struct radizAvl{
    NodeAvl *raiz;
}Avl;

/*------------------------------------------ Assinaturas das funcoes -----------------------------------------*/
NodeAvl* criaNode(int chave); //Funcao que cria uma instancia do node
Avl* criaAvl(); //Funcao que inicializa a arvore

void RotationLL(NodeAvl **node); //Funcao de Rotacao simples para a direita
void RotationRR(NodeAvl **node); //Funcao de Rotacao simples para a esquerda
void RotationLR(NodeAvl **node); //Funcao de Rotacao dupla para a direita
void RotationRL(NodeAvl **node); //Funcao de Rotacao dupla para a esquerda

int insertAvl(NodeAvl **node, int chave); //Funcao de Insercao da arvore (1)
NodeAvl* searchAvl(NodeAvl *node, int chave); //Funcao de Busca de um node (1)
int deleteAvl(NodeAvl *node, int chave); //Funcao de Remocao de um node (1)

int heightAvl(NodeAvl *raiz); //Funcao que retona a altura da raiz

void printAVL(NodeAvl *node); //Funcao para imprimir arvore (2)

/*Legenda:
    (1) int(compara)(void *, void*) -> Funcao implementada pelo programador usuário para verificar
        se o elemento buscado esta presente ou nao na AVL
    (2) void (printFunction)(void *, void *) -> 
*/

#endif //ARVBINAVL_H