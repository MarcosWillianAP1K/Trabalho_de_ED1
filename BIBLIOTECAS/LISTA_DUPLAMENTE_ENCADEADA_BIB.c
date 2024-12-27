#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"

typedef struct aux_thread
{
    Lista_duplamente_encadeada *lista;
    Lista_duplamente_encadeada **meio;
} aux_thread;

void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, INFO *informacao, bool frente_tras)
{
    if (*lista == NULL)
    {
        *lista = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
        (*lista)->informacoes = informacao;
        (*lista)->proximo = NULL;
        (*lista)->anterior = NULL;
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

void remover_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada **lista, int ID)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux = *lista;

    while (aux != NULL && aux->informacoes->ID != ID)
    {

        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        return;
    }

    if (aux->anterior != NULL)
    {
        aux->anterior->proximo = aux->proximo;
    }
    else
    {
        *lista = aux->proximo;
        (*lista)->anterior = NULL;
    }

    if (aux->proximo != NULL)
    {
        aux->proximo->anterior = aux->anterior;
    }
    else
    {
        aux->anterior->proximo = NULL;
    }

    liberar_INFO(&aux->informacoes);
    free(aux);
}

// Essa funciona diferente das outras bibliotecas, ela ja remove o elemento direto
void remover_elemento_duplamente_encadeada_por_endereco(Lista_duplamente_encadeada *lista, Lista_duplamente_encadeada **inicio)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux = lista;

    // Se anterior for null, este no é o primeiro da lista
    if (aux->anterior != NULL)
    {
        aux->anterior->proximo = aux->proximo;
    }
    else
    {
        lista = aux->proximo;
        lista->anterior = NULL;
        *inicio = lista;
    }

    if (aux->proximo != NULL)
    {
        aux->proximo->anterior = aux->anterior;
    }
    else
    {
        aux->anterior->proximo = NULL;
    }

    liberar_INFO(&aux->informacoes);
    free(aux);
}

Lista_duplamente_encadeada *buscar_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada *lista, int ID)
{
    Lista_duplamente_encadeada *aux = lista;

    while (aux != NULL && aux->informacoes->ID != ID)
    {
        aux = aux->proximo;
    }

    return aux;
}

Lista_duplamente_encadeada *buscar_meio(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim)
{
    Lista_duplamente_encadeada *aux = inicio;
    while (aux != fim && aux->proximo != fim)
    {
        inicio = inicio->proximo;
        aux = aux->proximo->proximo;
    }

    return inicio;
}

Lista_duplamente_encadeada *busca_binaria_recursiva(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim, int *ID)
{
    if (inicio == NULL)
    {
        return NULL;
    }

    Lista_duplamente_encadeada *meio = buscar_meio(inicio, fim);

    if (meio->informacoes->ID == *ID)
    {
        return meio;
    }
    else if (meio->informacoes->ID < *ID && meio->proximo != NULL)
    {
        return busca_binaria_recursiva(meio->proximo, fim, ID);
    }
    else if (meio->informacoes->ID > *ID && meio->anterior != NULL)
    {
        return busca_binaria_recursiva(inicio, meio->anterior, ID);
    }

    return NULL;
}


Lista_duplamente_encadeada *busca_binaria_duplamente_encadeada(Lista_duplamente_encadeada *lista, int ID)
{
    if (lista == NULL)
    {
        return NULL;
    }
    

    Lista_duplamente_encadeada *inicio = lista;
    Lista_duplamente_encadeada *fim = NULL;

    Lista_duplamente_encadeada *meio = buscar_meio(inicio, fim);

    if (meio->informacoes->ID == ID)
    {
        return meio;
    }
    else if (meio->informacoes->ID < ID && meio->proximo != NULL)
    {
        return busca_binaria_recursiva(meio->proximo, fim, &ID);
    }
    else if (meio->informacoes->ID > ID && meio->anterior != NULL)
    {
        return busca_binaria_recursiva(inicio, meio->anterior, &ID);
    }

    return NULL;
}
