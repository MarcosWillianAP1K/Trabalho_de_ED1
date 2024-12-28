#include "LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void atribuir_ID(INFO *informacoes)
{
    if (informacoes == NULL)
    {
        return;
    }

    informacoes->ID = (rand() % 998) + 1;
}

typedef struct thread_verificar_ID
{
    Lista_encadeada *novo_no;
    Lista_encadeada *lista;
} thread_verificar_ID;

void *verificar_ID(void *arg)
{
    thread_verificar_ID *novo_no_thread = (thread_verificar_ID *)arg;

    Lista_encadeada *atual = novo_no_thread->lista;

    while (1)
    {
        atribuir_ID(novo_no_thread->novo_no->informacoes);

        atual = novo_no_thread->lista;

        while (atual != NULL)
        {
            if (atual->informacoes->ID == novo_no_thread->novo_no->informacoes->ID && atual != novo_no_thread->novo_no)
            {
                break;
            }

            atual = atual->proximo;
        }

        if (atual == NULL)
        {
            break;
        }
    }

    pthread_exit(NULL);
}

void adicionar_elemento_encadeada(Lista_encadeada **lista, INFO *informacoes)
{
    srand(time(NULL));

    // vazia
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));

        (*lista)->informacoes = informacoes;
        atribuir_ID((*lista)->informacoes);
        (*lista)->proximo = NULL;
    }
    else
    {
        Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        novo_no->informacoes = informacoes;
        novo_no->proximo = NULL;

        thread_verificar_ID *novo_no_thread = (thread_verificar_ID *)malloc(sizeof(thread_verificar_ID));
        novo_no_thread->novo_no = novo_no;
        novo_no_thread->lista = *lista;

        pthread_t thread;
        pthread_create(&thread, NULL, verificar_ID, (void *)novo_no_thread);

        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;

        pthread_join(thread, NULL);

        free(novo_no_thread);
    }
}

// Esse apenas adiciona ja com base no ID fornecido
void adicionar_elemento_encadeada_ordernadado_por_ID(Lista_encadeada **lista, INFO *informacoes)
{
    if (informacoes->ID < 1 || informacoes == NULL)
    {
        printf("ID invalido\n");
        return;
    }

    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        (*lista)->informacoes = informacoes;
        (*lista)->proximo = NULL;
        return;
    }

    Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo_no->informacoes = informacoes;

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    while (atual != NULL && atual->informacoes->ID < novo_no->informacoes->ID)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == *lista)
    {
        novo_no->proximo = *lista;
        *lista = novo_no;
    }
    else
    {
        novo_no->proximo = anterior->proximo;
        anterior->proximo = novo_no;
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
    if (lista == NULL || endereco == NULL)
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
        return;
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
