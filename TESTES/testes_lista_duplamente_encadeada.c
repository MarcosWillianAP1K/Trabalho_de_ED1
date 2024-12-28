#include "../BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_lista_duplamente_encadeada.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c

int main()
{
    Lista_duplamente_encadeada *lista = NULL;

    INFO *teste1 = criar_info();
    INFO *teste2 = criar_info();
    INFO *teste3 = criar_info();
    INFO *teste4 = criar_info();
    INFO *teste5 = criar_info();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");
    atribuir_nome(&teste3->nome, "teste3");
    atribuir_nome(&teste4->nome, "teste4");
    atribuir_nome(&teste5->nome, "teste5");

    teste1->ID = 1;
    teste2->ID = 2;
    teste3->ID = 3;
    teste4->ID = 4;
    teste5->ID = 5;

    adicionar_elemento_duplamente_encadeada(&lista, teste1, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste2, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste3, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste4, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste5, true);

    printf("Antes de remover\n");
    printar_lista_duplamente_encadeada(lista);

    // remover_elemento_duplamente_encadeada_por_ID(&lista, 5);

    // printf("Depois de remover\n");

    // printar_lista_duplamente_encadeada(lista);

    remover_elemento_duplamente_encadeada_por_endereco(busca_binaria_duplamente_encadeada(lista, 6), &lista);
    remover_elemento_duplamente_encadeada_por_endereco(busca_binaria_duplamente_encadeada(lista, 2), &lista);
    remover_elemento_duplamente_encadeada_por_endereco(busca_binaria_duplamente_encadeada(lista, 5), &lista);

    printf("Depois de remover\n");

    printar_lista_duplamente_encadeada(lista);

    liberar_memoria_duplamente_encadeada(&lista);

    return 0;
}