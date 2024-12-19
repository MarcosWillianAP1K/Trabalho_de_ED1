#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"


int main()
{
    Lista_encadeada *lista = NULL;

    INFO teste;
    teste.ID = 1;
    teste.nome = "teste";
    teste.nivel_prioridade = 1;
    teste.minuto = 1;
    teste.hora = 1;
    teste.dia = 1;
    teste.mes = 1;
    teste.ano = 1;

    adicionar_elemento_encadeada(&lista, &teste);

    printf("ID: %d\n", lista->informacoes->ID);
    printf("Nome: %s\n", lista->informacoes->nome);
    printf("Nivel de Prioridade: %d\n", lista->informacoes->nivel_prioridade);
    printf("Minuto: %d\n", lista->informacoes->minuto);
    printf("Hora: %d\n", lista->informacoes->hora);
    printf("Dia: %d\n", lista->informacoes->dia);
    printf("Mes: %d\n", lista->informacoes->mes);
    printf("Ano: %d\n", lista->informacoes->ano);


    liberar_memoria_encadeada(&lista);

    return 0;
}