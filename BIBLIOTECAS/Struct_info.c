#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Struct_info.h"

void liberar_INFO(INFO **info)
{
    free((*info)->nome);
    free((*info)->data_entrega);
    free((*info)->data_criacao);
    free(*info);
    *info = NULL;
}

void limpar_buffer()
{
    fflush(stdin);
}

bool selecionar_s_ou_n()
{
    char c;

    do
    {
        limpar_buffer();
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

// Ave maria, terror de juliana
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

bool confirmar_dados(INFO *info)
{
    printar_dados(info);

    printf("\nDeseja confirmar os dados? (s/n): ");

    return selecionar_s_ou_n();
}

bool reescrever_dados()
{
    printf("\nDeseja reescrever os dados? (s/n): ");

    return selecionar_s_ou_n();
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

char *criar_nome(int tam)
{
    char *nome = (char *)malloc((tam + 1) * sizeof(char));

    verificar_alocacao(nome);

    return nome;
}



DATA_HORA *criar_data_hora()
{
    DATA_HORA *data = (DATA_HORA *)malloc(sizeof(DATA_HORA));

    verificar_alocacao(data);

    data->minuto = 0;
    data->hora = 0;
    data->dia = 0;
    data->mes = 0;
    data->ano = 0;

    return data;
}

INFO *criar_info()
{
    INFO *info = (INFO *)malloc(sizeof(INFO));

    verificar_alocacao(info);

    info->ID = 0;
    info->nome = criar_nome(1);
    info->nome[0] = '\0';
    info->nivel_prioridade = 0;
    info->data_criacao = criar_data_hora();
    info->data_entrega = criar_data_hora();

    pegar_data_atual(info->data_criacao);

    return info;
}



void atribuir_nome(char **nome1, char *nome2)
{
    if (nome2 == NULL)
    {
        return;
    }

    free(*nome1);
    *nome1 = criar_nome(strlen(nome2));
    strcpy(*nome1, nome2);
}

void copiar_infos(INFO **info1, INFO *info2)
{

    if (info2 == NULL)
    {
        return;
    }

    if (*info1 == NULL)
    {
        *info1 = criar_info();
    }

    
    (*info1)->ID = info2->ID;
    atribuir_nome(&(*info1)->nome, info2->nome);

    (*info1)->nivel_prioridade = info2->nivel_prioridade;

    (*info1)->data_entrega->minuto = info2->data_entrega->minuto;
    (*info1)->data_entrega->hora = info2->data_entrega->hora;
    (*info1)->data_entrega->dia = info2->data_entrega->dia;
    (*info1)->data_entrega->mes = info2->data_entrega->mes;
    (*info1)->data_entrega->ano = info2->data_entrega->ano;

    (*info1)->data_criacao->minuto = info2->data_criacao->minuto;
    (*info1)->data_criacao->hora = info2->data_criacao->hora;
    (*info1)->data_criacao->dia = info2->data_criacao->dia;
    (*info1)->data_criacao->mes = info2->data_criacao->mes;
    (*info1)->data_criacao->ano = info2->data_criacao->ano;
}

void printar_dados(INFO *info)
{
    if (info == NULL)
    {
        return;
    }

    printf("ID: %03d\n", info->ID);
    printf("Nome: %s\n", info->nome);
    printf("Nivel de Prioridade: %d\n", info->nivel_prioridade);
    printf("Data de Entrega: %02d/%02d/%04d\n", info->data_entrega->dia, info->data_entrega->mes, info->data_entrega->ano);
    printf("Hora de Entrega: %02d:%02d\n", info->data_entrega->hora, info->data_entrega->minuto);
    printf("Data de Criacao: %02d/%02d/%04d\n", info->data_criacao->dia, info->data_criacao->mes, info->data_criacao->ano);
    printf("Hora de Criacao: %02d:%02d\n", info->data_criacao->hora, info->data_criacao->minuto);
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
    char *nome = criar_nome(TAM_PADRAO);

    printf("Digite o nome: ");

    if (fgets(nome, TAM_PADRAO * sizeof(char), stdin) != NULL)
    {

        tam = strlen(nome);

        while (nome[tam - 1] != '\n')
        {
            cont++;
            char *temp = (char *)realloc(nome, (TAM_PADRAO * cont) * sizeof(char));

            verificar_realocacao(temp);

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



// Seguinte, essa função permite escrever os dados e retorna um ponteiro com o endereços dos dados, ja tem as blindagens necessarias
INFO *escrever_dados()
{

    INFO *info = criar_info();

    while(1)
    {
        // info->ID = digitar_ID();

        // Sera atribuido o ID correto depois
        info->ID = 0;

        atribuir_nome(&info->nome, digitar_nome());

        info->nivel_prioridade = digitar_nivel_prioridade();

        while (1)
        {
            info->data_entrega->minuto = digitar_minuto();

            info->data_entrega->hora = digitar_hora();

            info->data_entrega->dia = digitar_dia();

            info->data_entrega->mes = digitar_mes();

            info->data_entrega->ano = digitar_ano();

            if (!validar_data(info->data_entrega))
            {
                printf("\nData/hora invalida.");
                if (!reescrever_dados())
                {
                    liberar_INFO(&info);
                    printf("Operacao cancelada.\n");
                    return NULL;
                }
            }
            else
            {
                break;
            }
        }
        printf("\n");

        if (confirmar_dados(info))
        {
            pegar_data_atual(info->data_criacao);
            break;
        }

        if (!reescrever_dados())
        {
            liberar_INFO(&info);
            printf("Operacao cancelada.\n");
            break;
        }
    }

    return info;
}

void editar_dados(INFO **info)
{
    if (*info == NULL)
    {
        printf("\nNao ha dados para editar.\n");
        return;
    }
    

    INFO *nova_info = criar_info();

    copiar_infos(&nova_info, *info);

    char c;

    do
    {
        printar_dados(nova_info);
        // printar_dados(*info);

        printf("\nSelecione o que deseja editar:\n");
        printf("1 - Nome\n");
        printf("2 - Nivel de Prioridade\n");
        printf("3 - Data\n");
        printf("4 - Hora\n");
        printf("5 - Confirmar\n");
        printf("6 - Cancelar\n");

        limpar_buffer();
        scanf("%c", &c);
        limpar_buffer();

        switch (c)
        {
        case '1':
            atribuir_nome(&nova_info->nome, digitar_nome());
            break;

        case '2':
            nova_info->nivel_prioridade = digitar_nivel_prioridade();
            break;

        case '3':
        {
            DATA_HORA *data = criar_data_hora();

            data->minuto = nova_info->data_entrega->minuto;
            data->hora = nova_info->data_entrega->hora;

            while (1)
            {
                data->dia = digitar_dia();

                data->mes = digitar_mes();

                data->ano = digitar_ano();

                if (validar_data(data))
                {
                    nova_info->data_entrega->dia = data->dia;
                    nova_info->data_entrega->mes = data->mes;
                    nova_info->data_entrega->ano = data->ano;
                    free(data);
                    break;
                }
                else
                {
                    printf("\nData invalida.");
                    printf("\nDeseja reescrever a data? (s/n): ");

                    if (!selecionar_s_ou_n())
                    {
                        free(data);
                        break;
                    }
                }
            }
        }
        break;

        case '4':
        {
            DATA_HORA *data = criar_data_hora();

            data->dia = nova_info->data_entrega->dia;
            data->mes = nova_info->data_entrega->mes;
            data->ano = nova_info->data_entrega->ano;

            while (1)
            {
                data->hora = digitar_hora();

                data->minuto = digitar_minuto();

                if (validar_data(data))
                {
                    nova_info->data_entrega->hora = data->hora;
                    nova_info->data_entrega->minuto = data->minuto;
                    free(data);
                    break;
                }
                else
                {
                    printf("\nHora invalida.");
                    printf("\nDeseja reescrever a hora? (s/n): ");

                    if (!selecionar_s_ou_n())
                    {
                        free(data);
                        break;
                    }
                }
            }
        }

        break;

        case '5':
            printf("\n");
            if (confirmar_dados(nova_info))
            {
                copiar_infos(info, nova_info);
                liberar_INFO(&nova_info);
                printf("Dados alterados com sucesso.\n");
            }
            else
            {

                c = '0';
            }

            break;

        case '6':

            printf("Deseja cancelar a operacao? (s/n): ");

            if (selecionar_s_ou_n())
            {
                liberar_INFO(&nova_info);
                printf("Operacao cancelada.\n");
            }
            else
            {
                c = '0';
            }

            break;

        default:
            printf("Digite um valor valido: ");
            break;
        }

    } while (c != '5' && c != '6');
}
