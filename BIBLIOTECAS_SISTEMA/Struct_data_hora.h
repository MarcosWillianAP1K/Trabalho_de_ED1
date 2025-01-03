#include <stdbool.h>

#ifndef STRUCT_DATA_HORA_H
#define STRUCT_DATA_HORA_H

typedef struct DATA_HORA
{
    signed short int minuto;
    signed short int hora;
    signed short int dia;
    signed short int mes;
    signed short int ano;

} DATA_HORA;

void liberar_DATA_HORA(DATA_HORA **data);

void limpar_buffer();

bool validar_data(DATA_HORA *data);

void pegar_data_atual(DATA_HORA *data);

DATA_HORA *criar_data_hora();

short int digitar_minuto();

short int digitar_hora();

short int digitar_dia();

short int digitar_mes();

short int digitar_ano();


#endif // STRUCT_DATA_HORA_H