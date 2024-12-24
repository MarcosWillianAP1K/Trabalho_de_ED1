#include <stdio.h>
#include <stdlib.h>
#include "LISTA_CIRCULAR_BIB.h"

void adicionar_elemento_circular(Lista_circular **lista, INFO *informacoes)
{

    if (*lista == NULL)
    {
        *lista = (Lista_circular *)malloc(sizeof(Lista_circular));
        (*lista)->info = informacoes;
        (*lista)->prox = *lista;
    }
    else
    {
        Lista_circular *novo_no = (Lista_circular *)malloc(sizeof(Lista_circular));
        novo_no->info = informacoes;
        novo_no->prox = *lista;
        Lista_circular *atual = *lista;
        while (atual->prox != *lista)
        {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }
}


void printar_lista_circular(Lista_circular *lista)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_circular *atual = lista;
    do
    {
        printar_dados(atual->info);
        printf("\n");
        atual = atual->prox;
    } while (atual != lista);
}


void remover_primeiro_elemento_circular(Lista_circular **lista)
{
    if (*lista == NULL)
    {
        return;
    }

    if ((*lista)->prox == *lista)
    {
        liberar_INFO(&(*lista)->info);
        free(*lista);
        *lista = NULL;
    }
    else
    {
        Lista_circular *atual = *lista;

        while (atual->prox != *lista)
        {
            atual = atual->prox;
        }
        
        atual->prox = (*lista)->prox;
        atual = *lista;
        *lista = (*lista)->prox;
        liberar_INFO(&atual->info);
        free(atual);
    }
}



void liberar_memoria_circular(Lista_circular **lista)
{
    if (*lista == NULL)
    {
        return;
    }
    

    Lista_circular *atual = *lista;
    Lista_circular *proximo = NULL;

    proximo = atual->prox;
    while (proximo != *lista)
    {
        liberar_INFO(&atual->info);
        free(atual);
        atual = proximo;
        proximo = atual->prox;
    }
    liberar_INFO(&atual->info);
    free(atual);
    *lista = NULL;
}
