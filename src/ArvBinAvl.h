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
    void *info; //Chave generica (deve ser declarada no arquivo teste)
    int fatorBal; //Fator de balanceamento do no
    struct nodeAvl *right, *left; //Ponteiros para os filhos do no
}NodeAvl;

/*------------------------------------------ Estrutura da raiz da arvore ----------------------------------*/
typedef struct radixAvl{
    NodeAvl *raiz; //Raiz da arvore (No-Cabeca)
}Avl;

/*------------------------------------------ Assinaturas das funcoes -------------------------------------*/

/* ==================================  Funcoes de criacao da arvore  =====================================*/

/*  Funcao que cria uma instancia do node
    Entrada: void
    Saida: instancia de NodeAvl
*/
NodeAvl* criaNode();

/*  Funcao que inicializa a arvore
    Entrada: void
    Saida: instancia de Avl
*/
Avl* criaAvl();

/* ==================================  Funcoes de rotacao da arvore  =====================================*/

/*  
    Entrada: NodeAvl **node (No critico)
    Saida: void
*/
void RotationLL(NodeAvl **node); //Funcao de Rotacao simples para a direita
void RotationRR(NodeAvl **node); //Funcao de Rotacao simples para a esquerda
void RotationLR(NodeAvl **node); //Funcao de Rotacao dupla para a direita
void RotationRL(NodeAvl **node); //Funcao de Rotacao dupla para a esquerda

/* ==================================  Funcao de Insercao da arvore  =====================================*/
/*
    Entrada: (1) NodeAvl **node (Raiz da arvore/subarvore)
             (2) NodeAvl *novo (No a ser inserido)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
    Saida: 1 se inseriu ou 0 se nao inseriu
*/
int insertAvl(NodeAvl **node, NodeAvl *novo, int (compararValores)(void*,void*)); 

/* ==================================  Funcao de Busca da arvore  ========================================*/
/*  
    Entrada: (1) NodeAvl **node (Raiz da arvore/subarvore)
             (2) void *chave (Valor a ser buscado)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
    Saida: No que possui a chave buscada ou NULL
*/
NodeAvl* searchAvl(NodeAvl *node, void *chave, int (comparaValores)(void*,void*));

/* ==================================  Funcao de Remocao da arvore  ======================================*/
/*  
    Entrada: (1) NodeAvl **node (Raiz da arvore/subarvore)
             (2) void *chave (Valor a ser removido)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
    Saida: No que possui a chave buscada ou NULL
*/
NodeAvl* deleteAvl(NodeAvl **node, void *chave, int (compararValores)(void*,void*), void freeInfo(NodeAvl* node));

/* =============================  Funcao que retorna altura da arvore  ===================================*/
/*  
    Entrada: (1) NodeAvl *raiz (Raiz da arvore/subarvore)
    Saida: Altura da arvore/subarvore inserida
*/
int heightAvl(NodeAvl *raiz);

/* =================================  Funcao que imprime a  arvore  ======================================*/
/*  
    Entrada: (1) NodeAvl *raiz (Raiz da arvore/subarvore)
             (2) int nivel (Altura da arvore)
             (3) int (imprimeNo)(void*,void*) -> Funcao imprime a informacao do no,
                 deve ser implementada no arquivo teste
    Saida: void
*/
void printAvl(NodeAvl *raiz, int nivel,void (imprimeNo)(void*,void*));

/* ===============================  Funcao que libera a memoria  =========================================*/
/*  
    Entrada: (1) Avl *avl (Raiz da arvore/subarvore)
    Saida: void
*/
void destroyAvl(Avl *avl); //Destroi a arvore

/*  
    Entrada: (1) NodeAvl *node (Raiz da arvore/subarvore)
    Saida: void
*/
void auxDestroyAvl(NodeAvl *node) ;//Auxiliar de 'destroyAvl' que libera nó por nó

#endif //ARVBINAVL_H