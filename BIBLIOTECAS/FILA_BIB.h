
#include "Struct_info.h"

#ifndef FILA_BIB_H
#define FILA_BIB_H


typedef struct Fila_encadeada
{
    INFO *info;
    struct Fila_encadeada *proximo;
} Fila_encadeada;

typedef struct Fila
{
    Fila_encadeada *inicio;
    Fila_encadeada *fim;
} Fila;

void adicionar_elemento_fila(Fila *f, INFO *info);

INFO *remover_elemento_fila(Fila *f);

void liberar_fila(Fila **f);


#endif // FILA_BIB_H