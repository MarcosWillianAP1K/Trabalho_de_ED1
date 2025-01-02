#include "../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"
#include "../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.h"

#include <stdio.h>

//comando para compilar
// gcc -o teste -pthread ../TESTES/testes_ordenacao.c ../BIBLIOTECAS_LISTAS/Struct_info.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c

int main()
{
    Lista_duplamente_encadeada *lista = NULL;

    INFO *teste1 = criar_info();
    INFO *teste2 = criar_info();
    INFO *teste3 = criar_info();
    INFO *teste4 = criar_info();

    atribuir_nome(&teste1->nome, "teste1");
    atribuir_nome(&teste2->nome, "teste2");
    atribuir_nome(&teste3->nome, "teste3");
    atribuir_nome(&teste4->nome, "teste4");

    teste1->ID = 4;
    teste2->ID = 3;
    teste3->ID = 2;
    teste4->ID = 1;

    teste1->nivel_prioridade = 1;
    teste2->nivel_prioridade = 2;
    teste3->nivel_prioridade = 3;
    teste4->nivel_prioridade = 4;

    adicionar_elemento_duplamente_encadeada(&lista, teste1, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste2, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste3, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste4, true);

    // printf("Antes de ordenar\n");
    // printar_lista_duplamente_encadeada(lista);

    // bubble_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    // selection_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    // insertion_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    // quick_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    merge_sort_lista_duplamente_encadeada(&lista, comparar_ID);

    printf("Depois de ordenar\n");
    printar_lista_duplamente_encadeada(lista);


    liberar_memoria_duplamente_encadeada(&lista);

    return 0; 
}