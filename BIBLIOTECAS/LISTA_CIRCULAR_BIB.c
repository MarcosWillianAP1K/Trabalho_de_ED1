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

void remover_elemento_circular_por_ID(Lista_circular **lista, int ID)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_circular *atual = *lista;
    Lista_circular *anterior = *lista;

    do
    {
        if (atual->info->ID == ID)
        {
            // Caso seja o primeiro elemento
            if (atual == *lista)
            {
                // So um elemento na lista
                if (atual == atual->prox)
                {
                    liberar_INFO(&atual->info);
                    free(atual);
                    *lista = NULL;
                    return;
                }
                else
                {
                    while (anterior->prox != *lista)
                    {
                        anterior = anterior->prox;
                    }
                    anterior->prox = atual->prox;
                    *lista = atual->prox;
                    liberar_INFO(&atual->info);
                    free(atual);
                    return;
                }
            }
            else
            {
                anterior->prox = atual->prox;
                liberar_INFO(&atual->info);
                free(atual);
                return;
            }
        }

        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);
}

void remover_elemento_circular_por_endereco(Lista_circular **lista, Lista_circular *endereco)
{
    if (*lista == NULL || endereco == NULL)
    {
        return;
    }

    Lista_circular *atual = *lista;
    Lista_circular *anterior = *lista;

    do
    {
        if (atual == endereco)
        {
            // Caso seja o primeiro elemento
            if (atual == *lista)
            {
                // So um elemento na lista
                if (atual == atual->prox)
                {
                    liberar_INFO(&atual->info);
                    free(atual);
                    *lista = NULL;
                    return;
                }
                else
                {
                    while (anterior->prox != *lista)
                    {
                        anterior = anterior->prox;
                    }
                    anterior->prox = atual->prox;
                    *lista = atual->prox;
                    liberar_INFO(&atual->info);
                    free(atual);
                    return;
                }
            }
            else
            {
                anterior->prox = atual->prox;
                liberar_INFO(&atual->info);
                free(atual);
                return;
            }
        }

        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);
}

Lista_circular *buscar_lista_circular(Lista_circular *lista, int ID)
{
    if (lista == NULL)
    {
        return NULL;
    }

    Lista_circular *atual = lista;

    do
    {
        if (atual->info->ID == ID)
        {
            return atual;
        }
        atual = atual->prox;
    } while (atual != lista);

    return NULL;
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
