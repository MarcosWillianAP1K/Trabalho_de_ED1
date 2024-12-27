#include "../BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Lista_duplamente_encadeada *lista = NULL;
    

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
    INFO *teste3 = (INFO *)malloc(sizeof(INFO));
    teste3->ID = 3;
    teste3->nome = "teste3";
    teste3->nivel_prioridade = 3;
    teste3->dia = 3;
    teste3->mes = 3;
    teste3->ano = 2025;
    teste3->hora = 3;
    teste3->minuto = 3;

    INFO *teste4 = (INFO *)malloc(sizeof(INFO));
    teste4->ID = 4;
    teste4->nome = "teste4";
    teste4->nivel_prioridade = 4;
    teste4->dia = 4;
    teste4->mes = 4;
    teste4->ano = 2025;
    teste4->hora = 4;
    teste4->minuto = 4;

    INFO *teste5 = (INFO *)malloc(sizeof(INFO));
    teste5->ID = 5;
    teste5->nome = "teste5";
    teste5->nivel_prioridade = 5;
    teste5->dia = 5;
    teste5->mes = 5;
    teste5->ano = 2025;
    teste5->hora = 5;
    teste5->minuto = 5;

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