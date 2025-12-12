/******************************************************************************

Atividade solicitava um programa de listas ligadas para gerencias pedidos em
uma lanchonete, onde o programa deveria receber pedido, alterar status, definir
um id para cada pedido e, após finalizar, adicionar o pedido a um histórico
que deveria aparecer na tela ao ser solicitado. Neste caso quis testar fazer
com duas estruturas diferentes, sem protótipos e com cabeçalho.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//estrutura de um pedido
typedef struct pedidos{
    char status[20];
    char nome[20];
    int qnt;
    int npedido;
    struct pedidos *prox;
}Pedidos;
//estrutura do pedido no histórico
typedef struct historico{
    char nome[20];
    int qnt;
    int npedido;
    struct historico*prox;
}Historico;
//função para fazer um pedido
void pnovo(Pedidos* fila, int i){
    Pedidos *novo = (Pedidos*)malloc(sizeof(Pedidos));
    printf("\ndigite o nome do lanche: ");
    scanf(" %19[^\n]", novo->nome);
    printf("\nquantos vai querer?");
    scanf(" %d", &novo->qnt);
   novo->prox=NULL;
   novo->npedido=i;           //atribui id de forma automatica
   strcpy(novo->status, "Novo"); //atribui o status de novo pedido
   Pedidos *atual=fila;
   while(atual->prox!=NULL){
       atual=atual->prox;
   }
    atual->prox = novo;
 
}
//finaliza pedido e o adiciona ao histórico
void finalizaPedido(Pedidos*fila, Historico*history, int codigo){
    Pedidos*atual=fila;
    Pedidos*anterior=NULL;
    while(atual != NULL && atual->npedido != codigo){  //procura pedido na lista
        anterior=atual;
        atual=atual->prox;
    }
    if(atual!=NULL&&atual->npedido==codigo){
        Historico *novo=(Historico*)malloc(sizeof(Historico)); //aloca memória para histórico
        strcpy(novo->nome, atual->nome); //transferindo informaçoes de Pedidos para Histórico
        novo->qnt=atual->qnt;
        novo->npedido=atual->npedido;
        anterior->prox=atual->prox;
        free(atual);               //libera memória de Pedidos
        novo->prox=history->prox;  //adiciona no começo da lista Histórico
        history->prox=novo;
    }else printf("\nPedido não encontrado\n");    
    
}
//Troca status do pedido
void statusAtual(Pedidos* fila, Historico* history){
    int codigo;
    printf("\ndigite o código do pedido que deseja atualizar: ");
    scanf(" %d", &codigo);
    printf("\nProcurando pedido, Aguarde...");
    Pedidos *atual = fila;
    while(atual != NULL&&atual->npedido!=codigo){
        atual=atual->prox;
    }
    if(atual!= NULL && atual->npedido == codigo){
        int opcao = 0;
        printf("qual o novo status desse pedido?\n1-Novo\n2-Em Atendimento\n3-saiu para entrega\n4-Enregue(Finalizado)\n");
        scanf(" %d", &opcao);
        switch(opcao){
            case 1:
            strcpy(atual->status, "Novo");
            break;
            
            case 2:
            strcpy(atual->status, "Em Atendimento");
            break;
            
            case 3:
            strcpy(atual->status, "Saiu para Entrega");
            break;
            
            case 4:
            strcpy(atual->status, "Entregue");
            finalizaPedido(fila, history, codigo);
            break;
        }
    } else printf("\n Pedido não encontrado\n");   
}
//Mostra pedidos na tela e seus Status respectivos
void listaPedido(Pedidos * fila){
    Pedidos*atual=fila->prox;
    while(atual!=NULL){
        printf("\n PEDIDO Nº%d\n%s\n%d Unidade(s)\n Status Atual: %s \n", atual->npedido, atual->nome, atual->qnt, atual->status);
        atual=atual->prox;
    }
}
//Lista o histórico de pedidos na tela
void listaH(Historico* history){
    Historico* atual=history->prox;
    while(atual!=NULL){
        printf("\nPEDIDO Nº%d\n%s\n%d Unidade(s)\n", atual->npedido, atual->nome, atual->qnt);
        atual=atual->prox;
    }
}
int main()
{
    Pedidos Fila = {0};
    Historico Historic = {0};
    int i=0;
    int opcao;
    do{
        
        printf("\no que deseja fazer?\n1-Novo Pedido\n2-Alterar Status\n3-Finalizar pedido\n4-Lista Pedidos\n5-Historico\n0-Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1 :
            i++;
            pnovo(&Fila, i); 
            printf("\nSeu pedido ficará pronto em Breve, Obrigado!!!\n");
            break;
            
            case 2:
            statusAtual(&Fila, &Historic);
            break;
            
            case 3:
            int codigo;
            printf("\nDigite o número do pedido\n");
            scanf(" %d", &codigo);
            finalizaPedido(&Fila, &Historic, codigo);
            break;
            
            case 4 :
            listaPedido(&Fila);
            break;
            
            case 5:
            listaH(&Historic);
            break;
        }
    }while(opcao!=0);
    

    return 0;
}
