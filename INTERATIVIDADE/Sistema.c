#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Sistema.h"

void msg_saindo()
{
    printf("Saindo...\n");
    Sleep(100);
}

void inicializacao_do_sistema(GERENTE **gerente)
{
    if (*gerente != NULL)
    {
        liberacao_da_memoria_sistema(gerente);
    }
    else
    {
        *gerente = (GERENTE *)malloc(sizeof(GERENTE));
    }

    (*gerente)->tarefas = NULL;
    (*gerente)->usuarios = NULL;

    // printf("Sistema inicializado\n");
}

void liberacao_da_memoria_sistema(GERENTE **gerente)
{
    liberar_memoria_encadeada(&(*gerente)->tarefas, true);
    liberar_memoria_encadeada(&(*gerente)->usuarios, true);

    free(*gerente);
    *gerente = NULL;
}

void criar_tarefa_gerente(Lista_encadeada **lista)
{
    limpar_terminal();
    printf("Criando tarefa tarefa\n\n");
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

void listar_tarefas(Lista_encadeada **lista)
{
    limpar_terminal();

    if (*lista == NULL)
    {
        printf("Nao ha tarefas\n");
        return;
    }

    printar_lista_encadeada(*lista);

    pausar_terminal();
}

void buscar_por_ID(Lista_encadeada **lista, TIPO_INFO tipo)
{
    limpar_terminal();
    if (*lista == NULL)
    {
        printf("Nao ha elementos\n");
        pausar_terminal();
        return;
    }

    short int ID;
    printf("Digite o ID: ");
    while (scanf("%hd", &ID) != 1 || ID < 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    Endereco_lista_encadeada *endereco = buscar_lista_encadeada(*lista, ID, tipo);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Elemento nao encontrado\n");
        liberar_endereco_lista_encadeada(&endereco);
        return;
    }

    printar_INFO_convertido(tipo, endereco->no->informacoes);
    liberar_endereco_lista_encadeada(&endereco);
}

void menu_buscar_tarefa(Lista_encadeada **tarefas)
{
    limpar_terminal();
    if (tarefas == NULL)
    {
        printf("Nao ha tarefas\n");
        pausar_terminal();
        return;
    }

    char opcao;

    do
    {
        printf("1. Buscar por ID\n");
        printf("2. Buscar por nome\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case '1':
            buscar_por_ID(tarefas, INFO_TAREFA);
            break;
        case '2':
            // Implementar busca por nome
            break;
        case '0':

            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }
        limpar_terminal();
    } while (opcao != '0');
}

void menu_gerente(GERENTE **gerente)
{
    char opcao;

    do
    {
        limpar_terminal();
        printf("Menu do gerente\n");
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
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case '1':
            criar_tarefa_gerente(&(*gerente)->tarefas);
            break;
        case '2':
            menu_buscar_tarefa(&(*gerente)->tarefas);
            break;
        case '3':
            listar_tarefas(&(*gerente)->tarefas);
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
            msg_saindo();
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

    } while (opcao != '0');
}

void menu_usuario(USUARIO **usuario)
{
    char opcao;

    do
    {
        limpar_terminal();
        printf("Menu do usuario\n");
        printf("1. Buscar tarefa\n");
        printf("2. Organizar tarefas\n");
        printf("3. Ver proxima tarefa\n");
        printf("4. Listar tarefas\n");
        printf("5. Trocar de conta\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
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
            msg_saindo();
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

    } while (opcao != '0');
}

void menu_inicial(GERENTE **gerente)
{
    char opcao;

    do
    {
        limpar_terminal();
        printf("Menu inicial\n");
        printf("1. Gerente\n");
        printf("2. Usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case '1':
            menu_gerente(gerente);
            break;
        case '2':
            // menu_usuario();
            break;
        case '0':
            msg_saindo();

            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

    } while (opcao != '0');
}
