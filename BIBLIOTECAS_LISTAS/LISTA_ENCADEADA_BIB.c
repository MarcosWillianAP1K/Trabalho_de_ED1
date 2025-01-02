#include "LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "../BIBLIOTECAS_SISTEMA/Struct_usuario.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

short int atribuir_ID()
{
    return rand() % 999 + 1;
}

typedef struct thread_verificar_ID
{
    Lista_encadeada *novo_no;
    Lista_encadeada *lista;
} thread_verificar_ID;

void *verificar_ID(void *arg)
{
    if (arg == NULL)
    {
        return NULL;
    }
    thread_verificar_ID *novo_no_thread = (thread_verificar_ID *)arg;

    short int ID_novo_no, ID_atual;

    Lista_encadeada *atual = novo_no_thread->lista;

    while (1)
    {

        atual = novo_no_thread->lista;

        ID_novo_no = atribuir_ID();

        while (atual != NULL)
        {
            ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);

            if (atual->tipo == novo_no_thread->novo_no->tipo && ID_atual == ID_novo_no && atual != novo_no_thread->novo_no)
            {
                break;
            }

            atual = atual->proximo;
        }

        if (atual == NULL)
        {
            atribuir_ID_convertido(novo_no_thread->novo_no->tipo, novo_no_thread->novo_no->informacoes, ID_novo_no);
            break;
        }
    }

    pthread_exit(NULL);
}

void adicionar_elemento_encadeada(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo)
{
    srand(time(NULL));

    // vazia
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));

        (*lista)->informacoes = informacoes;
        (*lista)->tipo = tipo;
        atribuir_ID((*lista)->informacoes);
        (*lista)->proximo = NULL;
    }
    else
    {
        Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        novo_no->informacoes = informacoes;
        novo_no->tipo = tipo;
        novo_no->proximo = NULL;

        thread_verificar_ID *novo_no_thread = (thread_verificar_ID *)malloc(sizeof(thread_verificar_ID));
        novo_no_thread->novo_no = novo_no;
        novo_no_thread->lista = *lista;

        pthread_t thread;
        pthread_create(&thread, NULL, verificar_ID, (void *)novo_no_thread);

        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;

        pthread_join(thread, NULL);

        free(novo_no_thread);
    }
}

// Esse apenas adiciona em uma lista ja ordernada, ja com base no ID fornecido
void adicionar_elemento_encadeada_ordernadado_por_ID(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo)
{
    short int ID_info = retornar_ID_convertido(tipo, informacoes);

    if (ID_info < 1 || informacoes == NULL)
    {
        printf("ID invalido\n");
        return;
    }

    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        (*lista)->informacoes = informacoes;
        (*lista)->tipo = tipo;
        (*lista)->proximo = NULL;
        return;
    }

    Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
    novo_no->informacoes = informacoes;
    novo_no->tipo = tipo;

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    short int ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);

    while (atual != NULL && ID_atual < ID_info)
    {
        anterior = atual;
        atual = atual->proximo;
        ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);
    }

    if (atual == *lista)
    {
        novo_no->proximo = *lista;
        *lista = novo_no;
    }
    else
    {
        novo_no->proximo = anterior->proximo;
        anterior->proximo = novo_no;
    }
}

// Fornece o ID do elemento a ser removido
void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID, bool liberar_info)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    short int ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);

    while (atual != NULL && ID_atual != ID)
    {
        anterior = atual;
        atual = atual->proximo;
        ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);
    }

    if (atual == *lista)
    {
        *lista = atual->proximo;

        if (liberar_info)
        {
            liberar_INFO_convertido(atual->tipo, &atual->informacoes);
        }

        free(atual);
        return;
    }

    if (atual == NULL)
    {
        printf("ID nao encontrado\n");
        return;
    }

    anterior->proximo = atual->proximo;
    if (liberar_info)
    {
        liberar_INFO_convertido(atual->tipo, &atual->informacoes);
    }
    free(atual);
}

// Fornece o endereço do elemento a ser removido, pode ser usado em conjunto com buscar_lista_encadeada
void remover_elemento_encadeada_por_endereco(Lista_encadeada **lista, Lista_encadeada *endereco, bool liberar_info)
{
    if (lista == NULL || endereco == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    if (atual == endereco)
    {
        *lista = atual->proximo;
        if (liberar_info)
        {
            liberar_INFO_convertido(atual->tipo, &atual->informacoes);
        }
        free(atual);
        return;
    }

    while (atual != NULL && atual != endereco)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Endereco nao encontrado\n");
        return;
    }

    anterior->proximo = atual->proximo;
    if (liberar_info)
    {
        liberar_INFO_convertido(atual->tipo, &atual->informacoes);
    }
    free(atual);
}

void liberar_memoria_encadeada(Lista_encadeada **lista, bool liberar_info)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;

    while (*lista != NULL)
    {

        *lista = (*lista)->proximo;

        if (liberar_info)
        {
            liberar_INFO_convertido(anterior->tipo, &anterior->informacoes);
        }
        free(anterior);
        anterior = *lista;
    }

    free(anterior);
    lista = NULL;
}

void printar_lista_encadeada(Lista_encadeada *list)
{
    if (list == NULL)
    {
        return;
    }

    while (list != NULL)
    {
        printar_INFO_convertido(list->tipo, list->informacoes);
        printf("\n");
        list = list->proximo;
    }
}

Lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID)
{
    if (list == NULL)
    {
        return NULL;
    }

    short int ID_atual = retornar_ID_convertido(list->tipo, list->informacoes);

    while (list != NULL && ID_atual != ID)
    {
        list = list->proximo;
        ID_atual = retornar_ID_convertido(list->tipo, list->informacoes);
    }

    return list;
}
