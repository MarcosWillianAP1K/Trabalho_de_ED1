#include "../BIBLIOTECAS/LISTA_CIRCULAR_BIB.h"
// #include "../BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"

#include <stdio.h>
#include <stdlib.h>



int main()
{
    Lista_circular *lista = NULL;

    INFO *teste1 = (INFO *)malloc(sizeof(INFO));
    teste1->ID = 0;
    teste1->nome = "teste1";
    teste1->nivel_prioridade = 1;
    teste1->dia = 1;
    teste1->mes = 1;
    teste1->ano = 2025;
    teste1->hora = 1;
    teste1->minuto = 1;

    INFO *teste2 = (INFO *)malloc(sizeof(INFO));
    teste2->ID = 0;
    teste2->nome = "teste2";
    teste2->nivel_prioridade = 2;
    teste2->dia = 2;
    teste2->mes = 2;
    teste2->ano = 2025;
    teste2->hora = 2;
    teste2->minuto = 2;



    adicionar_elemento_circular(&lista, teste1);
    

    adicionar_elemento_circular(&lista, teste2);

    printf("Antes de remover\n");
    printar_lista_circular(lista);

    // remover_primeiro_elemento_circular(&lista);
    remover_elemento_circular_por_endereco(&lista, buscar_lista_circular(lista, 0));

    printf("\nDepois de remover\n");

    printar_lista_circular(lista);


    liberar_memoria_circular(&lista);

    

    return 0;
}