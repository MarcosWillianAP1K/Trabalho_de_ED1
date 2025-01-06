#include "Biblioteca_geral.h"



#ifndef SISTEMA_H
#define SISTEMA_H

typedef enum TIPO_CONTA{
    CONTA_GERENTE,
    CONTA_USUARIO
} TIPO_CONTA;

void inicializacao_do_sistema(GERENTE **gerente);

void liberacao_da_memoria_sistema(GERENTE **gerente);

void menu_inicial(GERENTE **gerente);


#endif
