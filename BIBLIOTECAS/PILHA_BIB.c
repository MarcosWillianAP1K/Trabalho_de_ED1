#include <stdio.h>
#include <stdlib.h>
#include "PILHA_BIB.h"

void adicionar_elemento_pilha(Pilha **p, INFO *info)
{
    Lista_encadeada *novo = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo->informacoes = info;
    novo->proximo = NULL;

    if (*p == NULL)
    {
        *p = (Pilha *)malloc(sizeof(Pilha));
        (*p)->topo = novo;
    }
    else
    {
        if ((*p)->topo == NULL)
        {
            (*p)->topo = novo;
        }
        else
        {
            novo->proximo = (*p)->topo;
            (*p)->topo = novo;
        }
    }
}

void atribuir_Lista_encadeada_a_pilha(Lista_encadeada *lista, Pilha **p)
{
    if (lista == NULL)
    {
        return;
    }

    if (*p != NULL)
    {
        liberar_pilha(p);
    }

    *p = (Pilha *)malloc(sizeof(Pilha));
    (*p)->topo = lista;
}

INFO *remover_elemento_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        return NULL;
    }

    Lista_encadeada *removido = p->topo;
    INFO *info = removido->informacoes;
    p->topo = p->topo->proximo;
    free(removido);

    return info;
}

void printar_topo_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        printf("\nPilha vazia.");
        return;
    }

    printar_dados(p->topo->informacoes);
    printf("\n");
}

void printar_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        printf("\nPilha vazia.");
        return;
    }

    Lista_encadeada *aux = p->topo;

    while (aux != NULL)
    {
        printar_dados(aux->informacoes);
        printf("\n");
        aux = aux->proximo;
    }
}

void liberar_pilha(Pilha **p)
{
    if (*p == NULL)
    {
        return;
    }

    Lista_encadeada *aux;

    while ((*p)->topo != NULL)
    {
        aux = (*p)->topo;
        (*p)->topo = (*p)->topo->proximo;
        liberar_INFO(&aux->informacoes);
        free(aux);
    }
}