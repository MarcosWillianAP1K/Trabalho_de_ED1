#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

#include <stdio.h>
#include <stdlib.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_lista_encadeada.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c

int main()
{
    Lista_encadeada *lista = NULL;

    TAREFA *teste1 = criar_tarefa();
    TAREFA *teste2 = criar_tarefa();
    TAREFA *teste3 = criar_tarefa();
    TAREFA *teste4 = criar_tarefa();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");
    atribuir_nome(&teste3->nome, "teste3");
    atribuir_nome(&teste4->nome, "teste4");

    adicionar_elemento_encadeada(&lista, teste1, INFO_TAREFA);
    adicionar_elemento_encadeada(&lista, teste2, INFO_TAREFA);
    adicionar_elemento_encadeada(&lista, teste3, INFO_TAREFA);
    adicionar_elemento_encadeada(&lista, teste4, INFO_TAREFA);
    

    teste1->ID = 1;
    teste2->ID = 2;
    teste3->ID = 3;
    teste4->ID = 4;

    printf("Antes de remover\n");
    printar_lista_encadeada(lista);

    remover_elemento_encadeada_por_endereco(&lista, buscar_lista_encadeada(lista, 1, INFO_TAREFA), true);
    // remover_elemento_encadeada_por_ID(&lista, 4, INFO_TAREFA, true);
    remover_elemento_encadeada_por_ID(&lista, 3, INFO_TAREFA, true);
    remover_elemento_encadeada_por_ID(&lista, 2, INFO_TAREFA, true);

    printf("Depois de remover\n");

    printar_lista_encadeada(lista);

    liberar_memoria_encadeada(&lista, true);

    return 0;
}