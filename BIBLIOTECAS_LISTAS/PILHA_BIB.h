#include "LISTA_ENCADEADA_BIB.h"


#ifndef PILHA_BIB_H
#define PILHA_BIB_H


typedef struct Pilha
{
    Lista_encadeada *topo;
} Pilha;


void adicionar_elemento_pilha(Pilha **p, void *info, TIPO_INFO tipo);

void atribuir_Lista_encadeada_a_pilha(Lista_encadeada *lista, Pilha **p);

void *remover_elemento_pilha(Pilha *p);

void printar_topo_pilha(Pilha *p);

void printar_pilha(Pilha *p);

void liberar_pilha(Pilha **p, bool liberar_info);



#endif // PILHA_BIB_H