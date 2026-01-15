
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TITULO 20
#define MAX_DESCRICAO 300
#define MAX_SOLUCAO 300
#define MAX_STATUS 15

typedef struct ticket{
    int id;
    char titulo[MAX_TITULO];
    char descricao[MAX_DESCRICAO];
    char status[MAX_STATUS];
    char solucao[MAX_SOLUCAO];
    char tecnico[20];
    struct ticket *prox;
}Chamados;

//protótipos
void abreChamado(Chamados *head, Chamados **tail, int *id);
void listar(Chamados *head);
void listando(Chamados *head, char crit1[MAX_STATUS], char crit2[MAX_STATUS]);
void acessaChamado(Chamados *head);
void solucionando(Chamados *head);
void liberamemoria(Chamados *head);

int main()
{
    setlocale(LC_ALL, ".UTF-8");
    Chamados lista = {0};
    Chamados *Tail=&lista;
    printf("\nPrograma Gerenciador de Chamados\n");
    int i = 999;
    int opcao;
    do{
        printf("\nEscolha a opção desejada:\n");
        printf("1-Novo Chamado\n");
        printf("2-Listar Chamados\n");
        printf("3-Acessar chamado\n");
        printf("4-Adicionar Solução\n");
        printf("0-Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1: abreChamado(&lista, &Tail, &i); break;

            case 2: listar(&lista); break;

            case 3: acessaChamado(&lista); break;

            case 4: solucionando(&lista); break;

            case 0: liberamemoria(&lista); break;

            default: printf("\nOPÇÃO INVÁLIDA\n"); break;
        }
    }while(opcao!=0);

    return 0;
}

//Função para Abrir Novo Chamado
void abreChamado(Chamados *head, Chamados **tail, int *id){
    char titulo[MAX_TITULO];
    char descricao[MAX_DESCRICAO];
    Chamados *novo =(Chamados*) malloc(sizeof(Chamados));
    novo->prox=NULL;
    printf("\nTítulo: ");
    scanf(" %19[^\n]", titulo);
    printf("\nDescrição: ");
    scanf(" %255[^\n]", descricao);
    (*id)++;
    novo->id=*id;
    strcpy(novo->titulo, titulo);
    strcpy(novo->descricao, descricao);
    strcpy(novo->status, "Novo");
    (*tail)->prox=novo;
    *tail=novo;
}
//Função para listar todos
void listar(Chamados *head){
    if(head->prox==NULL){
        printf("\nNenhum Chamado a Ser Listado\n");
        return;
    }
    int opcao;
    printf("\nQuais chamados deseja ver?\n");
    printf("1-Não Solucionado\n");
    printf("2-Solucionado\n");
    printf("3-Fechado\n");
    printf("4-Todos\n");
    scanf(" %d", &opcao);
    switch(opcao){
        case 1: listando(head, "Novo", "Em Atendimento"); 
        break;
        case 2: listando(head, "Solucionado", NULL); 
        break;
        case 3: listando(head, "Fechado", NULL); 
        break;
        case 4: listando(head, "Todos", NULL); 
        break;
        default: printf("\nOpção Inválida\n"); 
        break;
    }
}
//Função p/ imprimir o chamado na tela
void listando(Chamados *head, char crit1[MAX_STATUS], char crit2[MAX_STATUS]){
    Chamados *atual=head->prox;
    int i=0;
    while(atual!=NULL){
        if(strcmp(crit1, "Todos")==0 || strcmp(crit1, atual->status)==0 || (crit2!=NULL && strcmp(crit2, atual->status)==0)){
            printf("\nChamado %d: %s\n\n%s\n\n",atual->id, atual->status, atual->titulo);
            i++;
        }
        atual=atual->prox;
    }
    if(i==0){
        printf("\nNenhum chamado encontrado para o filtro escolhido!\n");
    }
}
//Função P/ visualizar um chamado
void acessaChamado(Chamados *head){
    if(head->prox==NULL){
        printf("\nNenhum chamado existente\n");
        return;
    }
    int opcao;
    Chamados *atual = head->prox;
    printf("\nDigite o id do chamado ou digite 0 para visualizar os chamados:\nR: ");
    scanf(" %d", &opcao);
    if(opcao == 0){
        listar(head);
        return;
    }else{
        while(atual != NULL && atual->id != opcao){
            atual=atual->prox;
        }
        if(atual==NULL){
            printf("Erro, Não há Chamado com esse id\nAbaixo digite 2 para visualizar os chamados existentes\n");
            return;
        }else if(atual->id == opcao){
            printf("\nChamado %d:\nSituação: %s\n %s \n %s\n", atual->id, atual->status, atual->titulo, atual->descricao);
        }else printf("\nErro Desconhecido\n");
    }
    
}
//Função para adicionar solução ao chamado
void solucionando(Chamados *head){
    if(head->prox==NULL){
        printf("\nNenhum chamado existente\n");
        return;
    }
    int id;
    char solucao[MAX_DESCRICAO];
    char tecnico[20];
    Chamados *atual = head->prox;
    printf("\nDigite o id do chamado para adicionar solução:\nR: ");
    scanf(" %d", &id);
    while(atual != NULL && atual->id != id){
        atual = atual->prox;
    }
    if(atual == NULL){
        printf("Chamado não encontrado.\n");
        return;
    }
    if(strcmp(atual->status, "Fechado") == 0){
        printf("Chamado já está fechado.\n");
        return;
    }
    if(strcmp(atual->status, "Solucionado") == 0){
        printf("Chamado já tem uma solução.\n");
        return;
    }
    printf("\nDigite a solução:\n");
    scanf(" %255[^\n]", solucao);
    strcpy(atual->solucao, "\nSolução: ");
    strcat(atual->solucao, solucao);
    strcpy(atual->status, "Solucionado");
    printf("\nDigite seu nome: ");
    scanf(" %s", tecnico);
    strcpy(atual->tecnico, tecnico);
    printf("Solução adicionada ao chamado %d.\n", id);

}
//Função para liberar memória ao sair do progrmama
void liberamemoria(Chamados *head){
    printf("\nSaindo...\n");
    Chamados *atual=head->prox;
    Chamados *libera;
    while(atual!=NULL){
        libera=atual;
        atual=atual->prox;
        free(libera);
    }
    printf("\nObrigado por usar nossos sistemas\n");
}
