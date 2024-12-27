#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Struct_info.h"

void printar_dados(INFO *info)
{
    if (info == NULL)
    {
        return;
    }

    printf("ID: %d\n", info->ID);
    printf("Nome: %s\n", info->nome);
    printf("Nivel de Prioridade: %d\n", info->nivel_prioridade);
    printf("Data: %02d/%02d/%04d\n", info->dia, info->mes, info->ano);
    printf("Hora: %02d:%02d\n", info->hora, info->minuto);
}

void limpar_buffer()
{
    fflush(stdin);
}

void liberar_INFO(INFO **info)
{
    free((*info)->nome);
    free(*info);
    *info = NULL;
}

bool selecionar_s_ou_n()
{
    char c;

    do
    {
        scanf("%c", &c);
        limpar_buffer();

        if (c == 's' || c == 'S')
        {
            return true;
        }

        if (c != 'n' && c != 'N' && c != 's' && c != 'S')
        {
            printf("Digite um valor valido: ");
        }

    } while (c != 'n' && c != 'N' && c != 's' && c != 'S');

    return false;
}

// Sequencia de funções para digitar os dados

// Digitar ID e apenas para testes, não sera implementado no produto final
short int digitar_ID()
{
    short int n;
    printf("Digite o ID: ");

    while (scanf("%hd", &n) != 1 || n < 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

char *digitar_nome()
{
#define TAM_PADRAO 20

    int tam, cont = 0;
    char *nome = (char *)malloc(TAM_PADRAO * sizeof(char));

    if (nome == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    printf("Digite o nome: ");

    if (fgets(nome, TAM_PADRAO * sizeof(char), stdin) != NULL)
    {

        tam = strlen(nome);

        while (nome[tam - 1] != '\n')
        {
            cont++;
            char *temp = (char *)realloc(nome, (TAM_PADRAO * cont) * sizeof(char));

            if (temp == NULL)
            {
                printf("Erro na realocacao de memoria\n");
                exit(1);
            }

            nome = temp;

            if (fgets(nome + tam, ((TAM_PADRAO * cont) * sizeof(char)) - tam, stdin) == NULL)
            {
                break;
            }

            tam = strlen(nome);
        }
    }

    tam = strlen(nome);

    if (nome[tam - 1] == '\n')
    {
        nome[tam - 1] = '\0';
    }

    // printf("\nNome: %s\n\nFoi realocado %d\nTamanho %d\n\n", nome, cont, tam);

    return nome;
}

short int digitar_nivel_prioridade()
{
    short int n;
    printf("Digite o nivel de prioridade (0 a 5): ");

    while (scanf("%hd", &n) != 1 || n < 0 || n > 5)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
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

// Ave maria, terror de juliana
bool validar_data(short int dia, short int mes, short int ano, short int hora, short int minuto)
{
    time_t t = time(NULL);
    // Pega a data atual
    struct tm tempo_atual = *localtime(&t);

    // Verificar se o mes é valido
    if (mes == 2)
    {
        if (ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0)
        {
            if (dia > 29)
            {
                return false;
            }
        }
        else
        {
            if (dia > 28)
            {
                return false;
            }
        }
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia > 30)
        {
            return false;
        }
    }

    // Verificar se a data digitada é antes da nossa data atual
    if (ano < tempo_atual.tm_year + 1900 || (ano == tempo_atual.tm_year + 1900 && mes < tempo_atual.tm_mon + 1) || (ano == tempo_atual.tm_year + 1900 && mes == tempo_atual.tm_mon + 1 && dia < tempo_atual.tm_mday))
    {
        return false;
    }

    // Verificar se a hora e minuto é valida
    if ((ano == tempo_atual.tm_year + 1900 && mes == tempo_atual.tm_mon + 1 && dia == tempo_atual.tm_mday) &&
        (hora < tempo_atual.tm_hour || (hora == tempo_atual.tm_hour && minuto < tempo_atual.tm_min)))
    {
        return false;
    }

    return true;
}

bool verificar(INFO **info)
{
    if (!validar_data((*info)->dia, (*info)->mes, (*info)->ano, (*info)->hora, (*info)->minuto))
    {
        printf("\nData invalida.");
        printf("\nDeseja reescrever a data? (s/n): ");

        if (selecionar_s_ou_n())
        {
            return true;
        }
        else
        {
            liberar_INFO(info);
            printf("\nOperacao cancelada.\n");
        }
    }

    return false;
}

bool confirmar_dados(INFO **info)
{
    printf("\nDeseja confirmar os dados? (s/n): ");

    if (selecionar_s_ou_n())
    {
        return true;
    }

    return false;
}

bool reescrever_dados(INFO **info)
{
    printf("\nDeseja reescrever os dados? (s/n): ");

    if (selecionar_s_ou_n())
    {
        return true;
    }

    return false;
}

// Seguinte, essa função permite escrever os dados e retorna um ponteiro com o endereços dos dados, ja tem as blindagens necessarias
INFO *escrever_dados()
{

    INFO *info = (INFO *)malloc(sizeof(INFO));
    bool confirma = true;
    do
    {
        do
        {

            // info->ID = digitar_ID();

            // Sera atribuido o ID correto depois
            info->ID = 0;

            free(info->nome);
            info->nome = digitar_nome();

            info->nivel_prioridade = digitar_nivel_prioridade();

            do
            {
                info->minuto = digitar_minuto();

                info->hora = digitar_hora();

                info->dia = digitar_dia();

                info->mes = digitar_mes();

                info->ano = digitar_ano();

            } while (verificar(&info));

            confirma = true;

            if (info != NULL)
            {
                printf("\n");
                printar_dados(info);
                confirma = confirmar_dados(&info);
            }

        } while (info == NULL && confirma);
    } while (!confirma && reescrever_dados(&info));

    return info;
}

void editar_dados(INFO **info)
{
    INFO *nova_info = malloc(sizeof(INFO));

    char c;

    do
    {   
        printar_dados(*info);

        printf("\nSelecione o que deseja editar:\n");
        printf("1 - Nome\n");
        printf("2 - Nivel de Prioridade\n");
        printf("3 - Data\n");
        printf("4 - Hora\n");
        printf("5 - Confirmar\n");
        printf("5 - Cancelar\n");

        scanf("%c", &c);
        limpar_buffer();

        switch (c)
        {
        case '1':
            free(nova_info->nome);
            nova_info->nome = digitar_nome();
            break;

        case '2':
            nova_info->nivel_prioridade = digitar_nivel_prioridade();
            break;

        case '3':
            do
            {
                nova_info->minuto = digitar_minuto();

                nova_info->hora = digitar_hora();

                nova_info->dia = digitar_dia();

                nova_info->mes = digitar_mes();

                nova_info->ano = digitar_ano();

            } while (verificar(&nova_info));
            break;

        case '4':
            nova_info->hora = digitar_hora();
            break;

        case '5':

            printf("\n");
            printar_dados(nova_info);
            if (confirmar_dados(&nova_info))
            {
                liberar_INFO(info);
                *info = nova_info;
            }

            break;

        case '6':

            liberar_INFO(&nova_info);
            printf("Operacao cancelada.\n");
            return;

        default:
            printf("Digite um valor valido: ");
            break;
        }

    } while (c != '5' && c != '6');
}
