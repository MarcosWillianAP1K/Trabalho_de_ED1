#include "Struct_data_hora.h"
#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"
#include <stdbool.h>

#ifndef STRUCT_INFO_H
#define STRUCT_INFO_H

typedef struct TAREFA
{
    signed short int ID;
    char *nome;
    signed short int nivel_prioridade;
    DATA_HORA *data_entrega;
    DATA_HORA *data_criacao;
    // char *descricao;????

    Lista_encadeada *usuarios_associados;

} TAREFA;

DATA_HORA *criar_data_hora();

TAREFA *criar_tarefa();

void atribuir_nome(char **nome1, char *nome2);

void copiar_tarefas(TAREFA **info1, TAREFA *info2);

void liberar_TAREFA(TAREFA **info);

void printar_tarefa(TAREFA *info);

TAREFA *escrever_tarefa();

TAREFA *editar_tarefa(TAREFA **info, bool liberar_tarefa_antiga); 

#endif // STRUCT_INFO_H
