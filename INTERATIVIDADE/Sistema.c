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

