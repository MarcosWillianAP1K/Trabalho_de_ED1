#include <stdio.h>
#include "../BIBLIOTECAS_LISTAS/PILHA_BIB.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_pilha.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_LISTAS/PILHA_BIB.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c

int main()
{
    Pilha *pilha = NULL;

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

    adicionar_elemento_pilha(&pilha, teste1, INFO_TAREFA);
    adicionar_elemento_pilha(&pilha, teste2, INFO_TAREFA);

    printf("Topo da pilha\n");
    printar_topo_pilha(pilha);

    adicionar_elemento_pilha(&pilha, teste3, INFO_TAREFA);
    adicionar_elemento_pilha(&pilha, teste4, INFO_TAREFA);

    printf("\nPilha\n");
    printar_pilha(pilha);

    TAREFA *removido = remover_elemento_pilha(pilha);

    printf("\nRemovido\n");
    printar_tarefa(removido);

    printf("\nPilha\n");
    printar_pilha(pilha);

    liberar_pilha(&pilha, true);


    return 0;
}