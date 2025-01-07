#include <stdbool.h>
#include "Struct_data_hora.h"

#ifndef Tipos_bib_h
#define Tipos_bib_h


typedef enum TIPO_INFO{
    INFO_TAREFA,
    INFO_USUARIO,
    INFO_GERENTE
} TIPO_INFO;

void error_tipo();

void conferir_tipos(TIPO_INFO tipo1, TIPO_INFO tipo2, void *info1, void *info2);

void *retorna_info_convertida(TIPO_INFO tipo, void *info);


short int retornar_ID_convertido(TIPO_INFO tipo, void *info);

char *retornar_nome_convertido(TIPO_INFO tipo, void *info);

DATA_HORA *retornar_data_entrega_convertida(TIPO_INFO tipo, void *info);

DATA_HORA *retornar_data_criacao_convertida(TIPO_INFO tipo, void *info);

DATA_HORA *retornar_data_conclusao_convertida(TIPO_INFO tipo, void *info);

void atribuir_ID_convertido(TIPO_INFO tipo, void *info, short int ID);

void liberar_INFO_convertido(TIPO_INFO tipo, void **info);

void printar_INFO_convertido(TIPO_INFO tipo, void *info);

void *editar_INFO_convertido(TIPO_INFO tipo, void **info, bool liberar_info_antiga);


#endif // Tipos_bib_h


