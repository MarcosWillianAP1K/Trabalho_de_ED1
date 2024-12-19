#include <stdio.h>
#include <stdlib.h>



typedef struct Lista_encadeada
{
    signed short int ID;
    char *nome;

    signed short int nivel_prioridade;

    signed short int minuto;
    signed short int hora;
    signed short int dia;
    signed short int mes;
    signed short int ano;

    struct Lista_encadeada *proximo;
} Lista_encadeada;




// void *iniciar();



void adicionar_elemento(Lista_encadeada **lista, int valor);




void criar_lista(Lista_encadeada **lista, int tam);

void criar_lista_aleatoria(Lista_encadeada **lista, int tam);



void liberar_memoria(Lista_encadeada **lista);



void printar_lista(Lista_encadeada *list);

void printar_lista_modificado(Lista_encadeada *list);

