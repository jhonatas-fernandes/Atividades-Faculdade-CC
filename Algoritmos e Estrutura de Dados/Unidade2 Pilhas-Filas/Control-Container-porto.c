/******************************************************************************

Atitidade proposta era criar um programa para gerenciamento de contâiner em portos
utilizando lista ligada com estrutura em forma de pilha seguindo o principio LIFO
Optei por fazer sem Cabeçalho

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct container{
    int id;
    char origem[41];
    char destino[41];
    char chegada[20];
    char saida[20];
    struct container *prox;
}Container;

//protótipos
void horaAtual(char *buffer, int tamanho);
void entrada(Container **head, int *id);
void saida(Container **head);
void proximo(Container **head);
void listac(Container **head);
void liberamemoria(Container **head);
int main(){
    Container *topo= NULL;
    int opcao;
    int i=0;
    printf("\n Gerenciador de Container\n");
    do{
        printf("\nDigite a opção desejada\n");
        printf("\n1-Dar entrada");
        printf("\n2-Dar saida");
        printf("\n3-Mostrar próximo container a sair");
        printf("\n4-Listar todos os Containers");
        printf("\n0-Sair\n");
        scanf(" %d", &opcao);
        printf("Voce digitou %d: ", opcao);

        switch(opcao){
            case 1: entrada(&topo, &i); break;
            
            case 2: saida(&topo); break;
            
            case 3: proximo(&topo); break;
            
            case 4: listac(&topo); break;
            
            case 0: liberamemoria(&topo); break;
            
            default: printf("\nopção inválida"); break;
        }
    }while(opcao != 0);

    return 0;
}
//Fução para salvar hora automaticamente
void horaAtual(char *buffer, int tamanho){
    //Pega o horário atual em formato de timestamp
    //timestamp //segundos desde 1º de janeiro de 1970.
    time_t agora = time(NULL); //time(NULL)=Hora atual do pc;
    
    //Converte o timestamp para data/hora local (struct tm) (horario humano)
    struct tm *info = localtime(&agora);
    
    //Converte a struct tm para texto formatado e salva no buffer
    strftime(buffer, tamanho, "%d/%m/%Y %H:%M:%S", info);
}
//Função para dar entrada de container
void entrada(Container **head, int *id){
    printf("Dando entrada ao Container:\n");
    char Hentrada[20];
    Container *novo = (Container*)malloc(sizeof(Container));
    novo->prox=*head;
    *head=novo;
    printf("\nde onde esse container está vindo?\n");
    scanf(" %40[^\n]", novo->origem);
    printf("\nPara onde ele vai?\n");
    scanf(" %40[^\n]", novo->destino);
    horaAtual(Hentrada, sizeof(Hentrada));
    strcpy(novo->chegada, Hentrada);
    (*id)++;
    novo->id= *id;
    printf("\nContainer id %d vindo de %s, indo para %s, entrado no porto as %s\n", novo->id, novo->origem, novo->destino, Hentrada);
    
}
//Função para dar saida e excluír container
void saida(Container **head){
    if(*head!=NULL){
        printf("Dando Saída a um Contâiner:\n");
        char Hsaida[20];
        Container *limpa=*head;
        *head=(*head)->prox;
        horaAtual(Hsaida, sizeof(Hsaida));
        strcpy(limpa->saida, Hsaida);
        printf("\nContainder id %d com destino a %s, saido do porto as %s\n", limpa->id, limpa->destino, limpa->saida);
        free(limpa);
    }else printf("Não existem Contâiner na Fila de Saída");    
}
//Função para mostrar o Próximo contâiner da Fila
void proximo(Container **head){
    if(*head!= NULL){ 
        printf("Próximo contâiner da fila é de id: %d, vindo de %s, com destino para %s\n", (*head)->id, (*head)->origem, (*head)->destino);
    }else printf("Sem Contâiner na Fila\n");
}
//Função para listar todos os contâiners
void listac(Container **head){
    printf("Listar Container\n");
    if(*head!=NULL){
        Container *atual = *head;
        printf("\nID    |    ORIGEM    |    DESTINO\n");
        while(atual!=NULL){
            printf("%d    |      %s      |    %s     \n", atual->id, atual->origem, atual->destino);
            atual=atual->prox;
        }
    }else printf("\nLISTA VAZIA!!\n");
}
//Função para Liberar Memória
void liberamemoria(Container **head){
    printf("\nFechando Aplicação...\n");
    if(*head!=NULL){    
        Container *atual = *head;
        Container *limpa;
        while(atual!=NULL){
            limpa=atual;
            atual=atual->prox;
            free(limpa);
        }
    }
    printf("Aplicação fechada, obrigado pela preferência");
}
