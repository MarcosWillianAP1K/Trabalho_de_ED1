//Essa biblioteca ordena apenas listas duplamente encadeadas
#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"

#include "../BIBLIOTECAS_SISTEMA/Tipos_bib.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_data_hora.h"
#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"

#ifndef ORDENACAO_BIB_H
#define ORDENACAO_BIB_H

void copiar_lista_para_duplamente(Lista_encadeada *lista, Lista_duplamente_encadeada **lista_dupla);

void copiar_duplamente_para_lista(Lista_duplamente_encadeada *lista, Lista_encadeada **lista_encadeada);

short int comparar_ID(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);

short int comparar_afalbetica(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);

short int comparar_prioridade(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);

short int comparar_data(DATA_HORA *data1, DATA_HORA *data2);

short int comparar_data_entrega(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);

short int comparar_data_criacao(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);

void trocar_nos(Lista_duplamente_encadeada **no1, Lista_duplamente_encadeada **no2);


void bubble_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));

void selection_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));

void insertion_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));

void quick_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));

void merge_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));



#endif // ORDENACAO_BIB_H