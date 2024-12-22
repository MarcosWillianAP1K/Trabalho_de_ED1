#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct_info.h"

void limpar_buffer()
{
    while (getchar() != '\n');
}

void digitar_ID(short int *n)
{
    printf("Digite o ID: ");

    while (scanf("%hd", &n) != 1 && n < 0)
    {
        printf("Digite um valor válido: ");
        limpar_buffer();
    }

    getchar();
}


void digitar_nome(char *nome)
{
#define TAM_PADRAO 20

    int tam, cont = 0;
    nome = (char *)malloc(TAM_PADRAO * sizeof(char));

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
                printf("Erro na alocação de memória\n");
                return;
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
}


void digitar_nivel_prioridade(short int *n)
{
    printf("Digite o nível de prioridade (0 a 5): ");

    while (scanf("%hd", &n) != 1 && n < 0 && n > 5)
    {
        printf("Digite um valor válido: ");
        limpar_buffer();
    }

    getchar();
}


void digitar_minuto(short int *n)
{
    printf("Digite o minuto: ");

    while (scanf("%hd", &n) != 1 && n < 0 && n > 59)
    {
        printf("Digite um valor válido: ");
        limpar_buffer();
    }
    
    getchar();
}





void escrever_dados(INFO *info)
{
    digitar_ID(info->ID);

    digitar_nome(info->nome);

    digitar_nivel_prioridade(info->nivel_prioridade);
}

void liberar_INFO(INFO *info)
{
    free(info->nome);
    free(info);
}