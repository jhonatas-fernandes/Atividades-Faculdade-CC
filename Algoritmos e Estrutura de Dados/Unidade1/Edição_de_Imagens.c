/******************************************************************************
Atividade solicitada era criar um programa que representava edição de imagens
com opção de desfazer e refazer edições. Primeiro contato com listas Duplamente Ligadas.
inicialmente começei fazer o código sem cabeçalho, apenas com ponteiros
mas ao final tive que "costurar" um cabeçalho representando iamgem sem edição
pois o programa não desfazia a primeira edição
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    char edicao[30];
    struct lista*next;
    struct lista *prev;
}Lista;

void geraEdicao(Lista **head, Lista **current, Lista **tail);   
void apagaDepois(Lista**current, Lista **tail);
void undo(Lista **current);
void redo(Lista **current);
int main()
{
    Lista *current=NULL;
    Lista *head=NULL;
    Lista *tail=NULL;
    int opcao;
    do{
        printf("\no que deseja fazer:\n1-adicionar imagem\n2-Editar\n3-Desfazer ultima edição\n4-Refazer ultima Edição\n0-Sair\n");
        scanf(" %d", &opcao);
        switch (opcao){
            case 1:
            if(head!=NULL){
                printf("\nERRO!Já exite imagem adicionada");
            }else{
            Lista *base=(Lista*)malloc(sizeof(Lista));
            head=base;
            current=base;
            tail=base;
            base->next=NULL;
            base->prev=NULL;
            }
            break;
            
            case 2:
            if(head==NULL){
                printf("nenhuma imagem adicionada para editar, por favor adicione imagem\n");
            }else{
            geraEdicao(&head, &current, &tail);//❗Regra de Ouro Função recebe Lista** → você passa &variavel  Fenção recebe Lista* → você passa variavel
            }
            break;
            
            case 3:
            undo(&current);
            break;
            
            case 4:
            redo(&current);
            break;
            
            case 0:
            printf("Saindo do Programa");
            break;
        }
    }while(opcao!=0);
    return 0;
}
//função para gerar novo nó
void geraEdicao(Lista **head, Lista **current, Lista **tail){
    int opcao=0;
    printf("\nQual a edição desejada?:\n");
    printf("1-contraste+\n");
    printf("2-contraste-\n");
    printf("3-brilho+\n");
    printf("4-brilho-\n");
    printf("5-recortar\n");
    scanf("%d", &opcao);
    //aloca memória para novo nó
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    if(novo==NULL){
        printf("Erro de Alocação de Memória");
    }
    
    //inicializa nó
    novo->next=NULL;
    novo->prev=NULL;
    
    //Insere Edição no novo nó
    switch(opcao){
        case 1 : strcpy(novo->edicao, "contraste+");break;
        case 2 : strcpy(novo->edicao, "contraste-");break;
        case 3 : strcpy(novo->edicao, "brilho+");break;
        case 4 : strcpy(novo->edicao, "brilho-");break;
        case 5 : strcpy(novo->edicao, "recortar");break;
    }
    
    
    //se existir nó depois de current apagar
    if((*current) != NULL && (*current)->next!=NULL){
        apagaDepois(current, tail);
    }
    
    //adicionando novo a lista e reajustando ponteiros
    novo->prev=*current;
    (*current)->next=novo;
    *current=novo;
    *tail=novo;
    
}  

//Função para apagar nós depois de current
void apagaDepois(Lista**current, Lista **tail){
    Lista *atual = (*current)->next;
    Lista*temp=NULL;
    while(atual!=NULL){
        temp = atual;
        atual=atual->next;
        free(temp);
    }
    (*current)->next=NULL;
    *tail=*current;
}

//Função para desfazer ultima edição(voltar current em um nó)
void undo(Lista **current){
    if(*current==NULL||(*current)->prev==NULL){
        printf("\nNão há alterações a serem desfeitas");
        return;
    }
    *current=(*current)->prev;
    printf("\n%s desfeito da edição", (*current)->next->edicao);
}

//Função para refazer ediçãodesfeita (current um nó a frente)
void redo(Lista **current){
    if(*current==NULL || (*current)->next==NULL){
        printf("\nnão exitem edições a serem recuperadas\n");
        return;
    }
    *current=(*current)->next;
    printf("\n%s aplicado novamente a imagem\n", (*current)->edicao);
}
