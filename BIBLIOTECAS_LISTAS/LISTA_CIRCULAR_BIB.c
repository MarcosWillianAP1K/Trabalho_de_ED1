#include <stdio.h>
#include <stdlib.h>
#include "LISTA_CIRCULAR_BIB.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

void liberar_no_circular(Lista_circular *no, bool liberar_info)
{
    if (no == NULL)
    {
        return;
    }

    if (liberar_info)
    {
        liberar_INFO_convertido(no->tipo, &no->info);
    }

    free(no);
}

short int adicionar_elemento_circular(Lista_circular **lista, void *informacoes, TIPO_INFO tipo)
{
    if (tipo == INFO_TAREFA)
    { 
        TAREFA *info = (TAREFA *)informacoes;
        if (info->data_conclusao == NULL)
        {
            
            info->data_conclusao = criar_data_hora();
            pegar_data_atual(info->data_conclusao);
        }
    }

    if (*lista == NULL)
    {
       
        *lista = (Lista_circular *)malloc(sizeof(Lista_circular));
        (*lista)->info = informacoes;
        (*lista)->tipo = tipo;
        (*lista)->prox = *lista;
        
        return 1;
    }
    else
    {

        // Inicia com 1 pois ja vai adicionar 1
        short int contador = 1;
        Lista_circular *novo_no = (Lista_circular *)malloc(sizeof(Lista_circular));
        novo_no->info = informacoes;
        novo_no->tipo = tipo;
        novo_no->prox = *lista;

        Lista_circular *atual = *lista;

        while (atual->prox != *lista)
        {
            atual = atual->prox;
            contador++;
        }
        atual->prox = novo_no;

        // soma mais 1 pois o contador para no penultimo elemento
        return contador + 1;
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
        TAREFA *tarefa = (TAREFA *)atual->info;
        printf("Data de conclusao: ");
        printf("%02hd/%02hd/%d %02hd:%02hd\n", tarefa->data_conclusao->dia, tarefa->data_conclusao->mes, tarefa->data_conclusao->ano, tarefa->data_conclusao->hora, tarefa->data_conclusao->minuto);
        printar_INFO_convertido(atual->tipo, atual->info);
        printf("\n");
        atual = atual->prox;
    } while (atual != lista);
}

void remover_primeiro_elemento_circular(Lista_circular **lista, bool liberar_info)
{
    if (*lista == NULL)
    {
        return;
    }

    if ((*lista)->prox == *lista)
    {
        liberar_no_circular(*lista, liberar_info);
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

        liberar_no_circular(atual, liberar_info);
    }
}

void remover_elemento_circular_por_ID(Lista_circular **lista, int ID, TIPO_INFO tipo, bool liberar_info)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_circular *atual = *lista;
    Lista_circular *anterior = *lista;

    short int ID_atual = retornar_ID_convertido(atual->tipo, atual->info);

    do
    {
        if (ID_atual == ID && atual->tipo == tipo)
        {
            // Caso seja o primeiro elemento
            if (atual == *lista)
            {
                // So um elemento na lista
                if (atual == atual->prox)
                {
                    liberar_no_circular(atual, liberar_info);
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

                    liberar_no_circular(atual, liberar_info);
                    return;
                }
            }
            else
            {
                anterior->prox = atual->prox;

                liberar_no_circular(atual, liberar_info);
                return;
            }
        }

        anterior = atual;
        atual = atual->prox;

        ID_atual = retornar_ID_convertido(atual->tipo, atual->info);
    } while (atual != *lista);
}

void remover_elemento_circular_por_endereco(Lista_circular **lista, Lista_circular *endereco, bool liberar_info)
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
                    liberar_no_circular(atual, liberar_info);
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

                    liberar_no_circular(atual, liberar_info);
                    return;
                }
            }
            else
            {
                anterior->prox = atual->prox;

                liberar_no_circular(atual, liberar_info);
                return;
            }
        }

        anterior = atual;
        atual = atual->prox;

    } while (atual != *lista);
}

Lista_circular *buscar_lista_circular(Lista_circular *lista, int ID, TIPO_INFO tipo)
{
    if (lista == NULL)
    {
        return NULL;
    }

    Lista_circular *atual = lista;
    short int ID_atual = retornar_ID_convertido(atual->tipo, atual->info);

    do
    {
        if (ID_atual == ID && atual->tipo == tipo)
        {
            return atual;
        }
        atual = atual->prox;
        ID_atual = retornar_ID_convertido(atual->tipo, atual->info);
    } while (atual != lista);

    return NULL;
}

void liberar_memoria_circular(Lista_circular **lista, bool liberar_info)
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
        liberar_no_circular(atual, liberar_info);
        atual = proximo;
        proximo = atual->prox;
    }

    liberar_no_circular(atual, liberar_info);
    *lista = NULL;
}

void copiar_lista_circular(Lista_circular *lista1, Lista_circular **lista2)
{
    if (lista1 == NULL)
    {
        return;
    }

    Lista_circular *aux = lista1;
    do
    {
        adicionar_elemento_circular(lista2, aux->info, aux->tipo);
        aux = aux->prox;
    } while (aux != lista1);
}
