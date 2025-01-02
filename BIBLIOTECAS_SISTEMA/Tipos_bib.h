


#ifndef Tipos_bib_h
#define Tipos_bib_h


typedef enum {
    INFO_TAREFA,
    INFO_USUARIO
} TIPO_INFO;

void error_tipo();

void conferir_tipos(TIPO_INFO tipo1, TIPO_INFO tipo2, void *info1, void *info2);


short int retornar_ID_convertido(TIPO_INFO tipo, void *info);

void atribuir_ID_convertido(TIPO_INFO tipo, void *info, short int ID);

void liberar_INFO_convertido(TIPO_INFO tipo, void **info);

void printar_INFO_convertido(TIPO_INFO tipo, void *info);


#endif // Tipos_bib_h


