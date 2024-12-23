#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
// #include "BIBLIOTECAS/Struct_info.h"


int main()
{
    Lista_encadeada *lista = NULL;

    INFO *teste1 = escrever_dados();
    INFO *teste2 = escrever_dados();


    adicionar_elemento_encadeada(&lista, teste1);

    adicionar_elemento_encadeada(&lista, teste2);


    printf("\nID: %d\n", lista->informacoes->ID);
    printf("Nome: %s\n", lista->informacoes->nome);
    printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    printf("Minuto: %d\n", lista->informacoes->minuto);
    printf("Hora: %d\n", lista->informacoes->hora);
    printf("Dia: %d\n", lista->informacoes->dia);
    printf("Mes: %d\n", lista->informacoes->mes);
    printf("Ano: %d\n", lista->informacoes->ano);
    
    
    lista = lista->proximo;

    printf("\nID: %d\n", lista->informacoes->ID);
    printf("Nome: %s\n", lista->informacoes->nome);
    printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    printf("Minuto: %d\n", lista->informacoes->minuto);
    printf("Hora: %d\n", lista->informacoes->hora);
    printf("Dia: %d\n", lista->informacoes->dia);
    printf("Mes: %d\n", lista->informacoes->mes);
    printf("Ano: %d\n", lista->informacoes->ano);


    liberar_memoria_encadeada(&lista);

    

    return 0;
}