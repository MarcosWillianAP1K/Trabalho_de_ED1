#include <stdio.h>
#include <stdlib.h>
#include "PILHA_BIB.h"

void adicionar_elemento_pilha(Pilha **p, void *info, TIPO_INFO tipo)
{
    Pilha_encadeada *novo = (Pilha_encadeada *)malloc(sizeof(Pilha_encadeada));
    novo->ultimo_estado = info;
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

void *remover_elemento_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        return NULL;
    }

    Pilha_encadeada *removido = p->topo;
    p->topo = p->topo->proximo;

    void *info = removido->ultimo_estado;
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

    printar_INFO_convertido(p->topo->tipo, p->topo->ultimo_estado);
    printf("\n");
}

void printar_pilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
    {
        printf("\nPilha vazia.");
        return;
    }

    Pilha_encadeada *aux = p->topo;

    while (aux != NULL)
    {
        printar_INFO_convertido(aux->tipo, aux->ultimo_estado);
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

    Pilha_encadeada *aux;

    while ((*p)->topo != NULL)
    {
        if ((*p)->topo->tipo == INFO_GERENTE)
        {
            printf("Esse tipo de informacao nao pode ser liberada aqui\n");
            exit(1);
        }

        aux = (*p)->topo;
        (*p)->topo = (*p)->topo->proximo;
        liberar_INFO_convertido(aux->tipo, aux->ultimo_estado);
        free(aux);
    }
    free(*p);
    *p = NULL;
}