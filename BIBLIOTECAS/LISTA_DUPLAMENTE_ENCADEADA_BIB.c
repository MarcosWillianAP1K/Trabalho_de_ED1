#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"

typedef struct aux_thread
{
    Lista_duplamente_encadeada *lista;
    Lista_duplamente_encadeada **meio;
} aux_thread;

void *atualizar_meio_thread(void *arg)
{
    aux_thread *aux = (aux_thread *)arg;
    Lista_duplamente_encadeada *aux_lista = aux->lista;
    *(aux->meio) = aux->lista;

    while (aux_lista != NULL && aux_lista->proximo != NULL)
    {
        aux_lista = aux_lista->proximo->proximo;
        *(aux->meio) = (*aux->meio)->proximo;
        // printf("%d\n", (*meio)->informacoes->ID);
    }

    return NULL;
}

void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, Lista_duplamente_encadeada **meio, INFO *informacao, bool frente_tras)
{
    if (*lista == NULL)
    {
        *lista = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
        (*lista)->informacoes = informacao;
        (*lista)->proximo = NULL;
        (*lista)->anterior = NULL;
        *meio = *lista;
        return;
    }

    pthread_t thread;
    aux_thread aux;
    aux.lista = *lista;
    aux.meio = meio;

    if (pthread_create(&thread, NULL, atualizar_meio_thread, (void *)&aux) != 0)
    {
        printf("Erro ao criar a thread\n");
        return;
    }

    Lista_duplamente_encadeada *novo_no = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
    novo_no->informacoes = informacao;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;

    if (frente_tras)
    {
        Lista_duplamente_encadeada *aux = *lista;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo_no;
        novo_no->anterior = aux;
    }
    else
    {
        novo_no->proximo = *lista;
        (*lista)->anterior = novo_no;
        *lista = novo_no;
    }

    if (pthread_join(thread, NULL) != 0)
    {
        printf("Erro ao esperar pela thread\n");
        return;
    }
}

void printar_lista_duplamente_encadeada(Lista_duplamente_encadeada *lista)
{
    Lista_duplamente_encadeada *aux = lista;
    while (aux != NULL)
    {
        printar_dados(aux->informacoes);
        printf("\n");
        aux = aux->proximo;
    }
    printf("\n");
}

void liberar_memoria_duplamente_encadeada(Lista_duplamente_encadeada **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *anterior = *lista;

    while (*lista != NULL)
    {
        *lista = (*lista)->proximo;
        liberar_INFO(&anterior->informacoes);
        free(anterior);
        anterior = *lista;
    }

    *lista = NULL;
}