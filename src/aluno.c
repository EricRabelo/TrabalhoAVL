
#include <stdlib.h>
#include <string.h>
#include "ArvBinAvl.c"

/*------------------------------------------ Estrutura da info do no -----------------------------------------*/

typedef struct info{
    int matricula;
    char *nome;
    char *disciplina;
}Info;


Info *createInfo(){
	Info *info;
    char key2[50],key3[50];
    int key1;

	if((info=(Info *)malloc(sizeof(Info))) && (info->nome=(char *)malloc(sizeof(char))) && (info->disciplina=(char *)malloc(sizeof(char)))){ //se o espaço para o elemento info e info->key for mallocado;
        
        printf("Digite o nome do aluno: ");
        scanf("%s",key2);
        printf("Digite a matricula: ");
        scanf("%d",&key1);
        printf("Digite a disciplina: ");
        scanf("%s",key3);

        strcpy(info->nome,key2);
        info->matricula = key1;
        strcpy(info->disciplina,key3);
	}
	return info;
}

NodeAvl *auxCriaNode(Info *inf){
    NodeAvl *novo = criaNode();
    novo->info = inf;
    return novo;
}

Info* fazerCastInfo(NodeAvl* node){
    return (Info *) node->info;
}

void freeInfo(NodeAvl* node){
    Info *inf = fazerCastInfo(node);
    free(inf->nome);
    free(inf->disciplina);
    free(inf);
}

void imprimeNo(void *ptr, void *info){
    NodeAvl *node = (NodeAvl*)ptr;
    Info *inf = (Info*)info;
    int chave = inf->matricula;
    printf("(%d):%d\n",chave,node->fatorBal);
}

void imprimeInfo(NodeAvl *node){
    Info *inf;
    inf=fazerCastInfo(node);
    if(!inf) return;
    printf("\nNome aluno: %s", inf->nome);
    printf("\nMatricula: %d", inf->matricula);
    printf("\nDisciplina: %s\n", inf->disciplina);
}

int compararValores(void *val1, void *val2){
    Info *inf1 = (Info*)val1;
    Info *inf2 = (Info*)val2;

    int value1 = inf1->matricula;
    int value2 = inf2->matricula;

    if(value1 == value2) return 0;
    else if(value1 > value2) return 1;
    else return -1;
}

void menu(){
    //Apresenta um menu para realizacao das operacoes
    printf("\n ============================= MENU INICIAL ======================\n\n");
    int opcao=1, insert;
    int valor;

    Avl *avl = criaAvl();

    while(opcao > 0 && opcao < 4.1){
        printf("\nDeseja: Inserir(1) - Deletar(2) - Pesquisar(3) - Imprimir(4) - Sair(0) ? \n");
        printf("Resposta: ");
        scanf("%d",&opcao);

        switch (opcao)
        {
            case 1:
                system("cls||clear");
                printf("\nInserindo\n");
                Info *inf = createInfo();
                NodeAvl *novo = auxCriaNode(inf);
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
                system("cls||clear");
                printf("\nDeletando\n");
                printf("\nArvore atual:\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                printf("Digite a matricula do aluno para deletar da AVL:\t");
                scanf("%d", &valor);
                NodeAvl *delete;

                delete = deleteAvl(&(avl->raiz),&valor,compararValores,freeInfo);
                
                if(delete) printf("\nRemocao concluida!\n\n");
                else printf("\nErro na remocao!\n");

                free(delete);

                printf("Imprimindo arvore...\n\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                break;
            case 3:
                system("cls||clear");
                printf("\nPesquisando\n");
                printf("Digite a matricula do aluno para pesquisar na AVL:\t");
                scanf("%d", &valor);

                NodeAvl *ptr = searchAvl(&(*(avl->raiz)),&valor,compararValores);
                if(ptr) imprimeInfo(ptr);
                else printf("\nAluno nao matriculado\n");
                break;
            case 4:
                system("cls||clear");
                if(avl->raiz == NULL) printf("Arvore vazia!\n");
                else{
                    printf("\nImprimindo a arvore:\n\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }
                break;
            default:
                system("cls||clear");
                printf("\nFinalizando programa!\n");
                if(avl->raiz == NULL) printf("Arvore vazia!\n");
                else{
                    printf("\nArvore final:\n\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }
                break;
        }

    }
    destroyAvl(avl);
}

int main(void)
{
    menu();

    printf("\n");
    return 0;
}