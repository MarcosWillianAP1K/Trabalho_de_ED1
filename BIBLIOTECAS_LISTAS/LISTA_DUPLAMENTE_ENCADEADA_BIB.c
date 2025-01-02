#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"

typedef struct aux_thread
{
    Lista_duplamente_encadeada *lista;
    Lista_duplamente_encadeada **meio;
} aux_thread;


void liberar_no_duplamente_encadeada(Lista_duplamente_encadeada *lista, bool liberar_info)
{

    if (lista == NULL)
    {
        return;
    }

    if (liberar_info)
    {
        liberar_INFO_convertido(lista->tipo, &lista->informacoes);
    }

    free(lista);
}

//TRUE = FRENTE
//FALSE = TRAS
void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, void *informacao, TIPO_INFO tipo , bool frente_tras)
{
    if (*lista == NULL)
    {
        *lista = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
        (*lista)->informacoes = informacao;
        (*lista)->tipo = tipo;
        (*lista)->proximo = NULL;
        (*lista)->anterior = NULL;
        return;
    }

    Lista_duplamente_encadeada *novo_no = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
    novo_no->informacoes = informacao;
    novo_no->tipo = tipo;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;

    Lista_duplamente_encadeada *aux = *lista;
    if (frente_tras)
    {
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo_no;
        novo_no->anterior = aux;
    }
    else
    {
        while(aux->anterior != NULL)
        {
            aux = aux->anterior;
        }

        aux->anterior = novo_no;
        novo_no->proximo = aux;
        *lista = novo_no;
    }
}

void adicionar_no_duplamente_encadeada(Lista_duplamente_encadeada **lista, Lista_duplamente_encadeada *novo_no, bool frente_tras)
{
    if (*lista == NULL)
    {
        *lista = novo_no;
        novo_no->proximo = NULL;
        novo_no->anterior = NULL;
        return;
    }

    novo_no->proximo = NULL;
    novo_no->anterior = NULL;
    Lista_duplamente_encadeada *aux = *lista;

    if (frente_tras)
    {
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo_no;
        novo_no->anterior = aux;
    }
    else
    {
        while (aux->anterior != NULL)
        {
            aux = aux->anterior;
        }
        
        aux->anterior = novo_no;
        novo_no->proximo = aux;
        *lista = novo_no;
    }
}

void printar_lista_duplamente_encadeada(Lista_duplamente_encadeada *lista)
{
    Lista_duplamente_encadeada *aux = lista;
    while (aux != NULL)
    {
        printar_INFO_convertido(aux->tipo, aux->informacoes);
        printf("\n");
        aux = aux->proximo;
    }
    printf("\n");
}

void liberar_memoria_duplamente_encadeada(Lista_duplamente_encadeada **lista, bool liberar_info)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *anterior = *lista;

    while (*lista != NULL)
    {
        *lista = (*lista)->proximo;
        liberar_no_duplamente_encadeada(anterior, liberar_info);
        anterior = *lista;
    }

    *lista = NULL;
}

void remover_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada **lista, int ID, TIPO_INFO tipo , bool liberar_info)
{
    if (*lista == NULL)
    {
        return;
    }

    Lista_duplamente_encadeada *aux = *lista;
    short int ID_aux = retornar_ID_convertido(aux->tipo, aux->informacoes);

    while (aux != NULL)
    {
        if ( ID_aux == ID && aux->tipo == tipo)
        {
            break;
        }
        
        aux = aux->proximo;
        ID_aux = retornar_ID_convertido(aux->tipo, aux->informacoes);
    }

    if (aux == NULL)
    {
        return;
    }
    
    if (aux->anterior == NULL && aux->proximo == NULL)
    {
        liberar_no_duplamente_encadeada(aux, liberar_info);
        *lista = NULL;
        return;
    }
    

    if (aux->anterior != NULL)
    {
        aux->anterior->proximo = aux->proximo;
    }
    else
    {
        *lista = aux->proximo;
        (*lista)->anterior = NULL;
    }

    if (aux->proximo != NULL)
    {
        aux->proximo->anterior = aux->anterior;
    }
    else
    {
        aux->anterior->proximo = NULL;
    }

    liberar_no_duplamente_encadeada(aux, liberar_info);
}

// Essa funciona diferente das outras bibliotecas, ela ja remove o elemento direto
void remover_elemento_duplamente_encadeada_por_endereco(Lista_duplamente_encadeada *lista, Lista_duplamente_encadeada **inicio, bool liberar_info)
{
    if (lista == NULL)
    {
        return;
    }
   

    Lista_duplamente_encadeada *aux = lista;

    if (aux == *inicio && aux->proximo == NULL)
    {
        liberar_no_duplamente_encadeada(aux, liberar_info);
        *inicio = NULL;
        return;
    }

   


    // Se anterior for null, este no é o primeiro da lista
    if (aux->anterior != NULL)
    {
        aux->anterior->proximo = aux->proximo;
    }
    else
    {
        lista = aux->proximo;
        lista->anterior = NULL;
        *inicio = lista;
    }
    

    if (aux->proximo != NULL)
    {
        aux->proximo->anterior = aux->anterior;
    }
    else
    {
        aux->anterior->proximo = NULL;
    }
    

    
    liberar_no_duplamente_encadeada(aux, liberar_info);
    

}

Lista_duplamente_encadeada *buscar_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada *lista, int ID,  TIPO_INFO tipo_info)
{
    Lista_duplamente_encadeada *aux = lista;

    short int ID_aux = retornar_ID_convertido(aux->tipo, aux->informacoes);

    while (aux != NULL )
    {
        if (ID_aux == ID && aux->tipo == tipo_info)
        {
            return aux;
        }
        aux = aux->proximo;
        ID_aux = retornar_ID_convertido(aux->tipo, aux->informacoes);
    }

    return aux;
}

Lista_duplamente_encadeada *buscar_meio(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim)
{
    Lista_duplamente_encadeada *aux = inicio;
    while (aux != fim && aux->proximo != fim)
    {
        inicio = inicio->proximo;
        aux = aux->proximo->proximo;
    }

    return inicio;
}

Lista_duplamente_encadeada *busca_binaria_recursiva(Lista_duplamente_encadeada *inicio, Lista_duplamente_encadeada *fim, int *ID, TIPO_INFO tipo)
{
    if (inicio == NULL)
    {
        return NULL;
    }

    Lista_duplamente_encadeada *meio = buscar_meio(inicio, fim);
    short int ID_meio = retornar_ID_convertido(meio->tipo, meio->informacoes);


    if ( ID_meio == *ID && meio->tipo == tipo)
    {
        return meio;
    }
    else if (ID_meio != -1 && ID_meio < *ID && meio->proximo != NULL)
    {
        return busca_binaria_recursiva(meio->proximo, fim, ID, tipo);
    }
    else if (ID_meio > *ID && meio->anterior != NULL)
    {
        return busca_binaria_recursiva(inicio, meio->anterior, ID, tipo);
    }

    return NULL;
}

Lista_duplamente_encadeada *busca_binaria_duplamente_encadeada(Lista_duplamente_encadeada *lista, int ID, TIPO_INFO tipo)
{
    if (lista == NULL)
    {
        return NULL;
    }

    Lista_duplamente_encadeada *inicio = lista;
    Lista_duplamente_encadeada *fim = NULL;

    Lista_duplamente_encadeada *meio = buscar_meio(inicio, fim);
    short int ID_meio = retornar_ID_convertido(meio->tipo, meio->informacoes);

    if ( ID_meio == ID && meio->tipo == tipo)
    {
        return meio;
    }
    else if (ID_meio < ID && meio->proximo != NULL)
    {
        return busca_binaria_recursiva(meio->proximo, fim, &ID, tipo);
    }
    else if (ID_meio > ID && meio->anterior != NULL)
    {
        return busca_binaria_recursiva(inicio, meio->anterior, &ID, tipo);
    }

    return NULL;
}
