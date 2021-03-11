/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO
DATA CRIACAO: 11/03/2021
ARQUIVO: .h
VERSAO: 1.0
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
void simple_RightRotation(NodeAvl *node, int bool); //Funcao de Rotacao simples para a direita
void simple_LeftRotation(NodeAvl *node, int bool); //Funcao de Rotacao simples para a esquerda
void double_RightRotation(NodeAvl *node, int bool); //Funcao de Rotacao dupla para a direita
void double_LeftRotation(NodeAvl *node, int bool); //Funcao de Rotacao dupla para a esquerda
NodeAvl* insertAvl(NodeAvl *node, int bool, int chave); //Funcao de Insercao da arvore
NodeAvl* searchAvl(NodeAvl *node, int bool, int chave); //Funcao de Busca de um node
int deleteAvl(NodeAvl *node, int bool, int chave); //Funcao de Remocao de um node
int heightAvl(NodeAvl *raiz); //Funcao que retona a altura da raiz
void printAvl(NodeAvl *raiz); //Funcao que imprime a arvore no formato em-ordem

#endif //ARVBINAVL_H