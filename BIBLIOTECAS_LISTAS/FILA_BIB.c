#include <stdio.h>
#include <stdlib.h>
#include "FILA_BIB.h"

void adicionar_elemento_fila(Fila **f, void *info, TIPO_INFO tipo)
{
    Lista_encadeada *novo = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo->informacoes = info;
    novo->tipo = tipo;
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
    if (lista == NULL )
    {
        return;
    }

    if (*f != NULL && (*f)->inicio != NULL)
    {
        printf("Fila ja possui elementos\n");
        return;
    }
    free(*f);

    *f = (Fila *)malloc(sizeof(Fila));
    (*f)->inicio = lista;

    while (lista->proximo != NULL)
    {
        lista = lista->proximo;
    }
    (*f)->fim = lista;
}

void *remover_elemento_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL)
    {
        return NULL;
    }

    Lista_encadeada *removido = f->inicio;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }
    TIPO_INFO tipo = removido->tipo;
    void *info = removido->informacoes;
    free(removido);

    return retorna_info_convertida(tipo, info);
}

void printar_inicio_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL)
    {
        printf("\nFila vazia.");
        return;
    }

    printar_INFO_convertido(f->inicio->tipo, f->inicio->informacoes);
    printf("\n");
}

void printar_fim_fila(Fila *f)
{
    if (f == NULL || f->fim == NULL)
    {
        printf("\nFila vazia.");
        return;
    }

    printar_INFO_convertido(f->fim->tipo, f->fim->informacoes);
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
        printar_INFO_convertido(atual->tipo, atual->informacoes);
        printf("\n");
        atual = atual->proximo;
    }
}

void liberar_fila(Fila **f, bool liberar_info)
{
    Lista_encadeada *atual = (*f)->inicio;
    while (atual != NULL)
    {
        Lista_encadeada *anterior = atual;
        atual = atual->proximo;
        liberar_no_encadeada(anterior, liberar_info);
    }
    free(*f);
    *f = NULL;
}
