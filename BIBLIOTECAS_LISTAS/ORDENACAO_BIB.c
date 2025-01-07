#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ORDENACAO_BIB.h"


void copiar_lista_para_duplamente(Lista_encadeada *lista, Lista_duplamente_encadeada **lista_dupla)
{
    if (lista == NULL)
    {
        return;
    }

    while (lista != NULL)
    {
        adicionar_elemento_duplamente_encadeada(lista_dupla, lista->informacoes, lista->tipo, true);
        lista = lista->proximo;
    }
}

void copiar_duplamente_para_lista(Lista_duplamente_encadeada *lista, Lista_encadeada **lista_encadeada)
{
    if (lista == NULL)
    {
        return;
    }

    while (lista != NULL)
    {
        adicionar_elemento_encadeada(lista_encadeada, lista->informacoes, lista->tipo);
        lista = lista->proximo;
    }
}

void copiar_circular_para_duplamente(Lista_circular *lista, Lista_duplamente_encadeada **lista_dupla)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_circular *aux = lista;

    do
    {
        adicionar_elemento_duplamente_encadeada(lista_dupla, aux->info, aux->tipo, true);
        aux = aux->prox;
    } while (aux != lista);
}

void copiar_duplamente_para_circular(Lista_duplamente_encadeada *lista, Lista_circular **lista_circular)
{
    if (lista == NULL)
    {
        return;
    }

    while (lista != NULL)
    {
        adicionar_elemento_circular(lista_circular, lista->informacoes, lista->tipo);
        lista = lista->proximo;
    }
}

short int comparar_ID(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    short int ID1 = retornar_ID_convertido(tipo1, info1);
    short int ID2 = retornar_ID_convertido(tipo2, info2);

    if (ID1 > ID2)
    {
        return 1;
    }

    if (ID1 < ID2)
    {
        return -1;
    }

    return 0;
}

short int comparar_afalbetica(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    char *nome1 = retornar_nome_convertido(tipo1, info1);
    char *nome2 = retornar_nome_convertido(tipo2, info2);

    return strcmp(nome1, nome2);
}

short int comparar_prioridade(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    if (tipo1 == INFO_USUARIO || tipo2 == INFO_USUARIO)
    {
        error_tipo();
    }

    short int prioridade1 = retornar_ID_convertido(tipo1, info1);
    short int prioridade2 = retornar_ID_convertido(tipo2, info2);

    if (prioridade1 > prioridade2)
    {
        return 1;
    }

    if (prioridade1 < prioridade2)
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

short int comparar_data_entrega(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    if (tipo1 == INFO_USUARIO || tipo2 == INFO_USUARIO)
    {
        error_tipo();
    }

    DATA_HORA *data1 = retornar_data_entrega_convertida(tipo1, info1);
    DATA_HORA *data2 = retornar_data_entrega_convertida(tipo2, info2);
    


    return comparar_data(data1, data2);
}

short int comparar_data_criacao(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    if (tipo1 == INFO_USUARIO || tipo2 == INFO_USUARIO)
    {
        error_tipo();
    }

    DATA_HORA *data1 = retornar_data_criacao_convertida(tipo1, info1);
    DATA_HORA *data2 = retornar_data_criacao_convertida(tipo2, info2);

    return comparar_data(data1, data2);
}


short int comparar_data_conclusao(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2)
{
    if (info1 == NULL || info2 == NULL)
    {
        return 0;
    }

    DATA_HORA *data1 = retornar_data_conclusao_convertida(tipo1, info1);
    DATA_HORA *data2 = retornar_data_conclusao_convertida(tipo2, info2);


    return comparar_data(data1, data2);
}


// void printar_no_teste(Lista_duplamente_encadeada *anterior, Lista_duplamente_encadeada *no, Lista_duplamente_encadeada *proximo, char *nome)
// {
//     printf("anterior: %s  %s: %s  proximo:  %s\n", anterior == NULL ? "NULL" : anterior->informacoes->nome, nome, no == NULL ? "NULL" : no->informacoes->nome, proximo == NULL ? "NULL" : proximo->informacoes->nome);
// }


//Essa ordenação é exclusiva para lista circular
void selection_sort_lista_circular(Lista_circular **lista, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_circular *aux1 = *lista;
    Lista_circular *aux2 = NULL;
    Lista_circular *menor = NULL;

    while (aux1->prox != *lista)
    {
        aux2 = aux1->prox;
        menor = aux1;

        while (aux2 != *lista)
        {
            if (comparar(menor->info, aux2->info, menor->tipo, aux2->tipo) > 0)
            {
                menor = aux2;
            }
            aux2 = aux2->prox;
        }

        void *info = menor->info;
        menor->info = aux1->info;
        aux1->info = info;

        aux1 = aux1->prox;
    }
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

void bubble_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
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
            if (comparar(aux1->informacoes, aux2->informacoes, aux1->tipo, aux2->tipo) > 0)
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

void selection_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
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
            if (comparar(menor->informacoes, aux2->informacoes, aux1->tipo, aux2->tipo) > 0)
            {
                menor = aux2;
            }
            aux2 = aux2->proximo;
        }

        if (menor != aux1 && menor != NULL && aux1->anterior == NULL)
        {
            *inicio = menor;
        }
        
        trocar_nos(&aux1, &menor);


        aux1 = aux1->proximo;
    }
}

void insertion_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
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

        while (aux3 != NULL && comparar(aux3->informacoes, aux2->informacoes, aux1->tipo, aux2->tipo) > 0)
        {
            void *aux_info = aux3->informacoes;
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

void organizar_pivo(Lista_duplamente_encadeada *pivo, Lista_duplamente_encadeada **maior, Lista_duplamente_encadeada **menor, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (pivo == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux = pivo->proximo;
    pivo->anterior = NULL;
    pivo->proximo = NULL;
    Lista_duplamente_encadeada *Adicionar = NULL;

    while (aux != NULL)
    {
        Adicionar = aux;
        aux = aux->proximo;

        if (comparar(Adicionar->informacoes, pivo->informacoes, pivo->tipo, pivo->tipo) >= 0 && Adicionar != pivo)
        {
            adicionar_no_duplamente_encadeada(maior, Adicionar, true);
        }
        else
        {
            adicionar_no_duplamente_encadeada(menor, Adicionar, true);
        }
    }
}

Lista_duplamente_encadeada *contatenar_listas(Lista_duplamente_encadeada *menor, Lista_duplamente_encadeada *maior, Lista_duplamente_encadeada *pivo)
{
    Lista_duplamente_encadeada *lista = pivo;

    if (menor != NULL)
    {

        Lista_duplamente_encadeada *aux = menor;

        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }

        aux->proximo = pivo;
        pivo->anterior = aux;
        lista = menor;
    }

    if (maior != NULL)
    {
        pivo->proximo = maior;
        maior->anterior = pivo;
    }

    return lista;
}

Lista_duplamente_encadeada *quick_sort_lista_duplamente_encadeada_recursivo(Lista_duplamente_encadeada *inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (inicio == NULL || inicio->proximo == NULL)
    {
        return inicio;
    }

    Lista_duplamente_encadeada *pivo = inicio;

    Lista_duplamente_encadeada *maior = NULL;
    Lista_duplamente_encadeada *menor = NULL;

    organizar_pivo(pivo, &maior, &menor, comparar);

    if (menor != NULL)
    {
        menor = quick_sort_lista_duplamente_encadeada_recursivo(menor, comparar);
    }

    if (maior != NULL)
    {
        maior = quick_sort_lista_duplamente_encadeada_recursivo(maior, comparar);
    }

    // Problema pra contatenar
    return contatenar_listas(menor, maior, pivo);
}

void quick_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (*inicio == NULL || (*inicio)->proximo == NULL)
    {
        return;
    }

    *inicio = quick_sort_lista_duplamente_encadeada_recursivo(*inicio, comparar);
}

Lista_duplamente_encadeada *buscar_meio_lista_duplamente_encadeada(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim)
{
    if (inicio == NULL)
    {
        return NULL;
    }
    Lista_duplamente_encadeada *aux = inicio;

    while (aux != fim && aux->proximo != fim)
    {
        inicio = inicio->proximo;
        aux = aux->proximo->proximo;
    }

    return inicio;
}

Lista_duplamente_encadeada *merge(Lista_duplamente_encadeada *esquerda, Lista_duplamente_encadeada *direita, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (esquerda == NULL)
        return direita;
    if (direita == NULL)
        return esquerda;

    if (comparar(esquerda->informacoes, direita->informacoes, esquerda->tipo, direita->tipo) <= 0)
    {
        esquerda->proximo = merge(esquerda->proximo, direita, comparar);
        esquerda->proximo->anterior = esquerda;
        esquerda->anterior = NULL;
        return esquerda;
    }
    else
    {
        direita->proximo = merge(esquerda, direita->proximo, comparar);
        direita->proximo->anterior = direita;
        direita->anterior = NULL;
        return direita;
    }
}

Lista_duplamente_encadeada *merge_sort_lista_duplamente_encadeada_recursivo(Lista_duplamente_encadeada *inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (inicio == NULL || inicio->proximo == NULL)
        return inicio;

    Lista_duplamente_encadeada *meio = buscar_meio_lista_duplamente_encadeada(inicio, NULL);

    if (meio->anterior != NULL)
    {
        meio->anterior->proximo = NULL;
    }

    meio->anterior = NULL;

    Lista_duplamente_encadeada *esquerda = merge_sort_lista_duplamente_encadeada_recursivo(inicio, comparar);
    Lista_duplamente_encadeada *direita = merge_sort_lista_duplamente_encadeada_recursivo(meio, comparar);

    return merge(esquerda, direita, comparar);
}

void merge_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2))
{
    if (*inicio == NULL || (*inicio)->proximo == NULL)
    {
        return;
    }

    *inicio = merge_sort_lista_duplamente_encadeada_recursivo(*inicio, comparar);
}
