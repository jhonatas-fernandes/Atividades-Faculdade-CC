/*******************************************************************************************
Minha primeira Atividade da faculdade e primeiro contato com C, Então sim tem muito a melhorar, dá pra refatorar,
diminuir códigos com funções, implementar novas funções como libera memória entre outras.
Atividade pedia para criar com lista Ligada um controle de estoque que gerasse um relátório
com produtos que estão abaixo do estoque mínimo 
em alguma das duas lojas, e imprimisse esses produtos na tela
***********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
//estrutura de um produto
struct estoque{
    int loj;
    char produto[20];
    int codigo;
    int qnt;
    int estMinimo;
    struct estoque *prox;
};
typedef struct estoque Estoque;

//protótipos
void cadastraItem(Estoque* loja1, Estoque* loja2);
void produtDel(Estoque* loja1, Estoque* loja2);
void deletando(Estoque** loja, int cod, int nloja);
void geraRelatorio(Estoque* loja, int nloja, Estoque* relEstoque);
void imprimeRel(Estoque* estbaixo);
int main()
{
  //Cabeçalhos, Nó's sem conteúdos
    Estoque loja1 = {0}; 
    Estoque loja2 = {0};
    Estoque relEstoque = {0};
  
    int opcao;
    do{
        printf("o que deseja fazer?\n1-cadastrar novo produto\n2-Excluir Produto\n3-Relatório de Estoque Baixo\n0-Sair ");
        scanf(" %d", &opcao);
        switch(opcao){
            case 1:
            cadastraItem(&loja1, &loja2);
            break;
            
            case 2:
            produtDel(&loja1, &loja2);
            break;
            
            case 3:
            geraRelatorio(&loja1, 1, &relEstoque);
            geraRelatorio(&loja2, 2, &relEstoque);
            imprimeRel(&relEstoque);
            break;
            
            case 0:
            printf("Fechando aplicação...");
            break;
            
            default:
            printf("\nOpção inválida!!!\n");
            break;
        }
        
    }while(opcao != 0);
    return 0;
}

//Exclui produto apontado pela função abaixo
void deletando(Estoque** loja, int cod, int nloja){
    Estoque *atual=*loja;
    Estoque *anterior=NULL;
    while(atual!= NULL && atual->codigo!=cod){
        anterior = atual;
        atual=atual->prox;
    }
    if(atual!=NULL){
        anterior->prox = atual->prox;
        printf("\nExcluíndo produto %s da loja %d\n", atual->produto, nloja);
        free(atual);    
    }else printf("\nProduto não encontrado na loja %d \n", nloja);   
    
}

//Função onde seleciona a loja e o produto que se deseja excluír
//está sem verificação de lista vazia
void produtDel(Estoque* loja1, Estoque* loja2){
    int nloja;
    int cod;
    printf("em qual loja o item será excluído? (1-2 ou 3-Ambas: )");
    scanf(" %d", &nloja);
    printf("Digite o codigo do produto que deseja excluir: ");
    scanf(" %d", &cod);
    switch(nloja){
        case 1:{
            deletando(&loja1, cod, nloja);
            break;
        }
        case 2:{
            deletando(&loja2, cod, nloja);
            break;
        }
        case 3 :{
            deletando(&loja1, cod, 1);
            deletando(&loja2, cod, 2);
            break;
        }
        default:
            printf("\nOpção inválida!!!\n");
            break;
    }
    
}

//Função para cadastrar novo item (sim, dava pra transformar esses while em função)
void cadastraItem(Estoque* loja1, Estoque* loja2){
    //aloca memória para novo produto cadastrado
    Estoque *novo = (Estoque*)malloc(sizeof(Estoque));
    novo->prox=NULL;
    int nloja;
    printf("\nPara qual loja o item será cadastrado? (1-2, 3-AMBAS):");
    scanf(" %d", &nloja);
        printf("\ndigite o nome do produto: ");
        scanf(" %19[^\n]", novo->produto);     //%19 limita a 19 caracteres e o resto aceita palavras com espaço, diferente de %s
        printf("\ndigite o codigo do poduto: ");
        scanf(" %d", &novo->codigo);
        printf("\nqual o estoque minimo para cada loja: ");
        scanf(" %d",&novo->estMinimo);
        printf("\nqual o estoque atual deste produto? ");
        scanf(" %d", &novo->qnt);
        switch(nloja){
            case 1:{
            Estoque *atual=loja1;
            while(atual->prox!=NULL){
            atual = atual->prox;}
            atual->prox=novo;
            novo->prox=NULL;
            break;
            }
            case 2:{
            Estoque *atual=loja2;
            while(atual->prox!=NULL){
            atual = atual->prox;}
            atual->prox=novo;
            novo->prox=NULL;
            break;
            }
            //passa todas as informações de novo para novo1 e novo2, depois libera memoria de novo
            case 3:{
            Estoque *novo1 = (Estoque*)malloc(sizeof(Estoque));
            Estoque *novo2 = (Estoque*)malloc(sizeof(Estoque));
            *novo1 = *novo;
            *novo2= *novo;
            free(novo);
                //cadastrando produto na loja1
            Estoque *atual=loja1;
            while(atual->prox!=NULL){
            atual = atual->prox;}
            atual->prox=novo1;
            novo1->prox=NULL;
                //cadastrando produto na loja2
            Estoque *copia=loja2;
            while(copia->prox!=NULL){
            copia = copia->prox;}
            copia->prox=novo2;
            novo2->prox=NULL;
            break;}
            
            default:
            printf("\nOpção inválida!!!\n");
            break;
        }
}
//gera o relatorio percorrendo toda lista de cada loja e salvando em relEstoque
void geraRelatorio(Estoque* loja, int nloja, Estoque* relEstoque){
    Estoque *lojaAtual = loja->prox;
    while(lojaAtual != NULL){
        if(lojaAtual->qnt<lojaAtual->estMinimo){
            Estoque* novo=(Estoque*)malloc(sizeof(Estoque));
            *novo=*lojaAtual;
            novo->loj=nloja;
            novo->prox=NULL;
            Estoque* atual = relEstoque;
            while(atual->prox != NULL){
               atual=atual->prox;
            }
           atual->prox=novo;
        }
        lojaAtual= lojaAtual->prox;
    }
    
    
    
}

//imprime na tela o conteúdo de relEstoque e limpa o relatório
//o correto seria produto sair do relatorio somente após ajustar estoque, mas
//atividade pedia assim para trabalhar o free()
void imprimeRel(Estoque* estbaixo){
    Estoque* atual = estbaixo->prox;
    Estoque* temp;
    int i=0;
    while(atual!= NULL){
        printf("loja: %d\nProduto: %s\nEstoque atual: %d\n Estoque minimo: %d\n REALIZAR PEDIDO\n", atual->loj, atual->produto, atual->qnt, atual->estMinimo);
        temp=atual;
        i++ ;
        free(atual);
        atual=temp->prox;
    }
    printf("Existem %d produtos com estoque abaixo do mínimo!!\n", i);
    
}
