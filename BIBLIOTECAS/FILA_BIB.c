#include <stdio.h>
#include "FILA_BIB.h"

void adicionar_elemento_fila(Fila *f, INFO *info)
{
    Fila_encadeada *novo = (Fila_encadeada *)malloc(sizeof(Fila_encadeada));
    novo->info = info;
    novo->proximo = NULL;

    if (f = NULL)
    {
        f = (Fila *)malloc(sizeof(Fila));
        f->inicio = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->proximo = novo;
        f->fim = novo;
    }
}


INFO *remover_elemento_fila(Fila *f)
{
    if (f == NULL || f->inicio == NULL) 
    {
        return NULL;
    }

    Fila_encadeada *removido = f->inicio;
    INFO *info = removido->info;
    f->inicio = f->inicio->proximo;
    free(removido);

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    return info;
}



void liberar_fila(Fila **f)
{
    Fila_encadeada *atual = (*f)->inicio;
    while (atual != NULL)
    {
        Fila_encadeada *anterior = atual;
        atual = atual->proximo;
        free(anterior);
    }
    free(*f);
    *f = NULL;
}

