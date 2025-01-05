#include "Struct_data_hora.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void liberar_DATA_HORA(DATA_HORA **data)
{
    free(*data);
    *data = NULL;
}


bool validar_data(DATA_HORA *data)
{
    time_t t = time(NULL);
    // Pega a data atual
    struct tm tempo_atual = *localtime(&t);

    // Verificar se o mes é valido
    if (data->mes == 2)
    {
        if ((data->ano % 4 == 0 && data->ano % 100 != 0) || data->ano % 400 == 0)
        {
            if (data->dia > 29)
            {
                return false;
            }
        }
        else
        {
            if (data->dia > 28)
            {
                return false;
            }
        }
    }

    if (data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 11)
    {
        if (data->dia > 30)
        {
            return false;
        }
    }

    // Verificar se a data digitada é antes da nossa data atual
    if (data->ano < tempo_atual.tm_year + 1900 || (data->ano == tempo_atual.tm_year + 1900 && data->mes < tempo_atual.tm_mon + 1) || (data->ano == tempo_atual.tm_year + 1900 && data->mes == tempo_atual.tm_mon + 1 && data->dia < tempo_atual.tm_mday))
    {
        return false;
    }

    // Verificar se a hora e minuto é valida
    if ((data->ano == tempo_atual.tm_year + 1900 && data->mes == tempo_atual.tm_mon + 1 && data->dia == tempo_atual.tm_mday) &&
        (data->hora < tempo_atual.tm_hour || (data->hora == tempo_atual.tm_hour && data->minuto < tempo_atual.tm_min)))
    {
        return false;
    }

    return true;
}

void pegar_data_atual(DATA_HORA *data)
{
    time_t t = time(NULL);
    // Pega a data atual
    struct tm tempo_atual = *localtime(&t);

    data->minuto = tempo_atual.tm_min;
    data->hora = tempo_atual.tm_hour;
    data->dia = tempo_atual.tm_mday;
    data->mes = tempo_atual.tm_mon + 1;
    data->ano = tempo_atual.tm_year + 1900;
}

DATA_HORA *criar_data_hora()
{
    DATA_HORA *data = (DATA_HORA *)malloc(sizeof(DATA_HORA));

    if (data == NULL)
    {
        printf("Erro ao alocar memoria para data e hora\n");
        exit(1);
    }

    data->minuto = 0;
    data->hora = 0;
    data->dia = 0;
    data->mes = 0;
    data->ano = 0;

    return data;
}

short int digitar_minuto()
{
    short int n;
    printf("Digite o minuto: ");

    while (scanf("%hd", &n) != 1 || n < 0 || n > 59)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_hora()
{
    short int n;
    printf("Digite a hora: ");

    while (scanf("%hd", &n) != 1 || n < 0 || n > 23)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_dia()
{
    short int n;
    printf("Digite o dia: ");

    while (scanf("%hd", &n) != 1 || n < 0 || n > 31)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_mes()
{
    short int n;
    printf("Digite o mes: ");

    while (scanf("%hd", &n) != 1 || n < 0 || n > 12)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_ano()
{
    time_t t = time(NULL);
    // Pega a data atual
    struct tm tempo_atual = *localtime(&t);

    short int n;
    printf("Digite o ano: ");
    //+500 pra não deixar o usuario colocar um ano muito distante
    while (scanf("%hd", &n) != 1 || n < 0 || n > tempo_atual.tm_year + 1900 + 500)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

