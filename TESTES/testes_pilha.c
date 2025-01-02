#include <stdio.h>
#include "../BIBLIOTECAS_LISTAS/PILHA_BIB.h"

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_pilha.c ../BIBLIOTECAS_SISTEMA/Struct_info.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/PILHA_BIB.c

int main()
{
    Pilha *pilha = NULL;

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

    adicionar_elemento_pilha(&pilha, teste1);
    adicionar_elemento_pilha(&pilha, teste2);

    printf("Topo da pilha\n");
    printar_topo_pilha(pilha);

    adicionar_elemento_pilha(&pilha, teste3);
    adicionar_elemento_pilha(&pilha, teste4);

    printf("\nPilha\n");
    printar_pilha(pilha);

    INFO *removido = remover_elemento_pilha(pilha);

    printf("\nRemovido\n");
    printar_dados(removido);

    printf("\nPilha\n");
    printar_pilha(pilha);

    liberar_pilha(&pilha);


    return 0;
}