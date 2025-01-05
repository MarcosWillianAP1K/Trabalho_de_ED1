#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <pthread.h>

#include "Sistema.h"

GERENTE **geral = NULL;

void msg_saindo()
{
    printf("Saindo...\n");
    Sleep(100);
}

void adicionar_testes(GERENTE **gerente)
{
    TAREFA *tarefa1 = criar_tarefa();
    TAREFA *tarefa2 = criar_tarefa();

    atribuir_nome(&tarefa1->nome, "tarefa1");
    atribuir_nome(&tarefa2->nome, "tarefa2");

    tarefa1->ID = 1;
    tarefa2->ID = 2;

    tarefa1->nivel_prioridade = 1;
    tarefa2->nivel_prioridade = 2;

    adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->tarefas, tarefa1, INFO_TAREFA);
    adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->tarefas, tarefa2, INFO_TAREFA);

    // USUARIO *usuario1 = criar_usuario();
    // USUARIO *usuario2 = criar_usuario();

    // atribuir_nome(&usuario1->login, "usuario1");
    // atribuir_nome(&usuario2->login, "usuario2");


    // usuario1->ID = 1;
    // usuario2->ID = 2;

    // adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->usuarios, usuario1, INFO_USUARIO);
    // adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->usuarios, usuario2, INFO_USUARIO);





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

    adicionar_testes(gerente);

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

void editar_INFO(void **info, TIPO_INFO tipo)
{
    limpar_terminal();

    // Mexer no desfazer aqui, tem o problema se n editar nada, vai ter um desfazer
    editar_INFO_convertido(tipo, info, true);
}

void excluir_INFO(Endereco_lista_encadeada *endereco, TIPO_INFO tipo)
{
    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar a informacao\n");
        pausar_terminal();
        return;
    }

    // Mexer no desfazer aqui

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

    liberar_endereco_lista_encadeada(&endereco);
}

void menu_oque_fazer_com_a_INFO(void *info, TIPO_INFO tipo)
{
    char opcao;

    do
    {
        limpar_terminal();
        printar_INFO_convertido(tipo, info);

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
            editar_INFO(&info, tipo);
            break;
        case '2':
            if (tipo == INFO_TAREFA)
            {
                excluir_INFO(buscar_lista_encadeada_por_nome((*geral)->tarefas, retornar_nome_convertido(tipo, info), tipo), tipo);
            }
            else
            {
                excluir_INFO(buscar_lista_encadeada_por_nome((*geral)->usuarios, retornar_nome_convertido(tipo, info), tipo), tipo);
            }
            break;
        case '0':
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }
    } while (opcao != '0' && opcao != '2');
}

typedef struct ordenacao_thread
{
    Lista_duplamente_encadeada **lista;
    void (*metodo)(Lista_duplamente_encadeada **inicio, short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2));
    short int (*comparar)(void *info1, void *info2, TIPO_INFO tipo1, TIPO_INFO tipo2);
} ordenacao_thread;

void *adicionar_na_duplamente_thread(void *arg)
{
    if (arg == NULL)
    {
        return NULL;
    }

    Lista_encadeada *lista = (Lista_encadeada *)arg;
    Lista_duplamente_encadeada *lista_dupla = NULL;

    while (lista != NULL)
    {
        adicionar_elemento_duplamente_encadeada(&lista_dupla, lista->informacoes, lista->tipo, true);
        lista = lista->proximo;
    }

    return (void *)lista_dupla;
}

void *liberar_duplamente_thread(void *arg)
{
    if (arg == NULL)
    {
        return NULL;
    }

    Lista_duplamente_encadeada *lista = (Lista_duplamente_encadeada *)arg;

    liberar_memoria_duplamente_encadeada(&lista, false);

    return NULL;
}

void *ordenar_duplamente_thread(void *arg)
{
    if (arg == NULL)
    {
        return NULL;
    }

    ordenacao_thread *ordenacao = (ordenacao_thread *)arg;

    if (ordenacao->lista == NULL || *ordenacao->lista == NULL)
    {
        return NULL;
    }

    if (ordenacao->metodo != NULL)
    {
        ordenacao->metodo(ordenacao->lista, ordenacao->comparar);
    }

    return NULL;
}

void listar(Lista_encadeada **lista, TIPO_INFO tipo)
{
#define quant_threads 5

    limpar_terminal();

    if (*lista == NULL)
    {
        printf("Nao ha informacoes\n");
        pausar_terminal();
        return;
    }

    pthread_t thread[quant_threads];

    Lista_duplamente_encadeada *lista_dupla[quant_threads];

    for (int i = 0; i < quant_threads; i++)
    {
        lista_dupla[i] = NULL;
        pthread_create(&thread[i], NULL, adicionar_na_duplamente_thread, (void *)*lista);
    }

    for (int i = 0; i < quant_threads; i++)
    {
        pthread_join(thread[i], (void **)&lista_dupla[i]);
    }

    ordenacao_thread ordenacao[quant_threads];

    for (int i = 0; i < quant_threads; i++)
    {
        ordenacao[i].lista = &lista_dupla[i];
    }

    ordenacao[0].metodo = bubble_sort_lista_duplamente_encadeada;
    ordenacao[1].metodo = selection_sort_lista_duplamente_encadeada;
    ordenacao[2].metodo = insertion_sort_lista_duplamente_encadeada;
    ordenacao[3].metodo = quick_sort_lista_duplamente_encadeada;
    ordenacao[4].metodo = merge_sort_lista_duplamente_encadeada;

    ordenacao[0].comparar = comparar_ID;
    ordenacao[1].comparar = comparar_afalbetica;
    ordenacao[2].comparar = comparar_prioridade;
    ordenacao[3].comparar = comparar_data_criacao;
    ordenacao[4].comparar = comparar_data_entrega;

    for (int i = 0; i < quant_threads; i++)
    {
        pthread_create(&thread[i], NULL, ordenar_duplamente_thread, (void *)&ordenacao[i]);
    }

    for (int i = 0; i < quant_threads; i++)
    {
        pthread_join(thread[i], NULL);
    }

    short int opcao;
    bool listagem = false;
    short int qual_lista = 0;
        limpar_terminal();
    do
    {
        
        printf("Como deseja listar as informacoes?\n");
        printf("1. Por ID\n");
        printf("2. Alfabetica\n");
        printf("3. Por prioridade\n");
        printf("4. Data de criacao\n");
        printf("5. Data de entrega\n");
        printf("6. Selecionar por ID\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();

        while (scanf("%hd", &opcao) != 1)
        {
            printf("Digite um valor valido: ");
            limpar_buffer();
        }
        
        

        switch (opcao)
        {
        case 1:
        limpar_terminal();
            printar_lista_duplamente_encadeada(lista_dupla[0]);
            listagem = true;
            qual_lista = opcao - 1;
            break;
        case 2:
        limpar_terminal();
            printar_lista_duplamente_encadeada(lista_dupla[1]);
            listagem = true;
            qual_lista = opcao - 1;
            break;
        case 3:
        limpar_terminal();
            printar_lista_duplamente_encadeada(lista_dupla[2]);
            listagem = true;
            qual_lista = opcao - 1;
            break;
        case 4:
        limpar_terminal();
            printar_lista_duplamente_encadeada(lista_dupla[3]);
            listagem = true;
            qual_lista = opcao - 1;
            break;
        case 5:
        limpar_terminal();
            printar_lista_duplamente_encadeada(lista_dupla[4]);
            listagem = true;
            qual_lista = opcao - 1;
            break;

        case 6:

            if (listagem)
            {
                Lista_duplamente_encadeada *aux = NULL;
                printf("p1\n");

                if (opcao == 1)
                {
                    printf("p2\n");
                    aux = busca_binaria_duplamente_encadeada(lista_dupla[0], digitar_ID(), tipo);
                    printf("p3\n");
                }
                else
                {
                    printf("p3\n");
                    aux = buscar_elemento_duplamente_encadeada_por_ID(lista_dupla[0], digitar_ID(), tipo);
                    printf("p4\n");
                }
                    printf("p5\n");
                if (aux != NULL)
                {
                    printf("p6\n");
                    menu_oque_fazer_com_a_INFO(aux->informacoes, tipo);
                    printf("p7\n");
                }
                else
                {
                    printf("ID nao encontrado\n");
                    pausar_terminal();
                }
                printf("p8\n");
            }
            else
            {
                printf("Selecione um metodo de listagem primeiro\n");
                pausar_terminal();
            }
            limpar_terminal();

            break;

        case 0:
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            limpar_terminal();
            break;
        }

        
    } while (opcao != 0 && opcao != 6);

    for (int i = 0; i < quant_threads; i++)
    {
        pthread_create(&thread[i], NULL, liberar_duplamente_thread, (void *)lista_dupla[i]);
    }

    for (int i = 0; i < quant_threads; i++)
    {
        pthread_join(thread[i], NULL);
    }
}

void buscar_nomes_parecidos(Lista_encadeada *list, char *nome, TIPO_INFO tipo)
{
    if (list == NULL)
    {
        return;
    }
    // printar_lista_encadeada(list);
    // pausar_terminal();
    // limpar_terminal();

    Lista_encadeada *aux = NULL;

    while (list != NULL)
    {
        Endereco_lista_encadeada *endereco = buscar_lista_encadeada_por_nome(list, nome, tipo);
        list = endereco->no;

        // printf("Informacoes encontradas:\n");
        // printar_INFO_convertido(tipo, endereco->no->informacoes);

        if (endereco->no != NULL)
        {
            // printf("adicionou\n");
            adicionar_elemento_encadeada(&aux, endereco->no->informacoes, tipo);
            list = endereco->no->proximo;
        }
        liberar_endereco_lista_encadeada(&endereco);
    }

    if (aux == NULL)
    {
        printf("Nao foi possivel encontrar informacoes\n");
        pausar_terminal();
        return;
    }

    do
    {
        printf("Informacoes encontradas\n");
        printar_lista_encadeada(aux);

        printf("Digite o ID da informacao que desejas.\n");

        Endereco_lista_encadeada *endereco = buscar_lista_encadeada(aux, digitar_ID(), tipo);

        if (endereco != NULL && endereco->no != NULL)
        {
            menu_oque_fazer_com_a_INFO(endereco->no->informacoes, tipo);
            liberar_memoria_encadeada(&aux, false);
        }
        else
        {
            printf("Digite um ID valido\n");
            pausar_terminal();
        }
        liberar_endereco_lista_encadeada(&endereco);

    } while (aux != NULL);
}

void buscar_por_ID(Lista_encadeada *list, short int ID, TIPO_INFO tipo)
{
    Endereco_lista_encadeada *endereco = buscar_lista_encadeada(list, ID, tipo);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar a informacao\n");
        pausar_terminal();
        return;
    }

    menu_oque_fazer_com_a_INFO(endereco->no->informacoes, tipo);

    liberar_endereco_lista_encadeada(&endereco);
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

            if (tipo == INFO_TAREFA)
            {
                buscar_por_ID((*geral)->tarefas, digitar_ID(), tipo);
            }
            else
            {
                buscar_por_ID((*geral)->usuarios, digitar_ID(), tipo);
            }
            break;
        case '2':
        {
            char *nome = digitar_nome();

            if (nome == NULL)
            {
                break;
            }

            if (tipo == INFO_TAREFA)
            {
                buscar_nomes_parecidos((*geral)->tarefas, nome, tipo);
            }
            else
            {
                buscar_nomes_parecidos((*geral)->usuarios, nome, tipo);
            }

            free(nome);
        }
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
        printf("4. Atribuir tarefa\n");
        printf("5. Adicionar usuario\n");
        printf("6. Buscar usuario\n");
        printf("7. Listar usuarios\n");
        printf("8. Trocar de conta\n");
        printf("9. Desfazer ultima acao\n");
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
            listar(&(*geral)->tarefas, INFO_TAREFA);
            break;
        case '4':
            // Implementar função de atribuir tarefa
            break;
        case '5':
            criar_usuario_gerente(&(*geral)->usuarios);
            break;
        case '6':
            menu_buscar(INFO_USUARIO);
            break;
        case '7':
            listar(&(*geral)->usuarios, INFO_USUARIO);
            break;
        case '8':
            // Implementar função de trocar de conta
            break;
        case '9':
            // Implementar função de desfazer última ação
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
