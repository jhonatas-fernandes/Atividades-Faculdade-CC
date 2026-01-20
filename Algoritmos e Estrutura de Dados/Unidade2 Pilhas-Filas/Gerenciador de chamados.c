
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
void atribuindo(Chamados *head, const char *tecnico);
void fechandoChamado(Chamados *head);

int main()
{
    setlocale(LC_ALL, ".UTF-8");
    char User[20];
    Chamados lista = {0};
    Chamados *Tail=&lista;
    printf("\nPrograma Gerenciador de Chamados\n");
    printf("\nDigite Seu Nome\n");
    scanf(" %s", User);
    int i = 999;
    int opcao;
    do{
        printf("\nEscolha a opção desejada:\n");
        printf("1-Novo Chamado\n");
        printf("2-Listar Chamados\n");
        printf("3-Acessar chamado\n");
        printf("4-Adicionar Solução\n");
        printf("5-Atribuir Chamado\n");
        printf("6-Fechar Chamado\n");
        printf("0-Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1: abreChamado(&lista, &Tail, &i); break;

            case 2: listar(&lista); break;

            case 3: acessaChamado(&lista); break;

            case 4: solucionando(&lista); break;

            case 5: atribuindo(&lista, User); break;

            case 6: fechandoChamado(&lista); break;

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
    Chamados *novo =(Chamados*)calloc(1, sizeof(Chamados));
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
    if(strcmp(atual->tecnico, "")==0){
        printf("Digite seu nome (sem espaço):\n");
        scanf(" %s", tecnico);
        strcpy(atual->tecnico, tecnico);
    }    
    printf("Solução adicionada ao chamado %d pelo técnico %s.\n", id, atual->tecnico);    
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
//Função P/ atribuir técnico ao chamado
void atribuindo(Chamados *head, const char *tecnico){
    if(head->prox == NULL){
        printf("\nERRO! Ainda não existem chamados\n");
        return;
    }
    Chamados *atual=head->prox;
    int id;
    int op;
    const char opcao;
    char user2[20];
    printf("\nDigite o ID do chamado\n");
    scanf(" %d", &id);
    while(atual!=NULL && atual->id!=id){
        atual=atual->prox;
    }
    if(atual==NULL){
        printf("\nChamado Não encontrado, Digite 2 para visualizar os chamados\n");
        return;
    }
    if(strcmp(atual->status, "Novo") != 0 && strcmp(atual->status, "Em Atendimento")!=0){
        printf("\nJá existe uma solução para este chamado, Deseja continuar mesmo assim? (S/N)\n");
        scanf(" %c", &opcao);
        if(opcao=='N' || opcao=='n'){
            printf("\nOperação cancelada\n");
            return;
        }
    }
    if(atual->id==id){
        printf("\n1-Associar a mim mesmo");
        printf("\n2-Associar a outro técnico");
        scanf(" %d", &op);
        switch(op){
            case 1:
            strcpy(atual->tecnico,tecnico);
            break;

            case 2:
            printf("digite o nome do técnico, sem espaço");
            scanf(" %s", user2);
            strcpy(atual->tecnico,user2);
            break;

            default: printf("\nopção inválida\n");
        }
        strcpy(atual->status, "Em Atendimento");
        printf("\nChamado %d %s pelo técnico %s\n", id, atual->titulo, atual->tecnico);
    }
}
//Função para mudar o status do chamado para fechado
void fechandoChamado(Chamados *head){
    if(head->prox==NULL){
        printf("\nNenhum chamado existente\n");
        return;
    }
    int id;
    Chamados *atual = head->prox;
    printf("\nDigite o id do chamado para fechar:\nR: ");
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
    strcpy(atual->status, "Fechado");
    printf("Chamado %d fechado com sucesso.\n", id);    
}
//fim do programa