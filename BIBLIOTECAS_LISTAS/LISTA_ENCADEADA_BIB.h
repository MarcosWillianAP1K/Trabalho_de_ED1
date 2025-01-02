#include "../BIBLIOTECAS_SISTEMA/Tipos_bib.h"

#include <stdbool.h>


#ifndef LISTA_ENCADEADA_BIB_H
#define LISTA_ENCADEADA_BIB_H

typedef struct Lista_encadeada
{
    void *informacoes;
    TIPO_INFO tipo;

    struct Lista_encadeada *proximo;

} Lista_encadeada;
 
void adicionar_elemento_encadeada(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo);

void adicionar_elemento_encadeada_ordernadado_por_ID(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo);

void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID, bool liberar_info);

void remover_elemento_encadeada_por_endereco(Lista_encadeada **lista, Lista_encadeada *endereco, bool liberar_info);

void liberar_memoria_encadeada(Lista_encadeada **lista, bool liberar_info);

void printar_lista_encadeada(Lista_encadeada *list);

Lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID);

#endif // LISTA_ENCADEADA_BIB_H