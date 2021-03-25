
#include <stdlib.h>
#include <string.h>
#include "ArvBinAvl.c"

/*------------------------------------------ Estrutura da info do no -----------------------------------------*/

typedef struct info{
    char *campo1;
    char *campo2;
    char *campo3;
}Info;


Info *createInfo(){
	Info *info;
    char key1[50],key2[50],key3[50];

	if((info=(Info *)malloc(sizeof(Info))) && (info->campo1=(char *)malloc(sizeof(char))) && (info->campo2=(char *)malloc(sizeof(char))) && (info->campo3=(char *)malloc(sizeof(char)))){ //se o espaço para o elemento info e info->key for mallocado;
        
        printf("Digite o nome do aluno: ");
        scanf("%s",key1);
        printf("Digite a matricula: ");
        scanf("%s",key2);
        printf("Digite a idade: ");
        scanf("%s",key3);

        strcpy(info->campo1,key1);
        strcpy(info->campo2,key2);
        strcpy(info->campo3,key3);
	}
	return info;
}

NodeAvl *auxCriaNode(Info *inf, char *chave){
    NodeAvl *novo = criaNode();
    novo->info = inf;
    novo->chave = chave;
    return novo;
}

Info* fazerCastInfo(NodeAvl* node){
    return (Info *) node->info;
}

void freeInfo(NodeAvl* node){
    Info *inf = fazerCastInfo(node);
    free(inf->campo1);
    free(inf->campo2);
    free(inf->campo3);
    free(inf);
}

void imprimeNo(void *ptr, void *info){
    NodeAvl *node = (NodeAvl*)ptr;
    Info *inf = (Info*)info;
    char *chave = (char*)inf->campo1;
    printf("(%s):%d\n",chave,node->fatorBal);
}

void imprimeInfo(NodeAvl *node){
    Info *inf;
    inf=fazerCastInfo(node);
    if(!inf) return;
    printf("\nNome aluno: %s", inf->campo1);
    printf("\nMatricula: %s", inf->campo2);
    printf("\nIdade: %s\n", inf->campo3);
}

int compararValores(void *val1, void *val2){
    char *value1 = (char*)val1;
    char *value2 = (char*)val2;

    return strcmp(value1,value2);
}

void menu(){
    //Apresenta um menu para realizacao das operacoes
    printf("\n ============================= MENU INICIAL ======================\n\n");
    int opcao=1, insert;
    int valor;
    char key1[50];

    Avl *avl = criaAvl();

    while(opcao > 0 && opcao < 4.1){
        printf("\nDeseja: Inserir(1) - Deletar(2) - Pesquisar(3) - Imprimir(4) - Sair(0) ? \n");
        scanf("%d",&opcao);

        switch (opcao)
        {
            case 1:
                limparTela();
                printf("\nInserindo\n");
                Info *inf = createInfo();
                NodeAvl *novo = auxCriaNode(inf,inf->campo1);
                if(!novo || !inf){
                    printf("Erro de alocacao!\n");
                    exit(1);
                }
                insert = insertAvl(&(avl->raiz),novo,compararValores);

                if(insert) printf("\nInsercao concluida!\n\n");
                else printf("\nErro na insercao!\n");
                if(avl->raiz!=NULL){
                    printf("Imprimindo arvore...\n\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }else printf("Arvore vazia!\n\n");
                break;
            case 2:
                limparTela();
                printf("\nDeletando\n");
                printf("\nArvore atual:\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                printf("Digite o nome do aluno para deletar da AVL:\t");
                scanf("%s", key1);
                NodeAvl *delete;

                delete = deleteAvl(&(avl->raiz),key1,compararValores,freeInfo);
                
                if(delete) printf("\nRemocao concluida!\n\n");
                else printf("\nErro na remocao!\n");

                free(delete);

                printf("Imprimindo arvore...\n\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                break;
            case 3:
                limparTela();
                printf("\nPesquisando\n");
                printf("Digite o nome do aluno para pesquisar na AVL:\t");
                scanf("%s", key1);

                NodeAvl *ptr = searchAvl(&(*(avl->raiz)),key1,compararValores);
                if(ptr) imprimeInfo(ptr);

                break;
            case 4:
                limparTela();
                if(avl->raiz == NULL) printf("Arvore vazia!\n");
                else{
                    printf("\nImprimindo a arvore:\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }
                break;
            default:
                limparTela();
                printf("\nFinalizando programa!\n");
                if(avl->raiz == NULL) printf("Arvore vazia!\n");
                else{
                    printf("\nArvore final:\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }
                break;
        }

    }
    destroyAvl(avl);
}