
#include "Struct_info.h"

#ifndef FILA_BIB_H
#define FILA_BIB_H


typedef struct Fila_encadeada
{
    INFO *info;
    struct Fila_encadeada *prox;
} Fila_encadeada;

typedef struct Fila
{
    Fila_encadeada *inicio;
    Fila_encadeada *fim;
} Fila;



#endif // FILA_BIB_H