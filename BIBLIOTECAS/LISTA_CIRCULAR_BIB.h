#include "Struct_info.h"

typedef struct Lista_circular
{
    INFO *info;
    struct Lista_circular *prox;
} Lista_circular;

void adicionar_elemento_circular(Lista_circular **lista, INFO *informacoes);

void printar_lista_circular(Lista_circular *lista);

void remover_primeiro_elemento_circular(Lista_circular **lista);

void remover_elemento_circular_por_ID(Lista_circular **lista, int ID);

void remover_elemento_circular_por_endereco(Lista_circular **lista, Lista_circular *endereco);

Lista_circular *buscar_lista_circular(Lista_circular *lista, int ID);

void liberar_memoria_circular(Lista_circular **lista);
