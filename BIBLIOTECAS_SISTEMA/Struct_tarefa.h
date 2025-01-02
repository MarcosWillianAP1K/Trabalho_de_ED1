

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

typedef struct TAREFA
{
    signed short int ID;
    char *nome;
    signed short int nivel_prioridade;
    DATA_HORA *data_entrega;
    DATA_HORA *data_criacao;
} TAREFA;

DATA_HORA *criar_data_hora();

TAREFA *criar_tarefa();

void atribuir_nome(char **nome1, char *nome2);

void copiar_tarefas(TAREFA **info1, TAREFA *info2);

void liberar_TAREFA(TAREFA **info);

void printar_tarefa(TAREFA *info);

TAREFA *escrever_tarefa();

void editar_tarefa(TAREFA **info);

#endif // STRUCT_INFO_H
