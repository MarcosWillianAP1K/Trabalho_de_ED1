#include "Struct_info.h"
#include <stdbool.h>

typedef struct Lista_duplamente_encadeada
{
    INFO *informacoes;

    struct Lista_duplamente_encadeada *proximo;
    struct Lista_duplamente_encadeada *anterior;

} Lista_duplamente_encadeada;

void adicionar_elemento_duplamente_encadeada(Lista_duplamente_encadeada **lista, INFO *informacao, bool frente_tras);

void printar_lista_duplamente_encadeada(Lista_duplamente_encadeada *lista);

void liberar_memoria_duplamente_encadeada(Lista_duplamente_encadeada **lista);

void remover_elemento_duplamente_encadeada_por_ID(Lista_duplamente_encadeada **lista , int ID);
