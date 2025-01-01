#include "../BIBLIOTECAS/FILA_BIB.h"

#include <stdio.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_fila.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS/FILA_BIB.c

int main()
{
    Fila *fila = NULL;

    INFO *teste1 = criar_info();
    INFO *teste2 = criar_info();
    INFO *teste3 = criar_info();
    INFO *teste4 = criar_info();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");
    atribuir_nome(&teste3->nome, "teste3");
    atribuir_nome(&teste4->nome, "teste4");

    teste1->ID = 1;
    teste2->ID = 2;
    teste3->ID = 3;
    teste4->ID = 4;
    

    adicionar_elemento_fila(&fila, teste1);
    adicionar_elemento_fila(&fila, teste2);

    printf("Inicio da fila\n");
    printar_inicio_fila(fila);

    printf("\nFim da fila\n");
    printar_fim_fila(fila);

    adicionar_elemento_fila(&fila, teste3);
    adicionar_elemento_fila(&fila, teste4);

    printf("\nFila\n");
    printar_fila(fila);

    INFO *removido = remover_elemento_fila(fila);

    printf("\nRemovido\n");
    printar_dados(removido);

    printf("\nFila\n");
    printar_fila(fila);

    liberar_fila(&fila);

    return 0;
}