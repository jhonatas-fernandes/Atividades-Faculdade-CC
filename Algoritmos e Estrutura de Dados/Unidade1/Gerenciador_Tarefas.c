/**********************************************************************************
Atividade Pedia um sistema de listas ligadas para gerenciar uma lista de tarefas,
cada tarefa deve conter um id atribuido de forma automática;
Como bônus adicionei um histórico de tarefas já realizadas durante o dia.
Optei por fazer essa atividade utilizando-se de Nó's falsos (cabeçalho)
Desenvolvi essa atividade utilizando-se de conhecimentos obtidos no codigo de
gerenciador de pedidos, que aqui no github aparecerá depois desse.
**********************************************************************************/  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{ //cria estrutura do nó
  int cod;           //identificador da tarefa
  char txt [31];     //Descrição da tarefa
  struct node *prox; //ponterio para próximo nó
}Lista;          //palavra-chave (alias) para struc node


//Protótipos
void addTarefa(Lista *head, int i, const char *descricao);
void concluido(Lista *head, int i, Lista *historico);
void listaTarefas(Lista *head);
void listaHistorico(Lista *head);
void liberamemoria(Lista *tarefa, Lista *historico );
int main(){
    printf("\n\nBem vindo ao Gerenciador de Tarefas");
    Lista tarefa = {0};   //cria um nó "falso", sem conteúdo, cabeçalho da lista.
    Lista historico = {0};
    int opcao=0;
    int i = 0;           //servirá como id das tarefas
    int codigo;
    char descricao[31]; //guardará descrição até transferir para o txt da struct
    do{
        printf("\nO QUE DESEJA FAZER?\n");
        printf("\n1-Adicionar Nova Tarefa\n");
        printf("2-Concluir Tarefa\n");
        printf("3-Listar Tarefas Pendentes\n");
        printf("4-Histórico de tarefas Realizadas\n");
        printf("0-Fechar programa\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
            i++;  //gera de fórma automatica o id da tarefa
            printf("descreva a tarefa em até 30 caracteres\n");
            scanf( " %30[^\n]", descricao); //lê texto com espaços
            addTarefa(&tarefa, i, descricao); //chamada de função
            break;
            
            case 2:
            if(tarefa.prox==NULL){ //caso lista tarefa esteja vazia
                printf("\nNENHUMA TAREFA PENDENTE\n");
                break;
            }else{ //caso exista itens para mostrar
                printf("\nDigite o código identificador da tarefa a ser concluída\n");
                printf("Ou digite \"0\" para visualizar as tarefas\n");
                scanf("%d", &codigo);
                if(codigo==0){        //caso o usuário queira ver o id das tarefas
                    listaTarefas(&tarefa);
                }else{               //caso opcao não seja zero, chama função para concluir a tarefa
                    concluido(&tarefa, codigo, &historico);
                }    
            }
            break;
            
            case 3:
            if(tarefa.prox==NULL){ //caso a lista de tarefas esteja vazia
                printf("Sem tarefas pendentes, digite 1 para cadastrar nova tarefa\n");
            }else{
                listaTarefas(&tarefa);//se tiver itens chama função para mostra-los
            }
            break;
            
            case 4:
            if(historico.prox==NULL){ //caso não haja intens em histórico
                printf("sem histórico até o momento\n");
            }else{
                listaHistorico(&historico); //se houver itens, chama função para imprimi-los na tela
            }    
            break;
            
            case 0:
            printf("Fechando Aplicação....Aguarde\n");
            liberamemoria(&tarefa, &historico); //libera memoria das duas listas antes de fecharF
            printf("Aplicação encerrada.....obrigado pela preferência\n");
            break;
        }
    }while(opcao!=0);

    return 0;
}

//função para adicionar nó ao final da lista de tarefas
void addTarefa(Lista *head, int i, const char *descricao){
    Lista *atual = head;
    while(atual->prox!=NULL){ //enquanto esxistir nó em prox
        atual=atual->prox;    //ande um nó a frente
    }
    Lista *novo = (Lista*)malloc(sizeof(Lista));//aloca memória para novo nó
    novo->prox=NULL;
    novo->cod=i; //vincula o identificador a nova tarefa
    strcpy(novo->txt, descricao); 
    atual->prox=novo; //adiciona novo nó em ultimo na lista
    printf("\ntarefa \"%s\" criada, código N° %d\n", novo->txt, novo->cod);
}

//Função para remover tarefa concluida de lista e adiciona-lá ao Histórico
void concluido(Lista *head, int i, Lista *historico){
    Lista *atual=head;
    Lista *anterior;
    while(atual!=NULL && atual->cod!=i){
        anterior=atual;
        atual=atual->prox;
    }
    if(atual==NULL){
        printf("\ntarefa não encontrada, por favor verifique o id digitado\n");
        return;
        
    }
    if(atual!=NULL && atual->cod==i){
        anterior->prox=atual->prox;//nó anterior deixa de apontar para atual e aponta para o proximo
        atual->prox=historico->prox;//ponteiro prox de atual aponta para onde historico->prox aponta
        historico->prox=atual;//historico->prox passa a apontar para atual, removendo-o das tarefas e 
                              //inserindo como primeiro na lista de historico
    }
    printf("\nTarefa \"%s\" concluída com sucesso!\n", atual->txt);
}

//função para imprimir na tela lista de tarefas em aberto
void listaTarefas(Lista *head){
    Lista *atual=head->prox;
    int i=0;
    while(atual!=NULL){
        i++;
        printf("\n%d-Tarefa: \"%s\" - código: %d", i, atual->txt, atual->cod);
        atual=atual->prox;
    }
}

//função para imprimir na tela histórico de tarefas concluidas
void listaHistorico(Lista *head){
    int i=0;
    Lista *atual=head->prox;
    while(atual!=NULL){
        i++;
        printf("\n%d-Tarefa \"%s\" - Código: %d Concluida com Sucesso!!", i, atual->txt, atual->cod);
        atual=atual->prox;
    }
}

//Função para liberar memória ao fechar o programa
void liberamemoria(Lista *tarefa, Lista *historico ){
    Lista *temp;
    Lista *atual=tarefa->prox;
    while(atual != NULL){
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    atual=historico->prox;
    while(atual != NULL){
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
