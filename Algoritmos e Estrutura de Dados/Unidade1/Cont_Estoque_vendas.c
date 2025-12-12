/**********************************************************************************
A proposta da atividade era fazer um sistema de controle de estoque para uma loja de autopeças
onde a cada alteração no estoque aparecesse em tempo real na tela um relatório completo do estoque
Esse sistema tinha que ter opção de comprar, vender e cadastrar produto, bem como consultar 
produto individual e gerar o relátorio de forma manual. Optei por fazer sem cabeçalhos, utilizando-se mais de ponteiros
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma execution_character_set("utf-8")
//Estrutura do Nó (produto)
typedef struct node {
	int cod;
	char produto[31];
	int qnt;
	struct node *prox;
} Estoque;
//prot´totipos
void comprando(Estoque **head);
void vendendo(Estoque **head);
void estRel(Estoque **head);
int cadastro(Estoque **head, Estoque **tail, int i);
void consulta(Estoque **head);
void liberamemoria(Estoque**head);
int main()
{
	Estoque *head = NULL; //ponteiro cabeça
	Estoque *tail = NULL;//ponteiro final da lista
	int vendas = 0;
	int opcao=0;
	int i=999;
	printf("\nBEM VINDO AO SISTEMA DE VENDAS");
	do {
		printf("\nSelecione uma opção");
		printf("\n1-Comprar");
		printf("\n2-Vender");
		printf("\n3-Atualizar Relatório de Estoque");
		printf("\n4-Cadastrar Novo Produto");
		printf("\n5-Consultar Produto");
		printf("\n0-Sair\n");
		scanf(" %d", &opcao);
		switch(opcao) {
		case 1:comprando(&head);break;

		case 2:vendendo(&head);break;

		case 3:estRel(&head);break;

		case 4:i++;cadastro(&head, &tail, i);break;

		case 5:consulta(&head);break;

		case 0:
			printf("\nFechando aplicação...");
			liberamemoria(&head);break;

		}
	} while(opcao!=0);
	return 0;
}

//Função para comprar produto
void comprando(Estoque **head) {
	int id=0;
	Estoque *atual= *head;
	if(atual==NULL) {
		printf("\nErro, não existem produtos cadastrados\n");
		return;
	}
	printf("\nDigite o código do produto que deseja comprar: ");
	scanf("%d", &id);

	while(atual!=NULL && atual->cod != id) {
		atual= atual->prox;
	}
	if(atual==NULL) {
		printf("\nproduto não encontrado\n");
		return;
	}
	int quantia;
	if(atual!=NULL && atual->cod==id) {
		printf("\nDigite a quantidade de itens comprados: ");
		scanf("%d", &quantia);
		atual->qnt+=quantia;
		printf("\n%d iten(s) adicionado(s) ao produto %s, novo estoque: %d ", quantia, atual->produto, atual->qnt);
		printf("\nNOVA COMPRA DE MERCADORIA REALIZADA= produto %s\n novo relatório de estoque:", atual->produto);
		estRel(head);
	}
}
//Função para vender produto
void vendendo(Estoque **head) {
	Estoque *atual=*head;
	int codigo = 0;
	int quantia = 0;
	if(atual==NULL) {                       //Se tentar vender quanto não há produtos cadastrados
		printf("\nAtenção!!! Nenhum produto cadastrado para venda, pressione 4 para cadastrar\n");
		return;
	}
	printf("\nDigite o Código do produto a ser vendido");
	scanf("%d", &codigo);
	while(atual!=NULL && atual->cod != codigo) {
		atual=atual->prox;
	}
	if(atual==NULL) {
		printf("\nProduto nC#o cadastrado, pressione 4 para cadastrar");
		return;
	}
	if(atual!=NULL && atual->cod == codigo) {
		printf("\nQuantos produtos foram vendidos?");
		scanf("%d", &quantia);
		atual->qnt -= quantia;
		printf("\nNovo estoque do produto %s, codigo %d: %d itens", atual->produto, atual->cod, atual->qnt);
		printf("\nNOVA VENDA REALIZADA= produto %s\n novo relatC3rio de estoque:", atual->produto);
		estRel(head);
	}
}
//Funçaõ para o relatório atualizado de estoque
void estRel(Estoque **head) {
	Estoque *atual=*head;
	if(atual==NULL) {
		printf("\nErro, Nenhum produto cadastrado\n");
		return;
	}
	while(atual!=NULL) {
		printf("\n%s, Código %d, estoque atual: %d\n", atual->produto, atual->cod, atual->qnt);
		atual=atual->prox;
	}
}
//Função para Cadastrar um novo Produto
int cadastro(Estoque **head, Estoque **tail, int i){
  //adicionando limite de produtos cadastrados
	if(i>9999) {
		printf("\nLimite máximo de produtos cadastrados");
		i--;
		return i;
	}
	Estoque *novo = (Estoque*)malloc(sizeof(Estoque));
	novo->prox=NULL;
	novo->cod=i;      //Define o código do produto de forma automática
	printf("\ndigite o nome do produto:");
	scanf(" %30[^\n]", novo->produto);
	printf("\nQual o estoque atual desse produto: ");
	scanf(" %d", &novo->qnt);
	if(*head==NULL) {
		*head=novo;
	}else (*tail)->prox=novo;  //adicionando nó ao final da lista
	
	*tail=novo;
	printf("\n%s cadastrado com sucesso sob o código %d e estoque %d\n", novo->produto, novo->cod, novo->qnt);
	printf("\nNOVA ALTERAÇÃO NO RELATÓRIO...Novo produto cadastrado, codigo: %d\n", novo->cod);
	estRel(head);   //chamando função para mostrar estoque atualizado
}
//Função para consultar produto de forma individual
void consulta(Estoque **head) {
	Estoque *atual=*head;
	int codigo = 0;
	if(atual==NULL) {
		printf("\nAtenção!!! Nenhum produto cadastrado, pressione 4 para cadastrar\n");
		return;
	}
	printf("\nDigite o código do produto a consultar: ");
	scanf("%d", &codigo);
	while(atual!=NULL && atual->cod != codigo) {
		atual=atual->prox;
	}
	if(atual==NULL) {
		printf("\nProduto não cadastrado, pressione 4 para cadastrar");
		return;
	}
	if(atual!=NULL &&atual->cod == codigo) {
		printf("\nExistem %d unidade(s) do produto %s, sob o codigo %d\n", atual->qnt, atual->produto, atual->cod);
	}
}
//função para liberar memória ao fechar o programa
void liberamemoria(Estoque**head) {
	Estoque * temp;
	while(*head!=NULL) {
		temp = *head;
		*head = (*head)->prox;
		free(temp);
	}
}
