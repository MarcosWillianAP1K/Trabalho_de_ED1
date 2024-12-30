#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ORDENACAO_BIB.h"

short int comparar_ID(INFO *info1, INFO *info2)
{
    if (info1->ID > info2->ID)
    {
        return 1;
    }

    if (info1->ID < info2->ID)
    {
        return -1;
    }

    return 0;
}

short int comparar_afalbetica(INFO *info1, INFO *info2)
{
    return strcmp(info1->nome, info2->nome);
}

short int comparar_prioridade(INFO *info1, INFO *info2)
{
    if (info1->nivel_prioridade > info2->nivel_prioridade)
    {
        return 1;
    }

    if (info1->nivel_prioridade < info2->nivel_prioridade)
    {
        return -1;
    }

    return 0;
}

// Pésadelo de juliana
short int comparar_data(DATA_HORA *data1, DATA_HORA *data2)
{
    if (data1->ano > data2->ano)
    {
        return 1;
    }

    if (data1->ano < data2->ano)
    {
        return -1;
    }

    if (data1->mes > data2->mes)
    {
        return 1;
    }

    if (data1->mes < data2->mes)
    {
        return -1;
    }

    if (data1->dia > data2->dia)
    {
        return 1;
    }

    if (data1->dia < data2->dia)
    {
        return -1;
    }

    if (data1->hora > data2->hora)
    {
        return 1;
    }

    if (data1->hora < data2->hora)
    {
        return -1;
    }

    if (data1->minuto > data2->minuto)
    {
        return 1;
    }

    if (data1->minuto < data2->minuto)
    {
        return -1;
    }

    return 0;
}

short int comparar_data_entrega(INFO *info1, INFO *info2)
{
    return comparar_data(info1->data_entrega, info2->data_entrega);
}

short int comparar_data_criacao(INFO *info1, INFO *info2)
{
    return comparar_data(info1->data_criacao, info2->data_criacao);
}

void printar_no_teste(Lista_duplamente_encadeada *anterior, Lista_duplamente_encadeada *no, Lista_duplamente_encadeada *proximo, char *nome)
{
    printf("anterior: %s  %s: %s  proximo:  %s\n", anterior == NULL ? "NULL" : anterior->informacoes->nome, nome, no == NULL ? "NULL" : no->informacoes->nome, proximo == NULL ? "NULL" : proximo->informacoes->nome);
}

void trocar_nos(Lista_duplamente_encadeada **no1, Lista_duplamente_encadeada **no2)
{
    if (*no1 == NULL || *no2 == NULL || *no1 == *no2)
    {
        return;
    }

    Lista_duplamente_encadeada *proximo1 = (*no1)->proximo;
    Lista_duplamente_encadeada *anterior1 = (*no1)->anterior;
    Lista_duplamente_encadeada *proximo2 = (*no2)->proximo;
    Lista_duplamente_encadeada *anterior2 = (*no2)->anterior;
    Lista_duplamente_encadeada *aux = *no1;

    if (*no1 == proximo2)
    {
        (*no1)->proximo = *no2;
    }
    else
    {
        (*no1)->proximo = (*no2)->proximo;
    }

    if (*no1 == anterior2)
    {
        (*no1)->anterior = *no2;
    }
    else
    {
        (*no1)->anterior = (*no2)->anterior;
    }

    if (*no2 == proximo1)
    {
        (*no2)->proximo = *no1;
    }
    else
    {
        (*no2)->proximo = proximo1;
    }

    if (*no2 == anterior1)
    {
        (*no2)->anterior = *no1;
    }
    else
    {
        (*no2)->anterior = anterior1;
    }

    if (proximo1 != NULL && proximo1 != *no2)
    {
        proximo1->anterior = *no2;
    }

    if (anterior1 != NULL && anterior1 != *no2)
    {
        anterior1->proximo = *no2;
    }

    if (proximo2 != NULL && proximo2 != *no1)
    {
        proximo2->anterior = *no1;
    }

    if (anterior2 != NULL && anterior2 != *no1)
    {
        anterior2->proximo = *no1;
    }

    *no1 = *no2;
    *no2 = aux;
}

void bubble_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (inicio == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux1 = *inicio;
    Lista_duplamente_encadeada *aux2 = NULL;

    while (aux1->proximo != NULL)
    {
        aux2 = aux1->proximo;

        while (aux2 != NULL)
        {
            // printf("Comparando %s com %s\n", aux1->informacoes->nome, aux2->informacoes->nome);
            if (comparar(aux1->informacoes, aux2->informacoes) > 0)
            {
                trocar_nos(&aux1, &aux2);
            }
            aux2 = aux2->proximo;
        }

        if (aux1->anterior == NULL)
        {
            *inicio = aux1;
        }

        aux1 = aux1->proximo;
    }
}

void selection_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (*inicio == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux1 = *inicio;
    Lista_duplamente_encadeada *aux2 = NULL;
    Lista_duplamente_encadeada *menor = NULL;

    while (aux1->proximo != NULL)
    {
        aux2 = aux1->proximo;
        menor = aux1;

        while (aux2 != NULL)
        {
            if (comparar(menor->informacoes, aux2->informacoes) > 0)
            {
                menor = aux2;
            }
            aux2 = aux2->proximo;
        }

        trocar_nos(&aux1, &menor);

        if (aux1->anterior == NULL)
        {
            *inicio = aux1;
        }

        aux1 = aux1->proximo;
    }
}

void insertion_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (*inicio == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux1 = *inicio;
    Lista_duplamente_encadeada *aux2 = NULL;
    Lista_duplamente_encadeada *aux3 = NULL;

    while (aux1->proximo != NULL)
    {
        aux2 = aux1->proximo;
        aux3 = aux1;

        while (aux3 != NULL && comparar(aux3->informacoes, aux2->informacoes) > 0)
        {
            INFO *aux_info = aux3->informacoes;
            aux3->informacoes = aux2->informacoes;
            aux2->informacoes = aux_info;

            aux3 = aux3->anterior;
            aux2 = aux2->anterior;
        }

        aux1 = aux1->proximo;
    }

    // while ((*inicio)->anterior != NULL)
    // {
    //     *inicio = (*inicio)->anterior;
    // }
}

// Lista_duplamente_encadeada *buscar_meio_lista_duplamente_encadeada(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim)
// {
//     if (inicio == NULL)
//     {
//         return NULL;
//     }

//     while(inicio != fim && inicio->proximo != fim)
//     {
//         inicio = inicio->proximo;
//         fim = fim->anterior;
//     }

//     return inicio;
// }


void organizar_pivo(Lista_duplamente_encadeada *pivo,  Lista_duplamente_encadeada *maior, Lista_duplamente_encadeada *menor, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (pivo == NULL)
    {
        return;
    }

    
    Lista_duplamente_encadeada *aux = pivo->proximo;
    Lista_duplamente_encadeada *Adicionar = NULL;

    while (aux != NULL)
    {
        Adicionar = aux;
        aux = aux->proximo;

        if (comparar(Adicionar->informacoes, pivo->informacoes) > 0)
        {
            adicionar_a_frente_duplamente_encadeada(&maior, Adicionar);
        }
        else
        {
            adicionar_a_frente_duplamente_encadeada(&menor, Adicionar);
        }
    }
}

void contatenar_listas(Lista_duplamente_encadeada **inicio, Lista_duplamente_encadeada *maior, Lista_duplamente_encadeada *pivo)
{
    

    Lista_duplamente_encadeada *aux = *inicio;

    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = pivo;
    pivo->anterior = aux;

   
    pivo->proximo = maior;
        
    
}


void quick_sort_lista_duplamente_encadeada_recursivo(Lista_duplamente_encadeada **inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (*inicio == NULL || (*inicio)->proximo == NULL)
    {
        printf("Voltando tudo\n");
        return;
    }

    Lista_duplamente_encadeada *pivo = *inicio;

    Lista_duplamente_encadeada *maior = NULL;
    Lista_duplamente_encadeada *menor = NULL;

    organizar_pivo(pivo, maior, menor, comparar);

    if (menor != NULL)
    {
        quick_sort_lista_duplamente_encadeada_recursivo(&menor, comparar);
    }
    
    if (maior != NULL)
    {
        quick_sort_lista_duplamente_encadeada_recursivo(&maior, comparar);
    }
    //Problema pra contatenar
    

}

void quick_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (*inicio == NULL)
    {
        return;
    }

    quick_sort_lista_duplamente_encadeada_recursivo(*inicio, comparar);

    
}
