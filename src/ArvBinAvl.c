/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: .c
*/

#include "ArvBinAvl.h"

// Funcao que cria uma instancia do node
NodeAvl* criaNode(){
    NodeAvl *novo;
    novo = (NodeAvl*)malloc(sizeof(NodeAvl));
    if(novo == NULL){
        printf("Erro na alocacao!");
        exit(1);
    }
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
NodeAvl* searchAvl(NodeAvl *node, void *chave, int (compararValores)(void*, void*)){
    if(!node) return NULL;
    if(compararValores(node->chave, chave) == 0) return node;
    else{
        if(compararValores(node->chave, chave) > 0){
            return searchAvl(node->left,chave,compararValores);
        }else{
            return searchAvl(node->right,chave,compararValores);
        }
    }
}

 //Funcao de Insercao da arvore
int insertAvl(NodeAvl **node, NodeAvl *novo, int (comparaValores)(void*,void*)){
    if(*node == NULL){
        (*node) = novo;
        return 1;
    }
    else{
        // if((*node)->chave == novo->chave) return 0;
        if(comparaValores((*node)->chave,novo->chave)==0) return 0;
        else{
            // if((*node)->chave > novo->chave){
            if(comparaValores((*node)->chave,novo->chave)>0){

                if(insertAvl(&(*node)->left, novo, comparaValores) == 1){

                    if(balanceAVL(*node) >= 2){
                        // if(novo->chave < (*node)->left->chave){
                        if(comparaValores(novo->chave,(*node)->left->chave)<0){
                            RotationLL(node);
                        }else RotationLR(node);
                    }
                }
            }else{
                // if((*node)->chave < novo->chave){
                if(comparaValores((*node)->chave,novo->chave)<0){
                    if(insertAvl(&(*node)->right, novo, comparaValores) == 1){

                        if(balanceAVL(*node) >= 2){
                            // if(novo->chave > (*node)->right->chave){
                            if(comparaValores(novo->chave ,(*node)->right->chave)>0){
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

NodeAvl *findSmallestElementAVL(NodeAvl *node){
    if(!node->left) return node;
    else return findSmallestElementAVL(node->left);
}

NodeAvl *deleteAvl(NodeAvl **node, void *chave, int (compararValores)(void*,void*),void freeInfo(NodeAvl* node)){
    if (!(*node)) return 0;
    NodeAvl *Remover;
    // if(chave<(*node)->chave){ //se a chave que quero remover é menor que o nó
    if(compararValores(chave,(*node)->chave) < 0){
        if(Remover = deleteAvl(&(*node)->left, chave, compararValores,freeInfo)){ //Como foi removida do lado esquerdo, preciso verificar se preciso balancear a arvore da direita
            if(balanceAVL(*node)>=2){
                if (heightAvl((*node)->right->left)<=heightAvl((*node)->right->right)) RotationRR(node);
                else RotationRL(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
        }
    }
    // if(chave>(*node)->chave){ //se a chave que quero remover é maior que o nó
    if(compararValores(chave,(*node)->chave) > 0){
        if(Remover = deleteAvl(&(*node)->right, chave, compararValores,freeInfo)){ //Como foi removida do lado direito, preciso verificar se preciso balancear a arvore da esquerda
            if(balanceAVL(*node)>=2){
                if (heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                else RotationLR(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
        }
    }
    // if(chave==(*node)->chave){
    if(compararValores(chave,(*node)->chave) == 0){
        if(((*node)->left==NULL || (*node)->right==NULL)){ //O pai tem 1 ou 0 filhos;
            Remover = (*node); //Aponta pro nó a ser removido
            if((*node)->left!=NULL)  *node=(*node)->left;
            else *node=(*node)->right;
        }else{ //o pai tem 2 filhos;
            NodeAvl *temp=findSmallestElementAVL((*node)->right); //Procura a menor chave da subarvore a direita
            freeInfo(*node);
            (*node)->chave=temp->chave; //Nó atual recebe a menor chave
            (*node)->info=temp->info;
            if(Remover = deleteAvl(&(*node)->right, (*node)->chave, compararValores, freeInfo)){ //chama a função delete para remover a menor chave da subarvore a direita (que nao tem nenhum filho)
                if(balanceAVL(*node)>=2){
                    if(heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                    else RotationLR(node);
                }
                (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
            }  
        }
    }
    return Remover;
}

 //Funcao que imprime uma arvore
void printAvl(NodeAvl *raiz, int nivel,void (imprimeNo)(void*,void*)){
    int i;
    if(raiz!=NULL){
        printAvl(raiz->right, nivel+1, imprimeNo);
        for(i=0; i<nivel; i++) printf("\t");
        imprimeNo(raiz,raiz->info);
        printAvl(raiz->left, nivel+1, imprimeNo);
    }
}

 //Auxiliar de 'destroyAvl' que libera no por no
void auxDestroyAvl(NodeAvl *node){
    if (!node) return;
    auxDestroyAvl(node->left);
    auxDestroyAvl(node->right);
    free(node);
    return;
}


 //Destroi a avl
void destroyAvl(Avl *avl){
    auxDestroyAvl(avl->raiz);
    free(avl);
}

//Limpa a tela para melhor visualizaçao
void limparTela(){
    system("cls||clear");
}