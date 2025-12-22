/******************************************************************************

sistema para gerenciar o histórico de operações 
realizadas por um usuário em uma calculadora científica. Cada operação realizada pelo usuário 
(como soma, subtração, etc.) deve ser armazenada em uma pilha para que seja possível desfazer 
as operações mais recentes. Sua tarefa é implementar essa funcionalidade de armazenamento e 
remoção utilizando a estrutura de pilha.
• Verificar pilha vazia: A função deve retornar verdadeiro se a pilha estiver vazia e falso caso 
contrário. 
• Operação push (inserção): Implementar uma função para inserir um elemento no topo da 
pilha. 
• Operação pop (remoção): Implementar uma função para remover o elemento do topo da 
pilha.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct calc {
    char oper[51];
    struct calc *prox;
} Calc;

//PROTÓTIPOS
//função para inserir/empilhar
void push(Calc *head);

//função para remover/desempilhar
void pop (Calc *head);

//função para mostrar histórico
void listar(Calc *head);

//verificar se a lista está vazia
int verifica(Calc *head);

//exclue todos os Nó's para liberar memória
void liberamemoria(Calc *head);

int main()
{
    Calc head = {0};
    int opcao;
    printf("\nBEM VINDO A CALCULADORA\n");
    do{
        printf("\n1-Nova Operação");
        printf("\n2-Desfazer");
        printf("\n3-Mostrar operações feitas");
        printf("\n0-Fechar Programa\nR: ");
        scanf(" %d", &opcao);
        switch(opcao){
            case 1: push(&head); break;
            
            case 2: pop(&head); break;
            
            case 3: listar(&head); break;
            
            case 0: liberamemoria(&head); break;
            
            default: printf("\nOpção Inválida\n"); break;
        }
        
    }while(opcao!=0);

    return 0;
}

//função para inserir/empilhar
void push(Calc *head){
    char operacao[51];
    Calc *novo=(Calc*)malloc(sizeof(Calc));
    if(novo==NULL){
        printf("\nErro de Memória\n");
        return;
    }
    novo->prox=head->prox;
    head->prox=novo;
    printf("\nDigite a operação desejada: ");
    scanf(" %s", operacao);
    strcpy(novo->oper, operacao);
    printf("\nOperação Gravada Com Sucesso\n");
}

//função para remover/desempilhar
void pop (Calc *head){
    if(verifica(head)){
        printf("\nErro, Não Exitem Operações a Serem Desfeitas\n");
    }else{
        Calc *atual=head->prox;
        head->prox=atual->prox;
        free(atual);
        printf("\nUltima Operação Removida do Histórico\n");
    }    
}

//função para mostrar histórico
void listar(Calc *head){
    if(verifica(head)){
        printf("\nNenhuma Operação a Ser Mostrada\n");
    }else{
        int i=0;
        Calc *atual=head->prox;
        printf("\nHISTÓRICO:\n");
        for(atual; atual!=NULL; atual=atual->prox){
            i++;
            printf("\n%d-%s", i, atual->oper);
        }
    printf("\n");
    }
}

//verificar se a lista está vazia
int verifica(Calc *head){
    if(head->prox==NULL){
        return 1;
    }else return 0;
}

//exclue todos os Nó's para liberar memória
void liberamemoria(Calc *head){
    Calc *atual=head->prox;
    Calc *libera;
    while(atual!=NULL){
        libera=atual;
        atual=atual->prox;
        free(libera);
    }
}
