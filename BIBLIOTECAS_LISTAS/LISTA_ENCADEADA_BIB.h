
#include "../BIBLIOTECAS_SISTEMA/Struct_info.h"


#ifndef LISTA_ENCADEADA_BIB_H
#define LISTA_ENCADEADA_BIB_H

typedef struct Lista_encadeada
{
    INFO *informacoes;

    struct Lista_encadeada *proximo;

} Lista_encadeada;

void adicionar_elemento_encadeada(Lista_encadeada **lista, INFO *informacoes);

void adicionar_elemento_encadeada_ordernadado_por_ID(Lista_encadeada **lista, INFO *informacoes);

void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID);

void remover_elemento_encadeada_por_endereco(Lista_encadeada **lista, Lista_encadeada *endereco);

void liberar_memoria_encadeada(Lista_encadeada **lista);

void printar_lista_encadeada(Lista_encadeada *list);

Lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID);

#endif // LISTA_ENCADEADA_BIB_H