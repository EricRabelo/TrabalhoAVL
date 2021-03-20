/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: main.c
VERSAO: 1.0
*/

#include <stdlib.h>
#include "ArvBinAvl.c"

int compararValores(void *val1, void *val2){
    int num1 = (int)val1;
    int num2 = (int)val2;

    if(num1 == num2) return 0;
    else if (num1 > num2 ) return 1;
    else return -1;
}

void imprimirArvore(void *node, void *nivel){
    int *valor = (int*)node;
    NodeAvl *ptr = (NodeAvl*)node;
    int *level = (int*)nivel;
    int i;
    for(i = 0; i<(*level); i++) printf("\t");
    printf("(%d):%d", *valor, ptr->fatorBal);
}

int main(int argc, char const *argv[])
{
    Avl *avl = criaAvl();

    //Apresenta um menu para realizacao das operacoes
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
                insert = insertAvl(&(avl->raiz),(void*)valor, compararValores);

                if(insert) printf("\nInsercao concluida!\n\n");
                else printf("\nErro na insercao!\n");
                // printf("Imprimindo arvore...\n\n");
                // imprimeArvore(avl->raiz, heightAvl(avl->raiz));
                break;
            case 2:
                // limparTela();
                // printf("\nDeletando\n");
                // printf("Digite um valor para deletar da AVL:\t");
                // scanf("%d", &valor);
                // delete = deleteAvl(&(avl->raiz),valor);

                // if(delete) printf("\nRemocao concluida!\n\n");
                // else printf("\nErro na remocao!\n");
                // printf("Imprimindo arvore...\n\n");
                // imprimeArvore(avl->raiz, heightAvl(avl->raiz));
                break;
            case 3:
                // limparTela();
                // printf("\nPesquisando\n");
                // printf("Digite um valor para pesquisar na AVL:\t");
                // scanf("%d", &valor);

                // NodeAvl *ptr = searchAvl(&(*(avl->raiz)),(void*)valor, compararValores);

                // printf("Chave: %d\n",ptr->chave);
                // printf("Fator de balanceamento: %d\n",avl->raiz->fatorBal);
                break;
            case 4:
                limparTela();
                if(avl->raiz == NULL) printf("Arvore vazia!\n");
                else{
                    printf("\nImprimindo a arvore:\n");
                    imprimeArvore(avl->raiz, heightAvl(avl->raiz),imprimirArvore);
                }
                break;
            default:
                limparTela();
                printf("\nFinalizando programa!\n");
                // if(avl->raiz == NULL) printf("Arvore vazia!\n");
                // else{
                //     printf("\nArvore final:\n");
                //     imprimeArvore(avl->raiz, heightAvl(avl->raiz));
                // }
                break;
        }
        
    }
    destroyAvl(avl);
    printf("\n");
    return 0;
}
