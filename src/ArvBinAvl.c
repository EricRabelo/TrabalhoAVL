/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: .c
*/

#include "ArvBinAvl.h"

/* ==================================  Funcoes de criacao da arvore  =====================================*/

/*  Funcao que cria uma instancia do node
    Entrada: void
    Saida: instancia de NodeAvl
*/
NodeAvl* criaNode(){
    NodeAvl *novo;
    novo = (NodeAvl*)malloc(sizeof(NodeAvl));
    if(novo == NULL){
        printf("Erro na alocacao!");
        exit(1);
    }
    // O campo ->info deve ser declarado no arquivo teste
    novo->fatorBal = 0; //No folha tem fator de balanceamento = 0
    novo->right = novo->left = NULL; //No folha nao tem filhos
    return novo;
}

/*  Funcao que inicializa a arvore
    Entrada: void
    Saida: instancia de Avl
*/
Avl* criaAvl(){
    Avl *ptr;
    ptr = (Avl*)malloc(sizeof(Avl));

    if(ptr == NULL){
        printf("Erro na alocacao!");
        exit(1);
    }

    ptr->raiz = NULL; //Arvore vazia
    return ptr;
}

/* =============================  Funcao que retorna altura da arvore  ===================================*/

/*  Funcao que calcula a altura da arvore/subarvore
    Entrada: (1) NodeAvl *raiz (Raiz da arvore/subarvore)
    Saida: Altura da arvore/subarvore inserida
*/
int heightAvl(NodeAvl *raiz){
    if(!raiz) return -1; //-1 para compensar a contagem da raiz

    int tam_esq, tam_dir;

    tam_esq = 1 + heightAvl(raiz->left);
    tam_dir = 1 + heightAvl(raiz->right);

    if(tam_dir > tam_esq) return tam_dir;
    else return tam_esq;
}

/* =============================  Funcao que retorna o balanco da arvore  ================================*/

/*  Calcula o fator de balanço de um nó
    Entrada: (1) NodeAvl *avl
    Saida: Fator de balanceamento do no (altura esquerda - altura direita)
*/
int balanceAVL(NodeAvl *avl){
	return labs(heightAvl(avl->left)-heightAvl(avl->right));
}

/* ==================================  Funcoes de rotacao da arvore  =====================================*/

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

/* ==================================  Funcao de Busca da arvore  ========================================*/

/*  Funcao de Busca de um node
    Entrada: (1) NodeAvl *node (Raiz da arvore/subarvore)
             (2) void *chave (Valor a ser buscado)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
    Saida: No que possui a chave buscada ou NULL
*/
NodeAvl* searchAvl(NodeAvl *node, void *chave, int (compararValores)(void*, void*)){
    if(!node) return NULL;
    if(compararValores(node->info, chave) == 0) return node; //Se as chaves sao iguais
    else{
        if(compararValores(node->info, chave) > 0){ //Funcao compararValores retorna 1
            return searchAvl(node->left,chave,compararValores); //Chave buscada e menor
        }else{
            //Funcao compararValores retorna -1
            return searchAvl(node->right,chave,compararValores); //Chave buscada e maior
        }
    }
}

/* ==================================  Funcao de Insercao da arvore  =====================================*/

/*  Funcao de Insercao da arvore
    Entrada: (1) NodeAvl **node (Raiz da arvore/subarvore)
             (2) NodeAvl *novo (No a ser inserido)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
    Saida: 1 se inseriu ou 0 se nao inseriu
*/
int insertAvl(NodeAvl **node, NodeAvl *novo, int (comparaValores)(void*,void*)){
    if(*node == NULL){ //Lugar de insercao do no
        (*node) = novo;
        return 1;
    }
    else{
        if(comparaValores((*node)->info,novo->info)==0) return 0; //Valores sao iguais entao nao insere
        else{
            if(comparaValores((*node)->info,novo->info)>0){ //Chave a ser inserida e menor que do no atual

                if(insertAvl(&(*node)->left, novo, comparaValores) == 1){ //Chamada recursiva para esquerda
                                                                          
                    if(balanceAVL(*node) >= 2){ //Verifica se o balanceamento passou de 2 em modulo (precisa balancear)
                        if(comparaValores(novo->info,(*node)->left->info)<0){ //Insercao foi no filho esquerdo da subarvore esquerda
                            RotationLL(node);
                        }else RotationLR(node);//Insercao foi no filho direito da subarvore esquerda
                    }
                }
            }else{
                if(comparaValores((*node)->info,novo->info)<0){ //Chave a ser inserida e maior que do no atual
                    
                    if(insertAvl(&(*node)->right, novo, comparaValores) == 1){ //Chamada recursiva para direita

                        if(balanceAVL(*node) >= 2){ //Verifica se o balanceamento passou de 2 em modulo (precisa balancear)
                            if(comparaValores(novo->info ,(*node)->right->info)>0){ //Insercao foi no filho direito da subarvore direita
                                RotationRR(node);
                            }else RotationRL(node);//Insercao foi no filho esquerdo da subarvore direita
                        }
                    }
                }
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right); //Atualiza balanceamento do no
            return 1; //Inseriu
        }
    }
}

/* ===========================  Funcao que retorna menor elemento da subarvore  ===========================*/

/*  
    Entrada: (1) NodeAvl *node (Raiz da subarvore)
    Saida: Ponteiro para no com menor valor
*/
NodeAvl *findSmallestElementAVL(NodeAvl *node){
    if(!node->left) return node; //Encontrou ultimo elemento a esquerda
    else return findSmallestElementAVL(node->left);
}

/* ==================================  Funcao de Remocao da arvore  ======================================*/
/*  
    Entrada: (1) NodeAvl **node (Raiz da arvore/subarvore)
             (2) void *chave (Valor a ser removido)
             (3) int (compararValores)(void*,void*) -> Funcao que compara as informacoes dos nos,
                 deve ser implementada no arquivo teste
             (4) void freeInfo(NodeAvl* node) -> Funcao que libera a memoria do no,
                 deve ser implementada no arquivo teste
    Saida: No que possui a chave buscada ou NULL
*/
NodeAvl *deleteAvl(NodeAvl **node, void *chave, int (compararValores)(void*,void*),void freeInfo(NodeAvl* node)){
    if (!(*node)) return 0;
    NodeAvl *Remover;

    if(compararValores(chave,(*node)->info) < 0){ //Se a chave que quero remover é menor que o nó

        if((Remover = deleteAvl(&(*node)->left, chave, compararValores,freeInfo))){ //Como foi removida do lado esquerdo, 
                                                                                  //preciso verificar se preciso balancear 
                                                                                  //a arvore da direita
            
            if(balanceAVL(*node)>=2){ //Verifica se o balanceamento passou de 2 em modulo (precisa balancear)
                if (heightAvl((*node)->right->left)<=heightAvl((*node)->right->right)) RotationRR(node);
                else RotationRL(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right); //Atualiza balanceamento do no
        }
    }
    if(compararValores(chave,(*node)->info) > 0){ //Se a chave que quero remover é maior que o nó
        
        if((Remover = deleteAvl(&(*node)->right, chave, compararValores,freeInfo))){ //Como foi removida do lado direito, 
                                                                                   //preciso verificar se preciso balancear 
                                                                                   //a arvore da esquerda
            
            if(balanceAVL(*node)>=2){ //Verifica se o balanceamento passou de 2 em modulo (precisa balancear)
                if (heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                else RotationLR(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right); //Atualiza balanceamento do no
        }
    }
    if(compararValores(chave,(*node)->info) == 0){ //Encontrou a chave
        
        if(((*node)->left==NULL || (*node)->right==NULL)){ //O pai tem 1 ou 0 filhos;
            Remover = (*node); //Aponta pro nó a ser removido
            if((*node)->left!=NULL)  *node=(*node)->left;
            else *node=(*node)->right;

        }else{ //o pai tem 2 filhos;
            NodeAvl *temp=findSmallestElementAVL((*node)->right); //Procura a menor chave da subarvore a direita
            
            freeInfo(*node);
            (*node)->info=temp->info; //Nó atual recebe a menor chave
            (*node)->info=temp->info;
            
            if((Remover = deleteAvl(&(*node)->right, (*node)->info, compararValores, freeInfo))){ //chama a função delete 
                                                                                                //para remover a menor chave 
                                                                                                //da subarvore a direita (que 
                                                                                                //nao tem nenhum filho)
                
                if(balanceAVL(*node)>=2){
                    if(heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                    else RotationLR(node);
                }
                (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right); //Atualiza balanceamento do no
            }  
        }
    }
    return Remover;
}

/* =================================  Funcao que imprime a  arvore  ======================================*/
/*  
    Entrada: (1) NodeAvl *raiz (Raiz da arvore/subarvore)
             (2) int nivel (Altura da arvore)
             (3) int (imprimeNo)(void*,void*) -> Funcao imprime a informacao do no,
                 deve ser implementada no arquivo teste
    Saida: void
*/
void printAvl(NodeAvl *raiz, int nivel,void (imprimeNo)(void*,void*)){
    int i;
    if(raiz!=NULL){
        printAvl(raiz->right, nivel+1, imprimeNo);
        for(i=0; i<nivel; i++) printf("\t");
        imprimeNo(raiz,raiz->info); //Funcao generica para impressao da informacao do no
        printAvl(raiz->left, nivel+1, imprimeNo);
    }
}

/* ===============================  Funcao que libera a memoria  =========================================*/
/*  Auxiliar de 'destroyAvl' que libera no por no
    Entrada: (1) NodeAvl *node (Raiz da arvore/subarvore)
    Saida: void
*/
void auxDestroyAvl(NodeAvl *node){
    if (!node) return;
    auxDestroyAvl(node->left);
    auxDestroyAvl(node->right);
    free(node);
    return;
}

/*  Libera a raiz da arvore
    Entrada: (1) Avl *avl (Ponteiro para a raiz da arvore)
    Saida: void
*/
void destroyAvl(Avl *avl){
    auxDestroyAvl(avl->raiz);
    free(avl);
}