#include "../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"
#include "../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.h"

#include "../BIBLIOTECAS_SISTEMA/Struct_tarefa.h"

#include <stdio.h>

//comando para compilar
// gcc -o teste -pthread ../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.c ../BLIOTECAS_SISTEMA/Struct_usuario.c ../BIBLIOTECAS_SISTEMA/Utilidades_sistema.c ../TESTES/testes_ordenacao.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c

int main()
{
    Lista_duplamente_encadeada *lista = NULL;

    TAREFA *teste1 = criar_tarefa();
    TAREFA *teste2 = criar_tarefa();
    TAREFA *teste3 = criar_tarefa();
    TAREFA *teste4 = criar_tarefa();

    atribuir_nome(&teste1->nome, "b");
    atribuir_nome(&teste2->nome, "a");
    atribuir_nome(&teste3->nome, "c");
    atribuir_nome(&teste4->nome, "d");

    teste1->ID = 4;
    teste2->ID = 3;
    teste3->ID = 2;
    teste4->ID = 1;

    teste1->nivel_prioridade = 1;
    teste2->nivel_prioridade = 2;
    teste3->nivel_prioridade = 3;
    teste4->nivel_prioridade = 4;

    adicionar_elemento_duplamente_encadeada(&lista, teste1, INFO_TAREFA,true);
    adicionar_elemento_duplamente_encadeada(&lista, teste2, INFO_TAREFA, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste3, INFO_TAREFA, true);
    adicionar_elemento_duplamente_encadeada(&lista, teste4, INFO_TAREFA, true);

    // printf("Antes de ordenar\n");
    // printar_lista_duplamente_encadeada(lista);

    // bubble_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    selection_sort_lista_duplamente_encadeada(&lista, comparar_afalbetica);
    // insertion_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    // quick_sort_lista_duplamente_encadeada(&lista, comparar_ID);
    // merge_sort_lista_duplamente_encadeada(&lista, comparar_ID);

    printf("Depois de ordenar\n");
    printar_lista_duplamente_encadeada(lista);


    liberar_memoria_duplamente_encadeada(&lista, true);

    return 0; 
}