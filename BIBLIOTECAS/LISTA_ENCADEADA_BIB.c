#include "LISTA_ENCADEADA_BIB.h"
#include <time.h>
#include <string.h>

void *iniciar()
{
    return NULL;
}



void adicionar_elemento(Lista **lista, int valor)
{
    Lista *novo_no = (Lista *)malloc(sizeof(Lista));
    novo_no->numero = valor;
    novo_no->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = novo_no;
    }
    else
    {
        Lista *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
    }
}

void adicionar_nomes(Lista_de_strings **lista, char *string)
{
    Lista_de_strings *novo_no = (Lista_de_strings *)malloc(sizeof(Lista_de_strings));
    strcpy(novo_no->string, string);
    novo_no->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = novo_no;
    }
    else
    {
        Lista_de_strings *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
    }

}

void adicionar_vetor(Lista_vetores **lista, int *vetor)
{
    Lista_vetores *novo_no = (Lista_vetores *)malloc(sizeof(Lista_vetores));

    novo_no->vetor = vetor;
    novo_no->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = novo_no;
    }
    else
    {
        Lista_vetores *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
    }
}



void criar_lista(Lista **lista, int tam)
{
    Lista **atual = lista;

    for (int i = 0; i < tam; i++)
    {
        adicionar_elemento(atual, i + 1);
        atual = &(*atual)->proximo;
    }
}

void criar_lista_aleatoria(Lista **lista, int tam)
{
    Lista **atual = lista;

    srand(time(NULL));

    for (int i = 0; i < tam; i++)
    {
        adicionar_elemento(atual, rand() % tam);
        atual = &(*atual)->proximo;
    }
}



void liberar_memoria(Lista *lista)
{
    Lista *anterior = lista;

    while (lista != NULL)
    {
        lista = lista->proximo;
        free(anterior);
        anterior = lista;
    }

    free(anterior);
}

void liberar_memoria_nomes(Lista_de_strings *lista)
{
    Lista_de_strings *anterior = lista;

    while (lista != NULL)
    {
        lista = lista->proximo;
        free(anterior);
        anterior = lista;
    }

    free(anterior);
}

void liberar_memoria_vetor(Lista_vetores *lista)
{
    Lista_vetores *anterior = lista;

    while (lista != NULL)
    {
        lista = lista->proximo;
        free(anterior);
        anterior = lista;
    }

    free(anterior);
}



void printar_lista(Lista *list)
{
    while (list != NULL)
    {
        printf("%d ", list->numero);
        list = list->proximo;
    }
}

void printar_lista_nomes(Lista_de_strings *list)
{
    while (list != NULL)
    {
        printf("%s  ", list->string);
        list = list->proximo;
    }
}

void printar_lista_modificado(Lista *list)
{
    while (list != NULL)
    {
        printf("\nvalor: %d\n", list->numero);
        printf("Endereco atual: %p\n", list);
        printf("Aponta: %p\n", list->proximo);
        list = list->proximo;
    }
}

void printar_lista_vetor(Lista_vetores *list)
{
    while (list != NULL)
    {
        int tam = sizeof(list->vetor) - 1;
        printf("[");
     
        for (int i = 0; i < tam; i++)
        {
            printf("%d", list->vetor[i]);
            
            if (i != tam -1)
            {
                printf(", ");
            }
        }
        printf("]  ");
        
        list = list->proximo;
    }
}
