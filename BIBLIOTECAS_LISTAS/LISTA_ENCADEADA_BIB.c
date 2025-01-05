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

void liberar_endereco_lista_encadeada(Endereco_lista_encadeada **endereco)
{
    if (*endereco == NULL)
    {
        return;
    }

    free(*endereco);
    *endereco = NULL;
}

void liberar_no_encadeada(Lista_encadeada *no, bool liberar_info)
{
    if (no == NULL)
    {
        return;
    }

    if (liberar_info)
    {
        liberar_INFO_convertido(no->tipo, &no->informacoes);
    }

    free(no);
}

void *verificar_ID(void *arg)
{
    srand(time(NULL));

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

void adicionar_elemento_encadeada_atribuir_ID(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo)
{
    srand(time(NULL));

    // vazia
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));

        (*lista)->informacoes = informacoes;
        (*lista)->tipo = tipo;
        atribuir_ID_convertido(tipo, (*lista)->informacoes, atribuir_ID());
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


void adicionar_elemento_encadeada(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo)
{
    // vazia
    if (*lista == NULL)
    {
        *lista = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));

        (*lista)->informacoes = informacoes;
        (*lista)->tipo = tipo;
        (*lista)->proximo = NULL;
    }
    else
    {
        Lista_encadeada *novo_no = (Lista_encadeada *)malloc(sizeof(Lista_encadeada));
        novo_no->informacoes = informacoes;
        novo_no->tipo = tipo;
        novo_no->proximo = NULL;

        Lista_encadeada *atual = *lista;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo_no;
    }
}


// Fornece o ID do elemento a ser removido
void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID, TIPO_INFO tipo ,bool liberar_info)
{
    if (lista == NULL)
    {
        return;
    }

    Lista_encadeada *anterior = *lista;
    Lista_encadeada *atual = *lista;

    short int ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);

    while (atual != NULL )
    {
        if (ID_atual == ID && atual->tipo == tipo)
        {
            break;
        }
        anterior = atual;
        atual = atual->proximo;
        ID_atual = retornar_ID_convertido(atual->tipo, atual->informacoes);
    }

    if (atual == *lista)
    {
        *lista = atual->proximo;
        liberar_no_encadeada(atual, liberar_info);

        return;
    }

    if (atual == NULL)
    {
        printf("ID nao encontrado\n");
        return;
    }

    anterior->proximo = atual->proximo;
    liberar_no_encadeada(atual, liberar_info);
}

// Fornece o endereço do elemento a ser removido, pode ser usado em conjunto com buscar_lista_encadeada
void remover_elemento_encadeada_por_endereco(Endereco_lista_encadeada *endereco, Lista_encadeada **lista, bool liberar_info)
{
    if (endereco == NULL || *lista == NULL || endereco->no == NULL)
    {
        return;
    }

    if (endereco->anterior == endereco->no)
    {
        *lista = (*lista)->proximo;
        liberar_no_encadeada(endereco->no, liberar_info);
        liberar_endereco_lista_encadeada(&endereco);
        return;
    }

    endereco->anterior->proximo = endereco->no->proximo;

    liberar_no_encadeada(endereco->no, liberar_info);
    liberar_endereco_lista_encadeada(&endereco);
    
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

        liberar_no_encadeada(anterior, liberar_info);
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

Endereco_lista_encadeada *buscar_lista_encadeada_por_nome(Lista_encadeada *list, char *nome, TIPO_INFO tipo)
{
    if (list == NULL)
    {
        return NULL;
    }

    Lista_encadeada *anterior = list;

    while (list != NULL )
    {
        // if (list != NULL)
        // {
        //     printar_INFO_convertido(list->tipo, list->informacoes);
        // }
        

        if (strstr( retornar_nome_convertido(list->tipo, list->informacoes), nome) != NULL && list->tipo == tipo)
        {
            // printf("brekou\n");
            break;
        }
        anterior = list;
        list = list->proximo;
    }

    Endereco_lista_encadeada *Endereco = (Endereco_lista_encadeada *)malloc(sizeof(Endereco_lista_encadeada));

    Endereco->anterior = anterior;
    Endereco->no = list;

    return Endereco;
}

Endereco_lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID, TIPO_INFO tipo)
{
    if (list == NULL)
    {
        return NULL;
    }

    Lista_encadeada *anterior = list;

    while (list != NULL )
    {
        if (retornar_ID_convertido(list->tipo, list->informacoes) == ID  && list->tipo == tipo)
        {
            break;
        }
        anterior = list;
        list = list->proximo;
        
    }

    Endereco_lista_encadeada *Endereco = (Endereco_lista_encadeada *)malloc(sizeof(Endereco_lista_encadeada));
    Endereco->anterior = anterior;
    Endereco->no = list;

    return Endereco;
}
