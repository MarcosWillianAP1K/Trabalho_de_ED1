#include "Struct_info.h"

typedef struct Lista_circular
{
    INFO *info;
    struct Lista_circular *prox;
} Lista_circular;



void adicionar_elemento_circular(Lista_circular **lista, INFO *informacoes);

void printar_lista_circular(Lista_circular *lista);


void remover_primeiro_elemento_circular(Lista_circular **lista);


void liberar_memoria_circular(Lista_circular **lista);
