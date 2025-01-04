#include "Struct_usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

USUARIO *criar_USUARIO()
{
    USUARIO *novo = (USUARIO *)malloc(sizeof(USUARIO));

    novo->login = NULL;
    novo->tarefas_associadas = NULL;
    novo->historico = NULL;

    return novo;
}

char *digitar_login()
{
#define TAM_PADRAO 20

    int tam, cont = 0;
    char *nome = (char *)malloc(TAM_PADRAO * sizeof(char));

    if (nome == NULL)
    {
        return NULL;
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
                free(nome);
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




void liberar_USUARIO(USUARIO **info)
{
    if (*info == NULL)
    {
        return;
    }

    if ((*info)->login != NULL)
    {
        free((*info)->login);
    }

    if ((*info)->tarefas_associadas != NULL)
    {
        liberar_memoria_encadeada(&(*info)->tarefas_associadas, false);
    }

    if ((*info)->historico != NULL)
    {
        liberar_memoria_circular(&(*info)->historico, false);
    }

    free(*info);
    *info = NULL;
}



USUARIO *escrever_usuario()
{
    USUARIO *novo = criar_USUARIO();

    if (novo == NULL)
    {
        return NULL;
    }

    novo->login = digitar_login();

    if (novo->login == NULL)
    {
        liberar_USUARIO(&novo);
        return NULL;
    }

    return novo;
}




