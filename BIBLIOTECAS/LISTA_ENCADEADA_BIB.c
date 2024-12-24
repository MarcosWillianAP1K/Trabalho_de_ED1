#include "LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void adicionar_elemento_encadeada(Lista_encadeada **lista, INFO *informacoes)
{
    // vazia
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));

        (*lista)->informacoes = informacoes;
        (*lista)->informacoes->ID = 1;
        (*lista)->proximo = NULL;
    }
    else if ((*lista)->informacoes->ID > 1)
    {
        // Caso o primeiro ID não seja 1
        Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        novo_no->informacoes = informacoes;
        novo_no->informacoes->ID = 1;
        novo_no->proximo = *lista;
        *lista = novo_no;
    }
    else
    {
        // Caso o ID não seja sequencial ou seja o ultimo
        Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        novo_no->informacoes = informacoes;

        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL && atual->informacoes->ID + 1 == atual->proximo->informacoes->ID)
        {
            atual = atual->proximo;
        }

        novo_no->informacoes->ID = atual->informacoes->ID + 1;

        if (atual->proximo == NULL)
        {
            novo_no->proximo = NULL;
            atual->proximo = novo_no;
        }
        else
        {
            novo_no->proximo = atual->proximo;
            atual->proximo = novo_no;
        }
    }
}

// Fornece o ID do elemento a ser removido
void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    if (atual->informacoes->ID == ID)
    {
        *lista = atual->proximo;
        liberar_INFO(&atual->informacoes);
        free(atual);
        return;
    }

    while (atual != NULL && atual->informacoes->ID != ID)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("ID nao encontrado\n");
        return;
    }

    anterior->proximo = atual->proximo;
    liberar_INFO(&atual->informacoes);
    free(atual);
}

// Fornece o endereço do elemento a ser removido, pode ser usado em conjunto com buscar_lista_encadeada
void remover_elemento_encadeada_por_endereco(Lista_encadeada **lista, Lista_encadeada *endereco)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    if (atual == endereco)
    {
        *lista = atual->proximo;
        liberar_INFO(&atual->informacoes);
        free(atual);
        return;
    }

    while (atual != NULL && atual != endereco)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Endereco nao encontrado\n");
        return;
    }

    anterior->proximo = atual->proximo;
    liberar_INFO(&atual->informacoes);
    free(atual);
}

void liberar_memoria_encadeada(Lista_encadeada **lista)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;

    while (*lista != NULL)
    {

        *lista = (*lista)->proximo;
        // Temporario, ja que tecnicamente precisamos salvar no historico
        liberar_INFO(&anterior->informacoes);
        free(anterior);
        anterior = *lista;
    }

    free(anterior);
    lista = NULL;
}

void printar_lista_encadeada(Lista_encadeada *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    while (list != NULL)
    {
        printar_dados(list->informacoes);
        printf("\n");
        list = list->proximo;
    }
}

Lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID)
{
    if (list == NULL)
    {
        return NULL;
    }

    while (list != NULL && list->informacoes->ID != ID)
    {
        list = list->proximo;
    }

    return list;
}
