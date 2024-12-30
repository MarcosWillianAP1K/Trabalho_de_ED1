#include <stdlib.h>
#include <string.h>

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

//Pésadelo de juliana
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



void bubble_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada *inicio, short int (*comparar)(INFO *info1, INFO *info2))
{
    if (inicio == NULL)
    {
        return;
    }
 
    Lista_duplamente_encadeada *aux1 = inicio;
    Lista_duplamente_encadeada *aux2 = NULL;

    while (aux1->proximo != NULL)
    {
        aux2 = aux1->proximo;

        while (aux2 != NULL)
        {
            if (comparar(aux1->informacoes, aux2->informacoes) > 0)
            {
                INFO *aux_info = aux1->informacoes;
                aux1->informacoes = aux2->informacoes;
                aux2->informacoes = aux_info;
            }
            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
    }

}