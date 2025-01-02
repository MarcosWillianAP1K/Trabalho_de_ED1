#include "../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.h"
#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"




#include <stdio.h>
#include <stdlib.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_lista_circular.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c

int main()
{
    Lista_circular *lista = NULL;

    TAREFA *teste1 = criar_tarefa();
    TAREFA *teste2 = criar_tarefa();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");

    teste1->ID = 1;
    teste2->ID = 2;

    adicionar_elemento_circular(&lista, teste1, INFO_TAREFA);
    adicionar_elemento_circular(&lista, teste2, INFO_TAREFA);

    printf("Antes de remover\n");
    printar_lista_circular(lista);

    // remover_primeiro_elemento_circular(&lista);
    remover_elemento_circular_por_endereco(&lista, buscar_lista_circular(lista, 1, INFO_TAREFA), true);

    printf("\nDepois de remover\n");
    printar_lista_circular(lista);

    liberar_memoria_circular(&lista, true);

    return 0;
}