#include "Struct_usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilidades_sistema.h"

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
        liberar_memoria_circular(&(*info)->historico, true);
    }

    free(*info);
    *info = NULL;
}

USUARIO *escrever_usuario()
{
    limpar_terminal();
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

void printar_historico(USUARIO *info)
{
    if (info == NULL)
    {
        return;
    }

    if (info->historico == NULL)
    {
        printf("Historico vazio\n");
        return;
    }
    

    printf("Historico de tarefas: \n");

    Lista_circular *aux = info->historico;

    do
    {
        printar_INFO_convertido(INFO_TAREFA, aux->info);
        aux = aux->prox;
    } while (aux != info->historico);
    
}

void printar_usuario(USUARIO *info)
{
    if (info == NULL)
    {
        return;
    }

    printf("ID: %03d\n", info->ID);
    printf("Login: %s\n", info->login);
    
    if (info->tarefas_associadas != NULL)
    {
        printf("IDs de tarefas associadas: \n");
        
        Lista_encadeada *aux = info->tarefas_associadas;

        while (aux != NULL)
        {
            printf("%03hd  ", retornar_ID_convertido(INFO_TAREFA, aux->informacoes));
            aux = aux->proximo;
        }
        printf("\n");
    }
    else
    {
        printf("Nenhuma tarefa associada\n");
    }


}

void copiar_USUARIO(USUARIO *original, USUARIO **copia)
{
    if (original == NULL)
    {
        return;
    }


    if (*copia != NULL)
    {
        liberar_USUARIO(copia);
    }
    *copia = criar_USUARIO();

    (*copia)->ID = original->ID;
    (*copia)->login = (char *)malloc((strlen(original->login) + 1) * sizeof(char));
    strcpy((*copia)->login, original->login);

    if (original->tarefas_associadas != NULL)
    {
        copiar_lista_encadeada(&(*copia)->tarefas_associadas, original->tarefas_associadas);
    }

    if (original->historico != NULL)
    {
        copiar_lista_circular(original->historico, &(*copia)->historico);
    }
}
