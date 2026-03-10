/******************************************************************************

Criar Fila para controle de um lava-rápido, onde deve ter controle de entrada
na fila(agenda cheia), inserção e remoção de elementos e liberação da agenda
Nesta atividade irei trabalhar tanto com ponteiros quanto com cabeçalhos para
fins de aprendizado

*******************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

//Estrutura de Nó de carro na fila
typedef struct carro{
    char placa[8];
    char cor[10];
    char atend[20];
    char saida[20];
    char status[11];
    struct carro *prox;
}Carro;

//protótipos
void agendando(Carro *head, int *agenda, char turno[6]);
void proxLav(Carro *head, Carro **current);
void horaAtual(char *buffer, int tamanho);
void liberamemoria(Carro *head);
void liberaagenda(Carro *head, Carro **current, char turno[6]);
void fimLav(Carro **current);
void listar(Carro *head, char turn[7]);
void consulta(Carro *head, char turn[6]);

int main(){   
    printf("\nSISTEMA LAVA-RÁPIDO INICIALIZADO, BEM VINDO!\n");
    //inicializando sentinelas e pnteiro current
    Carro manha = {0};
    Carro tarde = {0};
    Carro *current=NULL;
    //controle de agenda
    int agenda_m = 0;
    int agenda_t = 0;
    int turno;
    int opcao;
    do{
        printf("\nQual turno deseja Iniciar?\n1-Manhã\n2-tarde\n0-Sair\nR: ");
        scanf(" %d", &turno);
        //fechar sistema
        if(turno==0){
            printf("\nFechando Aplicação, aguarde\n");
            liberamemoria(&manha);
            liberamemoria(&tarde);
            printf("Agradeçemos a Prefencia\n\nSistema finalizado!");
            break;
            
        //trabalhar com turno especifico escolhido
        }else if(turno==1 || turno==2){ //trabalhar com turno especifico escolhido
            
            //aponta o current para lista referente ao turno escolhido
            if(turno==1){
                current=&manha;
            }else current=&tarde;
                
            do{
                printf("\nDigite a opção desejada:\n");
                printf("1-Agendar Carro\n");
                printf("2-Iniciar Próxima Lavagem\n");
                printf("3-Finalizar Lavagem\n");
                printf("4-Consultar Atendimento\n");
                printf("5-Mostrar Agenda\n");
                printf("6-Liberar Agenda (Horários já Atendidos)\n");
                printf("0-Encerrar Turno\n");
                scanf(" %d", &opcao);
                //trabalhando com opções do menu
                switch(opcao){
                    //agendamentos
                    case 1: 
                    int agenda;
                    printf("\nAtenção, só é possível agendar para data de hoje, não trabalhamos com agendamentos futuros\n");
                    printf("\nPara qual turno deseja agendar?\n1-Manhã\n2-Tarde\nR: ");
                    scanf("%d", &agenda);
                    if(agenda==1){
                        agendando(&manha, &agenda_m, "Manhã"); 
                        break;
                    }else{
                        agendando(&tarde, &agenda_t, "tarde"); 
                        break;
                    }
                    //ir para próxima lavagem
                    case 2: 
                    if(turno==1){
                        proxLav(&manha, &current);
                    }else{
                        proxLav(&tarde, &current);
                    }
                    break;
                    
                    case 3: fimLav(&current); break;
                    
                    case 4: 
                    printf("\nVocê só pode consultar seu carro se estiver agendado para o turno atual\n");
                    if(turno==1){
                        consulta(&manha, "Manhã");
                    }else consulta(&tarde, "tarde");
                    break;
                    
                    case 5: 
                    listar(&manha, "Manhã:");
                    listar(&tarde, "Tarde:");
                    break;
                    case 6:
                    if(turno==1){
                        liberaagenda(&manha, &current, "Manhã");
                    }else liberaagenda(&tarde, &current, "Tarde");
                    break;
                    
                    case 0: break;
                    default: printf("\nOpção Inválida");
                }
            }while(opcao!=0);
        //nenhum turno escolhido
        }else printf("\nOPÇÃO INVÁLIDA!!\n");
    }while(1);
    return 0;
}

//Função para entrar na fila
void agendando(Carro *head, int *agenda, char turno[6]){
    //caso agenda esteja cheia
    if(*agenda >= 10){
        printf("\nAgenda cheia para %s, por favor tente outro turno ou aguarde outra data\n", turno);
        return;
    }
    char hora[20];
    
    //aloca memória para novo carro agendando
    Carro *novo= (Carro*)malloc(sizeof(Carro));
    //confere erro de alocamento de memória
    if(novo==NULL){
        printf("\n!ERRO DE MEMÓRIA\n");
        return;
    }
    novo->prox=NULL;
    
    //recebendo informações do carro a entrar na fila
    printf("\nDigite a cor do carro sem espaços\n");
    scanf(" %s", novo->cor);
    printf("\nDigite a Placa do Carro sem Espaços\n");
    scanf(" %s", novo->placa);
    strcpy(novo->status, "Aguardando");
   
    Carro *atual=head;
    while(atual->prox != NULL){
        atual=atual->prox;
    }
    atual->prox=novo;
    (*agenda)++;
    printf("\nCarro agendado, N_%d na fila", *agenda);
}

//Função para mover o currente ao proximo nó (proxima lavagem)
void proxLav(Carro *head, Carro **current){
    //Caso a Lavagem atual não esteja finalizada
    if(strcmp((*current)->status, "Em Lavagem")==0){
        printf("\nJá Existe um carro em lavagem, Finalize o mesmo antes de seguir para o próximo\n");
        return;
    }
    if((*current)->prox==NULL){
        printf("\nUltimo carro da lista, Não existem mais carros serem lavados\nDigite 6 para aceitar mais carros neste turno\n");
        return;
    }else if((*current)->prox != NULL){
        char hora[20];
        *current= (*current)->prox;
        strcpy((*current)->status, "Em Lavagem");
        horaAtual(hora, sizeof(hora));
        strcpy((*current)->atend, hora);
        printf("\nCarro Placa %s Em Lavagem, Iniciada as %s", (*current)->placa, (*current)->atend);
    }
}

//Função para mostrar hora atual
void horaAtual(char *buffer, int tamanho){
    //pega hora atual em formato timestap (segundos desde 01/01/1970)
    //time=NULL hora atual da maquina
    time_t agora = time(NULL);
    
    //converte timestep para struct_tm (horario humano)
    struct tm *info = localtime(&agora);

    //converte struct tm para texto formatado
    strftime(buffer, tamanho, "%d/%m/%Y %H/%M/%S", info);
}

//função para liberar a memória ao fechar o programa
void liberamemoria(Carro *head){
    Carro *atual = head->prox;
    Carro *libera;
    while(atual != NULL){
        libera = atual;
        atual=atual->prox;
        free(libera);
    }    
   
}

//Fução para limpar nó's anteriores a current para liberar horarios
void liberaagenda(Carro *head, Carro **current, char turno[6]){
    //se não tiver nada na agenda;
    if(head-> prox == NULL){
        printf("\nNADA A LIBERAR, Todos os horários Livres\n");
        return;
    }
    int i=0;
    Carro *atual=head->prox; //head->prox pois cabeçalho não pode entrar no while
    Carro *libera;
    //liberando memórias apenas de carros prontos
    while(atual != NULL && strcmp(atual->status, "Pronto")==0){ //atual != null para nao dar erro de memoria na ultima volta do laço
        i++;
        libera=atual;
        atual=atual->prox;
        free(libera);
    }
    if(i>=10){
        printf("\ntodos os horários liberados no horário da %s\n", turno);
    }else if(i==0){
        printf("\nNão exitem carros a Liberar, todos em atenimento ou aguardando");
    }else printf("\n%d horários liberados no horário da %s\n", i, turno);
    
    head->prox=atual; //apontando cabeçalho ao proximo no que sobrou na lista
    
}

//Função para definir a lavagem atual como pronta, sem avançar para a proxima
void fimLav(Carro **current){
    if(*current==NULL){
        printf("\nNenhum carro em Lavagem no momento!\n");
        return;
    }
    if(strcmp((*current)->status, "Pronto")==0){
        printf("\nLavagem já finalizada anteriormente, por favor avançe para o próximo carro selecionando opção 2\n");
        return;
    }
    char hora[20];
    strcpy((*current)->status, "Pronto");
    horaAtual(hora, 20);
    strcpy((*current)->saida, hora);
    printf("\nLavagem do carro, placa %s, Finalizada as %s\n", (*current)->placa, (*current)->saida);
}

//Função para listar na tela todos os carros agendados
void listar(Carro *head, char turn[7]){
    Carro *atual = head->prox;
    if(atual==NULL){
        printf("\n\nLista Vazia para %s\n", turn);
        return;
    }
    printf("\n\n%s\n", turn);
    int i=0;
    while(atual!=NULL){
        i++;
        printf("\n%d- Carro %s, Placa:%s", i, atual-> cor, atual->placa);
        atual=atual->prox;
    }
}

//Função para consultar status do carro agendado
void consulta(Carro *head, char turn[6]){
    char id[8];
    printf("\nDigite a placa de seu carro (minusculo e sem traços):");
    scanf(" %7[^\n]", id);
    Carro *atual=head->prox;
    if(atual==NULL){
        printf("\nERRO, LISTA VAZIA PARA ESTE TURNO DA %s!!\n", turn);
        return;
    }
    while(atual!=NULL && strcmp(atual->placa, id)!=0){
        atual=atual->prox;
    }
    if(atual==NULL){
        printf("\nPlaca não encontrada neste turno da %s\n", turn);
        return;
    }
    if(strcmp(atual->placa, id)==0){
        printf("\nCarro %s, placa %s, está %s\n", atual->cor, atual->placa, atual->status);
    }
}
