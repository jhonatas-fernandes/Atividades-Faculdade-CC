#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

//estrutura de cada elemento na tabela
typedef struct elemento{
  char chave[50];
  char valor[50];
} Elemento;

Elemento *criarTabelaHash 
