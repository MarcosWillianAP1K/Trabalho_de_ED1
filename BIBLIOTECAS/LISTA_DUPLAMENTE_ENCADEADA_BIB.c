#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"


void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, INFO *informacao, bool frente_tras)
{
    if (*lista == NULL)
    {
        *lista = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
        (*lista)->informacoes = informacao;
        (*lista)->proximo = NULL;
        (*lista)->anterior = NULL;
    }
    else
    {
        Lista_duplamente_encadeada *novo_no = (Lista_duplamente_encadeada *)malloc(sizeof(Lista_duplamente_encadeada));
        novo_no->informacoes = informacao;
        novo_no->proximo = NULL;
        novo_no->anterior = NULL;
        
        if (frente_tras)
        {
            Lista_duplamente_encadeada *aux = *lista;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo_no;
            novo_no->anterior = aux;
        }
        else
        {
            novo_no->proximo = *lista;
            (*lista)->anterior = novo_no;
            *lista = novo_no;
        }
    }
    
}


