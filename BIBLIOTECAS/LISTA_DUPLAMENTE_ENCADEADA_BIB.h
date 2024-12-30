#include "Struct_info.h"
#include <stdbool.h>

#ifndef LISTA_DUPLAMENTE_ENCADEADA_BIB_H
#define LISTA_DUPLAMENTE_ENCADEADA_BIB_H



typedef struct Lista_duplamente_encadeada
{
    INFO *informacoes;

    struct Lista_duplamente_encadeada *proximo;
    struct Lista_duplamente_encadeada *anterior;

} Lista_duplamente_encadeada;

void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, INFO *informacao, bool frente_tras);

void adicionar_a_frente_duplamente_encadeada(Lista_duplamente_encadeada **lista, Lista_duplamente_encadeada *novo_no);

void adicionar_atras_duplamente_encadeada(Lista_duplamente_encadeada **lista, Lista_duplamente_encadeada *novo_no);

void printar_lista_duplamente_encadeada(Lista_duplamente_encadeada *lista);

void liberar_memoria_duplamente_encadeada(Lista_duplamente_encadeada **lista);

void remover_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada **lista, int ID);

void remover_elemento_duplamente_encadeada_por_endereco(Lista_duplamente_encadeada *lista, Lista_duplamente_encadeada **inicio);

Lista_duplamente_encadeada *buscar_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada *lista, int ID);

Lista_duplamente_encadeada *busca_binaria_duplamente_encadeada(Lista_duplamente_encadeada *lista, int ID);

#endif // LISTA_DUPLAMENTE_ENCADEADA_BIB_H