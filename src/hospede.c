/*
TRABALHO DE IMPLEMENTACAO DE ARVORE BINARIA DE BUSCA BALANCEADA (AVL)
AUTOR: LUIZ GUSTAVO FALQUETO e ERIC RABELO
DATA CRIACAO: 11/03/2021
ARQUIVO: .c
*/

#include <string.h>
#include "ArvBinAvl.h"

/*------------------------------------------ Estrutura da info do no -----------------------------------------*/

typedef struct infoCliente{ //Definicao da estrutura da informacao
    long int cadastro;
    char *nomeCliente;
    char *numQuarto;
    float valorDiaria;
}Cliente;

Cliente *createCliente(){ //Cria a informacao para ser colocada na info do no
	Cliente *cadCliente;
    int tamPalavras = 80;
    char nome[tamPalavras],quarto[tamPalavras];
    long int cadID;
    float diaria;

	if((cadCliente=(Cliente *)malloc(sizeof(Cliente))) && (cadCliente->nomeCliente=(char *)malloc(sizeof(char))) 
        && (cadCliente->numQuarto=(char *)malloc(sizeof(char)))){ //se o espaço para o elemento cadCliente e seus 
                                                                  //campos forem alocados;
        
        setbuf(stdin, 0);
        printf("Digite o nome do hospede: ");
        fgets(nome,tamPalavras,stdin);
        printf("Digite o cadastro do hospede: ");
        scanf("%ld",&cadID);
        setbuf(stdin, 0);
        printf("Digite o numero do quarto: ");
        fgets(quarto,tamPalavras,stdin);
        printf("Digite o valor da diaria: ");
        scanf("%f",&diaria);

        strcpy(cadCliente->nomeCliente,nome);
        cadCliente->cadastro = cadID;
        strcpy(cadCliente->numQuarto,quarto);
        cadCliente->valorDiaria = diaria;
	    return cadCliente;
	}else return NULL;
}

NodeAvl *auxCriaNode(Cliente *inf){ //Funcao para inserir a estrutura de informa no campo info do no
    NodeAvl *novo = criaNode();
    novo->info = inf;
    return novo;
}

Cliente* fazerCastCliente(NodeAvl* node){ //Faz o cast do campo generico do no para o nomeCliente da estrutura
    return (Cliente *) node->info;
}

void imprimeCliente(NodeAvl *node){ //Imprime o conteudo do no
    Cliente *inf;
    inf=fazerCastCliente(node);
    if(!inf) return;
    printf("\nNome do hospede: %s", inf->nomeCliente);
    printf("Cadastro: %ld", inf->cadastro);
    printf("\nQuarto ocupado: %s", inf->numQuarto);
    printf("Valor da diaria: %.2f\n", inf->valorDiaria);
}

void freeCliente(NodeAvl* node){ //Libera o no
    Cliente *inf = fazerCastCliente(node);
    free(inf->nomeCliente);
    free(inf->numQuarto);
    free(inf);
}

void imprimeNo(void *ptr, void *info){ //Imprime a chave de busca e balanceamento (usada na impressao da arvore)
    NodeAvl *node = (NodeAvl*)ptr;
    Cliente *inf = (Cliente*)info;
    printf("(%ld):%d\n",inf->cadastro,node->fatorBal);
}

int compararValores(void *val1, void *val2){ //Comparacao dos valores (usada na Insercao, Remocao e Busca na arvore)
    Cliente *inf1 = (Cliente*)val1;
    Cliente *inf2 = (Cliente*)val2;

    int value1 = inf1->cadastro;
    int value2 = inf2->cadastro;

    if(value1 == value2) return 0;
    else if(value1 > value2) return 1;
    else return -1;
}

void menu(){ //Apresenta um menu para realizacao das operacoes
    system("cls||clear");
    printf("\n ============================= MENU INICIAL ======================\n\n");
    int insert, continuar;
    float opcao=1.0;
    long int valor;

    Avl *avl = criaAvl();

    while(opcao > 0 && opcao < 4.1){
        printf("\nDeseja: Inserir(1) - Deletar(2) - Pesquisar(3) - Imprimir(4) - Sair(0) ? \n");
        printf("Resposta: ");
        scanf("%f",&opcao);

        switch ((int)opcao)
        {
            case 1:
                system("cls||clear");
                printf("\nInserindo\n");
                Cliente *inf = createCliente();
                NodeAvl *novo = auxCriaNode(inf);
                if(!novo || !inf){
                    printf("Erro de alocacao!\n");
                    exit(1);
                }
                insert = insertAvl(&(avl->raiz),novo,compararValores);

                if(insert){
                    system("cls||clear");
                    printf("\nInsercao concluida!\n");
                    getchar();
                    printf("\nDados do hospede inseridos na Avl:\n");
                    imprimeCliente(novo);
                    getchar();
                    system("cls||clear");
                } 
                else printf("\nErro na insercao!\n");
                if(avl->raiz!=NULL){
                    printf("\nImprimindo arvore...\n\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }else printf("Arvore vazia!\n\n");
                break;


            case 2:
                system("cls||clear");
                printf("\nDeletando\n");
                printf("\nArvore atual:\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                printf("\nDigite a cadastro do hospede para deletar da AVL:\t");
                scanf("%ld", &valor);
                NodeAvl *delete;

                delete = searchAvl(&(*(avl->raiz)),&valor,compararValores);
                if(delete){
                    system("cls||clear");
                    printf("\nDados do hospede que serao excluidos:\n");
                    imprimeCliente(delete);
                    printf("\nDeseja continuar? [1 para sim/0 para nao] ");
                    scanf("%d",&continuar);
                    if(continuar==0){
                        system("cls||clear");
                        break;
                    }
                    getchar();
                    system("cls||clear");
                }
                
                delete = deleteAvl(&(avl->raiz),&valor,compararValores,freeCliente);
                
                if(delete){
                    printf("\nRemocao concluida!\n");
                    getchar();
                    system("cls||clear");
                }else printf("\nErro na remocao!\n");

                free(delete);

                printf("\nImprimindo arvore...\n\n");
                printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                break;


            case 3:
                system("cls||clear");
                printf("\nPesquisando\n");
                printf("Digite a cadastro do hospede para pesquisar na AVL:\t");
                scanf("%ld", &valor);

                NodeAvl *ptr = searchAvl(&(*(avl->raiz)),&valor,compararValores);
                if(ptr) imprimeCliente(ptr);
                else printf("\nCliente nao cadastrado\n");
                break;


            case 4:
                system("cls||clear");
                if(avl->raiz == NULL) printf("\nArvore vazia!\n");
                else{
                    printf("\nImprimindo a arvore:\n\n");
                    printAvl(avl->raiz, heightAvl(avl->raiz), imprimeNo);
                }
                break;


            default:
                system("cls||clear");
                printf("\nFinalizando programa!\n");
                if(avl->raiz == NULL) printf("\nArvore vazia!\n");
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