#include "../BIBLIOTECAS/LISTA_CIRCULAR_BIB.h"
// #include "../BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"

#include <stdio.h>
#include <stdlib.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_lista_circular.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_CIRCULAR_BIB.c

int main()
{
    Lista_circular *lista = NULL;

    INFO *teste1 = criar_info();
    INFO *teste2 = criar_info();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");

    teste1->ID = 1;
    teste2->ID = 2;

    adicionar_elemento_circular(&lista, teste1);
    adicionar_elemento_circular(&lista, teste2);

    printf("Antes de remover\n");
    printar_lista_circular(lista);

    // remover_primeiro_elemento_circular(&lista);
    remover_elemento_circular_por_endereco(&lista, buscar_lista_circular(lista, 1));

    printf("\nDepois de remover\n");
    printar_lista_circular(lista);

    liberar_memoria_circular(&lista);

    return 0;
}