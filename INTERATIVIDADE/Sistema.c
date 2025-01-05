#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "Sistema.h"

GERENTE **geral = NULL;

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

void editar_INFO(void **info, TIPO_INFO tipo)
{
    limpar_terminal();
    
    // Mexer no desfazer aqui, tem o problema se n editar nada, vai ter um desfazer
    editar_INFO_convertido(tipo, info, true);
    
}

void excluir_INFO(Endereco_lista_encadeada *endereco, TIPO_INFO tipo)
{
    if (endereco == NULL)
    {
        printf("Nao foi possivel encontrar a informacao\n");
        pausar_terminal();
        return;
    }

    //Mexer no desfazer aqui

    if (tipo == INFO_TAREFA)
    {
        TAREFA *tarefa = (TAREFA *)endereco->no->informacoes;
        Lista_encadeada *usuarios = tarefa->usuarios_associados;

        if (usuarios != NULL)
        {

            while (usuarios != NULL)
            {
                USUARIO *usuario = (USUARIO *)usuarios->informacoes;

                if (usuario != NULL)
                {
                    remover_elemento_encadeada_por_ID(&usuario->tarefas_associadas, tarefa->ID, INFO_TAREFA, false);
                }
                usuarios = usuarios->proximo;
            }

            liberar_memoria_encadeada(&tarefa->usuarios_associados, false);
        }

        remover_elemento_encadeada_por_endereco(endereco, &(*geral)->tarefas, true);
    }
    else if (tipo == INFO_USUARIO)
    {
        USUARIO *usuario = (USUARIO *)endereco->no->informacoes;
        Lista_encadeada *tarefas = usuario->tarefas_associadas;

        if (tarefas != NULL)
        {
            while (tarefas != NULL)
            {
                TAREFA *tarefa = (TAREFA *)tarefas->informacoes;
                remover_elemento_encadeada_por_ID(&tarefa->usuarios_associados, usuario->ID, INFO_USUARIO, false);
                tarefas = tarefas->proximo;
            }

            liberar_memoria_encadeada(&usuario->tarefas_associadas, false);
        }

        remover_elemento_encadeada_por_endereco(endereco, &(*geral)->usuarios, true);
    }
}

void menu_oque_fazer_com_a_INFO(Endereco_lista_encadeada *endereco, TIPO_INFO tipo)
{
    char opcao;

    do
    {
        limpar_terminal();
        printar_INFO_convertido(tipo, endereco->no->informacoes);

        printf("O que deseja fazer com a informacao?\n");

        printf("1. Editar\n");
        printf("2. Excluir\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case '1':
            editar_INFO(&endereco->no->informacoes, tipo);
            break;
        case '2':
            excluir_INFO(endereco, tipo);
            break;
        case '0':
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }
    } while (opcao != '0');
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

void menu_buscar(TIPO_INFO tipo)
{
    limpar_terminal();
    if (tipo == INFO_TAREFA)
    {
        if ((*geral)->tarefas == NULL)
        {
            printf("Nao ha tarefas\n");
            pausar_terminal();
            return;
        }
    }
    else
    {
        if ((*geral)->usuarios == NULL)
        {
            printf("Nao ha usuarios\n");
            pausar_terminal();
            return;
        }
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
            menu_oque_fazer_com_a_INFO(buscar_lista_encadeada((*geral)->tarefas, digitar_ID(), tipo), tipo);
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

void menu_gerente()
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
            criar_tarefa_gerente(&(*geral)->tarefas);
            break;
        case '2':
            menu_buscar(INFO_TAREFA);
            break;
        case '3':
            listar_tarefas(&(*geral)->tarefas);
            break;
        case '4':
            criar_usuario_gerente(&(*geral)->usuarios);

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

void menu_usuario(USUARIO *usuario)
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
    geral = gerente;

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
            menu_gerente();
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
