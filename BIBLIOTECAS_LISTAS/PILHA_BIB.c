#include <stdio.h>
#include <stdlib.h>
#include "PILHA_BIB.h"

void adicionar_elemento_pilha(Pilha **p, void *info, TIPO_INFO tipo)
{
    Lista_encadeada *novo = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo->informacoes = info;
    novo->tipo = tipo;
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

    if (*p != NULL && (*p)->topo != NULL)
    {
        printf("\nPilha ja possui elementos.\n");
        return;
    }
    free(*p);
    *p = (Pilha *)malloc(sizeof(Pilha));
    (*p)->topo = lista;
}

void *remover_elemento_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        return NULL;
    }

    Lista_encadeada *removido = p->topo;
    p->topo = p->topo->proximo;

    void *info = removido->informacoes;
    TIPO_INFO tipo = removido->tipo;
    free(removido);


   

    return retorna_info_convertida(tipo, info);
}

void printar_topo_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        printf("\nPilha vazia.");
        return;
    }

    printar_INFO_convertido(p->topo->tipo, p->topo->informacoes);
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
        printar_INFO_convertido(aux->tipo, aux->informacoes);
        printf("\n");
        aux = aux->proximo;
    }
}

void liberar_pilha(Pilha **p, bool liberar_info)
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
        liberar_no_encadeada(aux, liberar_info);
    }
    free(*p);
    *p = NULL;
}