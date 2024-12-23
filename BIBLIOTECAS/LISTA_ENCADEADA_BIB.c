#include "LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// void *iniciar()
// {
//     return NULL;
// }



void adicionar_elemento_encadeada(Lista_encadeada **lista, INFO *informacoes)
{
    
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        
        (*lista)->informacoes = informacoes;
        (*lista)->proximo = NULL;
    }
    else
    {
        
        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        atual = atual->proximo;
        atual->informacoes = informacoes;
        atual->proximo = NULL;
    }
}




// void criar_lista_encadeada(Lista_encadeada **lista, int tam)
// {
//    Lista_encadeada **atual = lista;

//     for (int i = 0; i < tam; i++)
//     {
//         adicionar_elemento(atual, i + 1);
//         atual = &(*atual)->proximo;
//     }
// }

// void criar_lista_aleatoria_encadeada(Lista_encadeada **lista, int tam)
// {
//     Lista_encadeada **atual = lista;

//     srand(time(NULL));

//     for (int i = 0; i < tam; i++)
//     {
//         adicionar_elemento(atual, rand() % tam);
//         atual = &(*atual)->proximo;
//     }
// }



void liberar_memoria_encadeada(Lista_encadeada **lista)
{
    Lista_encadeada *anterior = *lista;

    while (*lista != NULL)
    {

        *lista = (*lista)->proximo;
        //Temporario, ja que tecnicamente precisamos salvar no historico
        liberar_INFO(anterior->informacoes);
        free(anterior);
        anterior = *lista;
    }

    free(anterior);
    lista = NULL;
}




// void printar_lista_encadeada(Lista_encadeada *list)
// {
//     while (list != NULL)
//     {
        
//         list = list->proximo;
//     }
// }


// void printar_lista_modificado_encadeada(Lista_encadeada *list)
// {
//     while (list != NULL)
//     {
//         printf("Endereco atual: %p\n", list);
//         printf("Aponta: %p\n", list->proximo);
//         list = list->proximo;
//     }
// }

