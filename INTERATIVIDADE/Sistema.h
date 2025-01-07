#include "Biblioteca_geral.h"




#ifndef SISTEMA_H
#define SISTEMA_H
#include <stdbool.h>
typedef enum TIPO_CONTA{
    CONTA_GERENTE,
    CONTA_USUARIO
} TIPO_CONTA;

void inicializacao_do_sistema(GERENTE **gerente, bool com_testes);

void liberacao_da_memoria_sistema(GERENTE **gerente);

void menu_inicial(GERENTE **gerente);

void copiar_sistema_para_outro_sistema(GERENTE *gerente_copiado, GERENTE **gerente_recebedor);


#endif
