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

typedef struct Endereco_lista_encadeada
{
    Lista_encadeada *anterior;
    Lista_encadeada *no;

} Endereco_lista_encadeada;

void liberar_endereco_lista_encadeada(Endereco_lista_encadeada **endereco);


void liberar_no_encadeada(Lista_encadeada *no, bool liberar_info);
 
void adicionar_elemento_encadeada_atribuir_ID(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo);

void adicionar_elemento_encadeada(Lista_encadeada **lista, void *informacoes, TIPO_INFO tipo);

void remover_elemento_encadeada_por_ID(Lista_encadeada **lista, int ID, TIPO_INFO tipo ,bool liberar_info);

void remover_elemento_encadeada_por_endereco(Endereco_lista_encadeada *endereco, Lista_encadeada **lista, bool liberar_info);

void liberar_memoria_encadeada(Lista_encadeada **lista, bool liberar_info);

void printar_lista_encadeada(Lista_encadeada *list);

Endereco_lista_encadeada *buscar_lista_encadeada_por_nome(Lista_encadeada *list, char *nome, TIPO_INFO tipo);

Endereco_lista_encadeada *buscar_lista_encadeada(Lista_encadeada *list, int ID, TIPO_INFO tipo);

void copiar_lista_encadeada(Lista_encadeada **lista1, Lista_encadeada *lista2);


#endif // LISTA_ENCADEADA_BIB_H