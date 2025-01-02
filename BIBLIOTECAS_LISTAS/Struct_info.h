

#ifndef STRUCT_INFO_H
#define STRUCT_INFO_H

typedef struct DATA_HORA
{
    signed short int minuto;
    signed short int hora;
    signed short int dia;
    signed short int mes;
    signed short int ano;

} DATA_HORA;

typedef struct INFO
{
    signed short int ID;
    char *nome;
    signed short int nivel_prioridade;
    DATA_HORA *data_entrega;
    DATA_HORA *data_criacao;
} INFO;

DATA_HORA *criar_data_hora();

INFO *criar_info();

void atribuir_nome(char **nome1, char *nome2);

void copiar_infos(INFO **info1, INFO *info2);

void liberar_INFO(INFO **info);

void printar_dados(INFO *info);

INFO *escrever_dados();

void editar_dados(INFO **info);

#endif // STRUCT_INFO_H
