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

int ID_global;

void *percorrer_lista_esquerda_thread(void *arg)
{
    Lista_duplamente_encadeada *aux = (Lista_duplamente_encadeada *)arg;

    while (aux != NULL)
    {
        if (aux->informacoes->ID == ID_global)
        {
            return aux;
        }

        aux = aux->anterior;
    }

    return NULL;
}

void *percorrer_lista_direita_thread(void *arg)
{
    Lista_duplamente_encadeada *aux = (Lista_duplamente_encadeada *)arg;

    while (aux != NULL)
    {
        if (aux->informacoes->ID == ID_global)
        {
            return aux;
        }

        aux = aux->proximo;
    }

    return NULL;
}

int tamanho_lista_duplamente_encadeada(Lista_duplamente_encadeada *meio)
{
    if (meio == NULL)
    {
        return 0;
    }

    int tamanho = 0;
    Lista_duplamente_encadeada *aux = meio;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->proximo;
    }

    aux = meio->anterior;

    while (aux != NULL)
    {
        tamanho++;
        aux = aux->anterior;
    }

    return tamanho;
}

void remover_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada **inicio, Lista_duplamente_encadeada **meio, int ID)
{
    if (*meio == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *remover = NULL;

    if ((*meio)->informacoes->ID == ID)
    {
        remover = *meio;

        if (tamanho_lista_duplamente_encadeada(*meio) % 2 == 0)
        {
            *meio = (*meio)->anterior;
        }
        else
        {
            *meio = (*meio)->proximo;
        }
    }
    else
    {
        ID_global = ID;
        pthread_t thread_esquerda;
        pthread_t thread_direita;
        Lista_duplamente_encadeada *aux_esquerda = (*meio)->anterior;
        Lista_duplamente_encadeada *aux_direita = (*meio)->proximo;

        // Pavor de juliana
        if (pthread_create(&thread_esquerda, NULL, percorrer_lista_esquerda_thread, (void *)aux_esquerda) != 0)
        {
            printf("Erro ao criar a thread\n");
            return;
        }

        if (pthread_create(&thread_direita, NULL, percorrer_lista_direita_thread, (void *)aux_direita) != 0)
        {
            printf("Erro ao criar a thread\n");
            return;
        }

        if (pthread_join(thread_esquerda, (void **)&aux_esquerda) != 0)
        {
            printf("Erro ao esperar pela thread\n");
            return;
        }

        if (pthread_join(thread_direita, (void **)&aux_direita) != 0)
        {
            printf("Erro ao esperar pela thread\n");
            return;
        }

        if (aux_esquerda != NULL)
        {

            remover = aux_esquerda;
            *meio = (*meio)->proximo;
        }

        if (aux_direita != NULL)
        {

            remover = aux_direita;
            *meio = (*meio)->anterior;
        }
    }

    if (remover != NULL)
    {

        if (remover->anterior != NULL)
        {
            remover->anterior->proximo = remover->proximo;
        }
        else
        {
            *inicio = remover->proximo;
            remover->proximo->anterior = NULL;
        }

        if (remover->proximo != NULL)
        {
            remover->proximo->anterior = remover->anterior;
        }
        else
        {
            remover->anterior->proximo = NULL;
        }

        liberar_INFO(&remover->informacoes);
        free(remover);
    }
}