#include <stdio.h>
#include <stdlib.h>
#include "FILA_BIB.h"

void adicionar_elemento_fila(Fila **f, INFO *info)
{
    Lista_encadeada *novo = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo->informacoes = info;
    novo->proximo = NULL;

    // printf("*\n");

    if (*f == NULL)
    {
        *f = (Fila *)malloc(sizeof(Fila));
        (*f)->inicio = novo;
        (*f)->fim = novo;
    }
    else
    {
        if ((*f)->inicio == NULL)
        {
            (*f)->inicio = novo;
            (*f)->fim = novo;
        }
        else
        {

            (*f)->fim->proximo = novo;
            (*f)->fim = novo;
        }
    }
}

void atribuir_Lista_encadeada_a_fila(Lista_encadeada *lista, Fila **f)
{
    if (lista == NULL)
    {
        return;
    }

    if (*f != NULL)
    {
        liberar_fila(f);
    }

    *f = (Fila *)malloc(sizeof(Fila));
    (*f)->inicio = lista;

    while (lista->proximo != NULL)
    {
        lista = lista->proximo;
    }
    (*f)->fim = lista;
}

INFO *remover_elemento_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL)
    {
        return NULL;
    }

    Lista_encadeada *removido = f->inicio;
    INFO *info = removido->informacoes;
    f->inicio = f->inicio->proximo;
    free(removido);

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    return info;
}

void printar_inicio_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL)
    {
        printf("\nFila vazia.");
        return;
    }

    printar_dados(f->inicio->informacoes);
    printf("\n");
}

void printar_fim_fila(Fila *f)
{
    if (f == NULL || f->fim == NULL)
    {
        printf("\nFila vazia.");
        return;
    }

    printar_dados(f->fim->informacoes);
    printf("\n");
}

void printar_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL)
    {
        printf("\nFila vazia.");
        return;
    }

    Lista_encadeada *atual = f->inicio;
    while (atual != NULL)
    {
        printar_dados(atual->informacoes);
        printf("\n");
        atual = atual->proximo;
    }
}

void liberar_fila(Fila **f)
{
    Lista_encadeada *atual = (*f)->inicio;
    while (atual != NULL)
    {
        Lista_encadeada *anterior = atual;
        atual = atual->proximo;
        liberar_INFO(&anterior->informacoes);
        free(anterior);
    }
    free(*f);
    *f = NULL;
}
