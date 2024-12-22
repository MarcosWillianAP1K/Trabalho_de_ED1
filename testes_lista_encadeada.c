#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
// #include "BIBLIOTECAS/Struct_info.h"


int main()
{
    // Lista_encadeada *lista = NULL;

    INFO *teste = escrever_dados();

    // adicionar_elemento_encadeada(&lista, &teste);

    // printf("ID: %d\n", lista->informacoes->ID);
    // printf("Nome: %s\n", lista->informacoes->nome);
    // printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    // printf("Minuto: %d\n", lista->informacoes->minuto);
    // printf("Hora: %d\n", lista->informacoes->hora);
    // printf("Dia: %d\n", lista->informacoes->dia);
    // printf("Mes: %d\n", lista->informacoes->mes);
    // printf("Ano: %d\n", lista->informacoes->ano);
    printf("\n");
    printar_dados(teste);


    // liberar_memoria_encadeada(lista);

    liberar_INFO(teste);

    return 0;
}