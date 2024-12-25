#include "Struct_info.h"


typedef struct Lista_duplamente_encadeada
{
    INFO *informacoes;

    struct Lista_duplamente_encadeada *proximo;
    struct Lista_duplamente_encadeada *anterior;

} Lista_duplamente_encadeada;