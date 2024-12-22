#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Struct_info.h"


void liberar_INFO(INFO *info)
{
    free(info->nome);
    free(info);
}




// Sequencia de funções para digitar os dados
void limpar_buffer()
{
    fflush(stdin);
}

short int digitar_ID()
{
    short int n;
    printf("Digite o ID: ");

    while (scanf("%hd", &n) != 1 || n < 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

<<<<<<< HEAD
    limpar_buffer();

    return n;
=======
    //AIAI TESTANDO NE
    getchar();
>>>>>>> 045c84c98225183a8fd7568815504e80f5f0dd04
}

char *digitar_nome()
{
#define TAM_PADRAO 20

    int tam, cont = 0;
    char *nome = (char *)malloc(TAM_PADRAO * sizeof(char));

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
                printf("Erro na alocacao de memoria\n");
                return NULL;
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
    short int n;
    printf("Digite o ano: ");

    while (scanf("%hd", &n) != 1 || n < 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}



// Ave maria, terror de juliana
bool validar_data(short int dia, short int mes, short int ano)
{
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

    return true;
}


bool verificar(INFO **info)
{
    if(!validar_data((*info)->dia, (*info)->mes, (*info)->ano))
    {
        printf("\nData invalida.\nDeseja reescrever a data? (s/n): ");
        char c;
        scanf("%c", &c);
        limpar_buffer();
        
        

        if(c == 's' || c == 'S')
        {
            return true;
        }
        else
        {
            liberar_INFO(*info);
            *info = NULL;
            printf("\nOperacao cancelada.\n");
        }


    }


    return false;
}


INFO *escrever_dados()
{
    INFO *info = (INFO *)malloc(sizeof(INFO));

    
        info->ID = digitar_ID();

        info->nome = digitar_nome();

        info->nivel_prioridade = digitar_nivel_prioridade();

        info->minuto = digitar_minuto();

        info->hora = digitar_hora();

    do
    {

        info->dia = digitar_dia();

        info->mes = digitar_mes();

        info->ano = digitar_ano();

    } while (verificar(&info));

    return info;
}



void printar_dados(INFO *info)
{
    if (info == NULL)
    {
        return;
    }
    

    printf("ID: %d\n", info->ID);
    printf("Nome: %s\n", info->nome);
    printf("Nivel de Prioridade: %d\n", info->nivel_prioridade);
    printf("Minuto: %d\n", info->minuto);
    printf("Hora: %d\n", info->hora);
    printf("Dia: %d\n", info->dia);
    printf("Mes: %d\n", info->mes);
    printf("Ano: %d\n", info->ano);
}
