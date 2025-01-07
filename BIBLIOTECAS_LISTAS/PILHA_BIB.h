#include "../BIBLIOTECAS_SISTEMA/Tipos_bib.h"

#ifndef PILHA_BIB_H
#define PILHA_BIB_H

// Este tipo de pilha é especial para o sistema, ele vai ser exclusivo para o sistema


typedef struct Pilha_encadeada
{
    void *ultimo_estado;
    TIPO_INFO tipo;
    struct Pilha_encadeada *proximo;
} Pilha_encadeada;

typedef struct Pilha
{
    Pilha_encadeada *topo;

} Pilha;

void adicionar_elemento_pilha(Pilha **p, void *info, TIPO_INFO tipo);


void *remover_elemento_pilha(Pilha *p);

void printar_topo_pilha(Pilha *p);

void printar_pilha(Pilha *p);

void liberar_pilha(Pilha **p, bool liberar_info);

#endif // PILHA_BIB_H