#include <stdio.h>
#include <stdlib.h>

#include "Utilidades_sistema.h"


void limpar_buffer()
{
    fflush(stdin);
}

void verificar_alocacao(void *ponteiro)
{
    if (ponteiro == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
}

void verificar_realocacao(void *ponteiro)
{
    if (ponteiro == NULL)
    {
        printf("Erro na realocacao de memoria\n");
        exit(1);
    }
}

void pausar_terminal()
{
    system("pause");
}

void limpar_terminal()
{
    system("cls||clear");
}