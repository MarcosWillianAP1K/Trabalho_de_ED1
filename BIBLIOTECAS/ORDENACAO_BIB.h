//Essa biblioteca ordena apenas listas duplamente encadeadas
#include "LISTA_DUPLAMENTE_ENCADEADA_BIB.h"

#ifndef ORDENACAO_BIB_H
#define ORDENACAO_BIB_H


short int comparar_ID(INFO *info1, INFO *info2);

short int comparar_afalbetica(INFO *info1, INFO *info2);

short int comparar_prioridade(INFO *info1, INFO *info2);

short int comparar_data(DATA_HORA *data1, DATA_HORA *data2);

short int comparar_data_entrega(INFO *info1, INFO *info2);

short int comparar_data_criacao(INFO *info1, INFO *info2);



void bubble_sort_lista_duplamente_encadeada(Lista_duplamente_encadeada *inicio, short int (*comparar)(INFO *info1, INFO *info2));




#endif // ORDENACAO_BIB_H