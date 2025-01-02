#include "LISTA_ENCADEADA_BIB.h"
#include "Struct_info.h"


#ifndef PILHA_BIB_H
#define PILHA_BIB_H


typedef struct Pilha
{
    Lista_encadeada *topo;
} Pilha;


void adicionar_elemento_pilha(Pilha **p, INFO *info);

void atribuir_Lista_encadeada_a_pilha(Lista_encadeada *lista, Pilha **p);

INFO *remover_elemento_pilha(Pilha *p);

INFO *remover_elemento_pilha(Pilha *p);

void printar_topo_pilha(Pilha *p);

void printar_pilha(Pilha *p);

void liberar_pilha(Pilha **p);



#endif // PILHA_BIB_H