#include <stdio.h>
#include <stdlib.h>
#include "Struct_info.h"


typedef struct Lista_encadeada
{
    struct INFO *informacoes;

    struct Lista_encadeada *proximo;

} Lista_encadeada;






// void *iniciar();



void adicionar_elemento_encadeada(Lista_encadeada **lista, INFO *informacoes);


// void criar_lista_encadeada(Lista_encadeada **lista, int tam);

// void criar_lista_aleatoria_encadeada(Lista_encadeada **lista, int tam);



void liberar_memoria_encadeada(Lista_encadeada **lista);



// void printar_lista_encadeada(Lista_encadeada *list);

// void printar_lista_modificado_encadeada(Lista_encadeada *list);

