#include <stdio.h>
#include <stdlib.h>

typedef struct Lista_vetores
{
    int *vetor;
    struct Lista_vetores *proximo;
} Lista_vetores;


typedef struct Lista
{
    int numero;
    struct Lista *proximo;
} Lista;

typedef struct Lista_de_strings
{
    char string[20];
    struct Lista_de_strings *proximo;
} Lista_de_strings;



void *iniciar();



void adicionar_elemento(Lista **lista, int valor);

void adicionar_nomes(Lista_de_strings **lista, char *string);

void adicionar_vetor(Lista_vetores **lista, int *vetor);



void criar_lista(Lista **lista, int tam);

void criar_lista_aleatoria(Lista **lista, int tam);



void liberar_memoria(Lista **lista);

void liberar_memoria_nomes(Lista_de_strings **lista);

void liberar_memoria_vetor(Lista_vetores **lista);



void printar_lista(Lista *list);

void printar_lista_nomes(Lista_de_strings *list);

void printar_lista_modificado(Lista *list);

void printar_lista_vetor(Lista_vetores *list);
