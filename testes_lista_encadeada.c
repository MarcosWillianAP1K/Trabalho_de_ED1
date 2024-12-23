#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
// #include "BIBLIOTECAS/Struct_info.h"


int main()
{
    Lista_encadeada *lista = NULL;

    INFO *teste1 = escrever_dados();
    printf("\n");
    INFO *teste2 = escrever_dados();
    printf("\n");


    adicionar_elemento_encadeada(&lista, teste1);

    adicionar_elemento_encadeada(&lista, teste2);


    printf("ID: %d\n", lista->informacoes->ID);
    printf("Nome: %s\n", lista->informacoes->nome);
    printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    printf("Data: %02d/%02d/%04d\n", lista->informacoes->dia, lista->informacoes->mes, lista->informacoes->ano);
    printf("Hora: %02d:%02d\n", lista->informacoes->hora, lista->informacoes->minuto);
    
    
    lista = lista->proximo;

    printf("\nID: %d\n", lista->informacoes->ID);
    printf("Nome: %s\n", lista->informacoes->nome);
    printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    printf("Data: %02d/%02d/%04d\n", lista->informacoes->dia, lista->informacoes->mes, lista->informacoes->ano);
    printf("Hora: %02d:%02d\n", lista->informacoes->hora, lista->informacoes->minuto);


    liberar_memoria_encadeada(&lista);

    

    return 0;
}