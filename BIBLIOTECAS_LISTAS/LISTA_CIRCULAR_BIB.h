#include "../BIBLIOTECAS_SISTEMA/Tipos_bib.h"
#include <stdbool.h>

#ifndef LISTA_CIRCULAR_BIB_H
#define LISTA_CIRCULAR_BIB_H

typedef struct Lista_circular
{
    void *info;
    TIPO_INFO tipo;
    struct Lista_circular *prox;
} Lista_circular;

short int adicionar_elemento_circular(Lista_circular **lista, void *informacoes, TIPO_INFO tipo);

void printar_lista_circular(Lista_circular *lista);

void remover_primeiro_elemento_circular(Lista_circular **lista, bool liberar_info);

void remover_elemento_circular_por_ID(Lista_circular **lista, int ID, TIPO_INFO tipo ,bool liberar_info);

void remover_elemento_circular_por_endereco(Lista_circular **lista, Lista_circular *endereco, bool liberar_info);

Lista_circular *buscar_lista_circular(Lista_circular *lista, int ID, TIPO_INFO tipo);

void liberar_memoria_circular(Lista_circular **lista, bool liberar_info);

void copiar_lista_circular(Lista_circular *lista1, Lista_circular **lista2);

#endif // LISTA_CIRCULAR_BIB_H
