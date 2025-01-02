#include "../BIBLIOTECAS_LISTAS/FILA_BIB.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

#include <stdio.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_fila.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_LISTAS/FILA_BIB.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c

int main()
{
    Fila *fila = NULL;

    TAREFA *teste1 = criar_tarefa();
    TAREFA *teste2 = criar_tarefa();
    TAREFA *teste3 = criar_tarefa();
    TAREFA *teste4 = criar_tarefa();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");
    atribuir_nome(&teste3->nome, "teste3");
    atribuir_nome(&teste4->nome, "teste4");

    teste1->ID = 1;
    teste2->ID = 2;
    teste3->ID = 3;
    teste4->ID = 4;
    

    adicionar_elemento_fila(&fila, teste1, INFO_TAREFA);
    adicionar_elemento_fila(&fila, teste2, INFO_TAREFA);

    printf("Inicio da fila\n");
    printar_inicio_fila(fila);

    printf("\nFim da fila\n");
    printar_fim_fila(fila);

    adicionar_elemento_fila(&fila, teste3, INFO_TAREFA);
    adicionar_elemento_fila(&fila, teste4, INFO_TAREFA);

    printf("\nFila\n");
    printar_fila(fila);

    //So é possivel atribuir tarefa pq tenho certeza que oq esta sendo adicionado são tarefas
    TAREFA *removido = remover_elemento_fila(fila);

    printf("\nRemovido\n");
    printar_tarefa(removido);

    printf("\nFila\n");
    printar_fila(fila);

    liberar_fila(&fila, true);

    return 0;
}