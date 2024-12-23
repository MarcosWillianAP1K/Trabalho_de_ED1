#include "../BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>
// #include "BIBLIOTECAS/Struct_info.h"


int main()
{
    Lista_encadeada *lista = NULL;

    INFO *teste1 = (INFO *)malloc(sizeof(INFO));
    teste1->ID = 1;
    teste1->nome = "teste1";
    teste1->nivel_prioridade = 1;
    teste1->dia = 1;
    teste1->mes = 1;
    teste1->ano = 2025;
    teste1->hora = 1;
    teste1->minuto = 1;

    INFO *teste2 = (INFO *)malloc(sizeof(INFO));
    teste2->ID = 2;
    teste2->nome = "teste2";
    teste2->nivel_prioridade = 2;
    teste2->dia = 2;
    teste2->mes = 2;
    teste2->ano = 2025;
    teste2->hora = 2;
    teste2->minuto = 2;



    adicionar_elemento_encadeada(&lista, teste1);
    

    adicionar_elemento_encadeada(&lista, teste2);

    printf("Antes de remover\n");
    printar_lista_encadeada(lista);


    remover_elemento_encadeada_por_endereco(&lista, buscar_lista_encadeada(lista, 1));

    printf("Depois de remover\n");

    printar_lista_encadeada(lista);


    liberar_memoria_encadeada(&lista);

    

    return 0;
}