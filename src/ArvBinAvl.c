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

NodeAvl *findSmallestElementAVL(NodeAvl *node){
    if(!node->left) return node;
    else return findSmallestElementAVL(node->left);
}

int deleteAvl(NodeAvl **node, int chave){

    if (!(*node)) return 0;
    if(chave<(*node)->chave){ //se a chave que quero remover é menor que o nó
        if(deleteAvl(&(*node)->left, chave)==1){ //Como foi removida do lado esquerdo, preciso verificar se preciso balancear a arvore da direita
            if(balanceAVL(*node)>=2){
                if (heightAvl((*node)->right->left)<=heightAvl((*node)->right->right)) RotationRR(node);
                else RotationRL(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
        }
    }
    if(chave>(*node)->chave){ //se a chave que quero remover é maior que o nó
        if(deleteAvl(&(*node)->right, chave)==1){ //Como foi removida do lado direito, preciso verificar se preciso balancear a arvore da esquerda
            if(balanceAVL(*node)>=2){
                if (heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                else RotationLR(node);
            }
            (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
        }
    }
    if(chave==(*node)->chave){
        if(((*node)->left==NULL || (*node)->right==NULL)){ //O pai tem 1 ou 0 filhos;
            NodeAvl *Remover=(*node); //Aponta pro nó a ser removido
            if((*node)->left!=NULL)  *node=(*node)->left;
            else *node=(*node)->right;
            free(Remover);
        }else{ //o pai tem 2 filhos;
            NodeAvl *temp=findSmallestElementAVL((*node)->right); //Procura a menor chave da subarvore a direita
            (*node)->chave=temp->chave; //Nó atual recebe a menor chave
            if(deleteAvl(&(*node)->right, (*node)->chave)){ //chama a função delete para remover a menor chave da subarvore a direita (que nao tem nenhum filho)
                if(balanceAVL(*node)>=2){
                    if(heightAvl((*node)->left->right)<=heightAvl((*node)->left->left)) RotationLL(node);
                    else RotationLR(node);
                }
                (*node)->fatorBal = heightAvl((*node)->left) - heightAvl((*node)->right);
            }  
        }
    }

    return 1;
}


void imprimeArvore(NodeAvl *T, int nivel){
    int i;
    if(T!=NULL){
        imprimeArvore(T->right, nivel+1);
        for(i=0; i<nivel; i++) printf("\t");
        printf("(%d):%d\n",T->chave,T->fatorBal);
        imprimeArvore(T->left, nivel+1);
    }
}

//Limpa a tela para melhor visualizaçao
void limparTela(){
    system("cls||clear");
}

//Apresenta um menu para realizacao das operacoes
void menu(Avl *avl){
    printf("\n ============================= MENU INICIAL ======================\n\n");
    int opcao=1, insert, delete;
    int valor;

    while(opcao > 0 && opcao < 4.1){
        printf("\nDeseja: Inserir(1) - Deletar(2) - Pesquisar(3) - Imprimir(4) - Sair(0) ? \n");
        scanf("%d",&opcao);
        
        switch (opcao)
        {
        case 1:
            limparTela();
            printf("\nInserindo\n");
            printf("Digite um valor para inserir na AVL:\t");
            scanf("%d", &valor);
            insert = insertAvl(&(avl->raiz),valor);

            if(insert) printf("\nInsercao concluida!\n\n");
            else printf("\nErro na insercao!\n");
            printf("Imprimindo arvore...\n\n");
            imprimeArvore(avl->raiz, heightAvl(avl->raiz));
            break;
        case 2:
            printf("\nDeletando\n");
            printf("Digite um valor para deletar da AVL:\t");
            scanf("%d", &valor);
            delete = deleteAvl(&(avl->raiz),valor);

            if(delete) printf("\nRemocao concluida!\n\n");
            else printf("\nErro na remocao!\n");
            printf("Imprimindo arvore...\n\n");
            imprimeArvore(avl->raiz, heightAvl(avl->raiz));
            break;
        case 3:
            limparTela();
            printf("\nPesquisando\n");
            printf("Digite um valor para pesquisar na AVL:\t");
            scanf("%d", &valor);
            NodeAvl *ptr = searchAvl(&(*(avl->raiz)),19);
            printf("Chave: %d\n",avl->raiz->chave);
            printf("Fator de balanceamento: %d\n",avl->raiz->fatorBal);
            break;
        case 4:
            limparTela();
            if(avl->raiz == NULL) printf("Arvore vazia!\n");
            else{
                printf("\nImprimindo a arvore:\n");
                imprimeArvore(avl->raiz, heightAvl(avl->raiz));
            }
            break;
        default:
            limparTela();
            printf("\nFinalizando programa!\n");
            if(avl->raiz == NULL) printf("Arvore vazia!\n");
            else{
                printf("\nArvore final:\n");
                imprimeArvore(avl->raiz, heightAvl(avl->raiz));
            }
            break;
        }
        
    }
}