#include "LISTA_ENCADEADA_BIB.h"
#include <time.h>
#include <string.h>

// void *iniciar()
// {
//     return NULL;
// }



void adicionar_elemento(Lista_encadeada **lista, int valor)
{
    Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    // novo_no->numero = valor;
    novo_no->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = novo_no;
    }
    else
    {
        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
    }
}




void criar_lista(Lista_encadeada **lista, int tam)
{
   Lista_encadeada **atual = lista;

    for (int i = 0; i < tam; i++)
    {
        adicionar_elemento(atual, i + 1);
        atual = &(*atual)->proximo;
    }
}

void criar_lista_aleatoria(Lista_encadeada **lista, int tam)
{
    Lista_encadeada **atual = lista;

    srand(time(NULL));

    for (int i = 0; i < tam; i++)
    {
        adicionar_elemento(atual, rand() % tam);
        atual = &(*atual)->proximo;
    }
}



void liberar_memoria(Lista_encadeada *lista)
{
    Lista_encadeada *anterior = lista;

    while (lista != NULL)
    {
        lista = lista->proximo;
        free(anterior);
        anterior = lista;
    }

    free(anterior);
}




void printar_lista(Lista_encadeada *list)
{
    while (list != NULL)
    {
        
        list = list->proximo;
    }
}


void printar_lista_modificado(Lista_encadeada *list)
{
    while (list != NULL)
    {
        printf("Endereco atual: %p\n", list);
        printf("Aponta: %p\n", list->proximo);
        list = list->proximo;
    }
}

