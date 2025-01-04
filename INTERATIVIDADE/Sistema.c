#include <stdio.h>
#include <stdlib.h>

#include "Sistema.h"

void inicializacao_do_sistema(GERENTE **gerente)
{
    (*gerente)->tarefas = NULL;
    (*gerente)->usuarios = NULL;

    // printf("Sistema inicializado\n");
}



void criar_tarefa_gerente(Lista_encadeada **lista)
{
    TAREFA *nova_tarefa = escrever_tarefa();

    if (nova_tarefa == NULL)
    {
        return;
    }

    adicionar_elemento_encadeada_atribuir_ID(lista, nova_tarefa, INFO_TAREFA);
}

void criar_usuario_gerente(Lista_encadeada **lista)
{
    USUARIO *novo_usuario = escrever_usuario();

    if (novo_usuario == NULL)
    {
        return;
    }

    adicionar_elemento_encadeada_atribuir_ID(lista, novo_usuario, INFO_USUARIO);
}


void menu_buscar_tarefa(Lista_encadeada **tarefas)
{
    if (tarefas == NULL)
    {
        printf("Nao ha tarefas\n");
        return;
    }

    char opcao;

    do {
        printf("1. Buscar por ID\n");
        printf("2. Buscar por nome\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch(opcao) {
            case '1':
                // Implementar busca por ID
                break;
            case '2':
                // Implementar busca por nome
                break;
            case '0':
                printf("Voltando...\n");
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }
    } while(opcao != '0');
}



void menu_gerente(GERENTE **gerente)
{
    printf("Menu do gerente\n");
    char opcao;

    do {
        printf("1. Criar tarefa\n");
        printf("2. Buscar tarefa\n");
        printf("3. Listar tarefas\n");
        printf("4. Adicionar usuario\n");
        printf("5. Buscar usuario\n");
        printf("6. Listar usuarios\n");
        printf("7. Trocar de conta\n");
        printf("8. Desfazer ultima acao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch(opcao) {
            case '1':
                criar_tarefa_gerente(&(*gerente)->tarefas);
                break;
            case '2':
                
                
                break;
            case '3':
                
                
                break;
            case '4':
                criar_usuario_gerente(&(*gerente)->usuarios);
                
                break;
            case '5':
                
                
                break;
            case '6':
                
                
                break;
            case '7':
                
                
                break;
            case '8':
                
                break;
            case '0':
                printf("Saindo...\n");
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }
    } while(opcao != '0');
}

void menu_usuario()
{
    printf("Menu do usuario\n");
    char opcao;

    do {
        printf("1. Buscar tarefa\n");
        printf("2. Organizar tarefas\n");
        printf("3. Ver proxima tarefa\n");
        printf("4. Listar tarefas\n");
        printf("5. Trocar de conta\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch(opcao) {
            case '1':
               
                break;
            case '2':
                
                break;
            case '3':
                
                break;
            case '4':
                
                break;
            case '5':
                
                break;
            case '0':
                printf("Saindo...\n");
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }
    } while(opcao != '0');
}


void menu_inicial(GERENTE **gerente)
{
    printf("Menu inicial\n");
    char opcao;

    do {
        printf("1. Gerente\n");
        printf("2. Usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch(opcao) {
            case '1':
                menu_gerente(gerente);
                break;
            case '2':
                menu_usuario();
                break;
            case '0':
                printf("Saindo...\n");
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }
    } while(opcao != '0');
}
