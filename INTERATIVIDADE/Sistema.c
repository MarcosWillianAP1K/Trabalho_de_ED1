#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <pthread.h>

#include "Sistema.h"

GERENTE **geral = NULL;
USUARIO *usuario_logado = NULL;
Fila *tarefas_do_usuario = NULL;
char ultima_organizacao_do_usuario = '1';

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

    USUARIO *usuario1 = criar_USUARIO();
    USUARIO *usuario2 = criar_USUARIO();

    atribuir_nome(&usuario1->login, "usuario1");
    atribuir_nome(&usuario2->login, "usuario2");

    usuario1->ID = 1;
    usuario2->ID = 2;

    adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->usuarios, usuario1, INFO_USUARIO);
    adicionar_elemento_encadeada_atribuir_ID(&(*gerente)->usuarios, usuario2, INFO_USUARIO);
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

    if (tipo == INFO_USUARIO)
    {
        printf("\nEsta versao do sistema nao e possivel editar usuario.\n");
        printf("Sera lancado na proxima atulizacao em breve\n");
        pausar_terminal();
    }

    // Mexer no desfazer aqui, tem o problema se n editar nada, vai ter um desfazer
    editar_INFO_convertido(tipo, info, true);
}

void excluir_INFO(Endereco_lista_encadeada *endereco, TIPO_INFO tipo, bool liberar_info)
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

        remover_elemento_encadeada_por_endereco(endereco, &(*geral)->tarefas, liberar_info);
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

        remover_elemento_encadeada_por_endereco(endereco, &(*geral)->usuarios, liberar_info);
    }

    liberar_endereco_lista_encadeada(&endereco);
}

void atribuir_tarefa_usuario(TAREFA *tarefa, Lista_encadeada *usuarios)
{
    limpar_terminal();

    if (usuarios == NULL)
    {
        printf("Nao ha usuarios\n");
        pausar_terminal();
        return;
    }
    printar_lista_encadeada(usuarios);

    printf("Atribuir tarefa a um usuario\n");

    printf("Digite o ID do usuario: ");
    short int ID = digitar_ID();

    Endereco_lista_encadeada *endereco = buscar_lista_encadeada(usuarios, ID, INFO_USUARIO);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar o usuario\n");
        pausar_terminal();
        return;
    }

    USUARIO *usuario = (USUARIO *)endereco->no->informacoes;

    if (usuario == NULL)
    {
        printf("Nao foi possivel encontrar o usuario\n");
        pausar_terminal();
        return;
    }

    adicionar_elemento_encadeada(&usuario->tarefas_associadas, tarefa, INFO_TAREFA);
    adicionar_elemento_encadeada(&tarefa->usuarios_associados, usuario, INFO_USUARIO);

    liberar_endereco_lista_encadeada(&endereco);
}

void atribuir_usuarior_tarefa(USUARIO *usuario, Lista_encadeada *tarefas)
{
    limpar_terminal();

    if (tarefas == NULL)
    {
        printf("Nao ha tarefas\n");
        pausar_terminal();
        return;
    }
    printar_lista_encadeada(tarefas);

    printf("Atribuir usuario a uma tarefa\n");

    printf("Digite o ID da tarefa: ");
    short int ID = digitar_ID();

    Endereco_lista_encadeada *endereco = buscar_lista_encadeada(tarefas, ID, INFO_TAREFA);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar a tarefa\n");
        pausar_terminal();
        return;
    }

    TAREFA *tarefa = (TAREFA *)endereco->no->informacoes;

    if (tarefa == NULL)
    {
        printf("Nao foi possivel encontrar a tarefa\n");
        pausar_terminal();
        return;
    }

    adicionar_elemento_encadeada(&usuario->tarefas_associadas, tarefa, INFO_TAREFA);
    adicionar_elemento_encadeada(&tarefa->usuarios_associados, usuario, INFO_USUARIO);

    liberar_endereco_lista_encadeada(&endereco);
}

void reoganizar_tarefas(Fila **f, char *opcao)
{
    if (*f == NULL || (*f)->inicio == NULL)
    {
        printf("Nao ha tarefas\n");
        pausar_terminal();
        return;
    }

    Lista_duplamente_encadeada *aux = NULL;

    copiar_lista_para_duplamente((*f)->inicio, &aux);
    

    switch (*opcao)
    {
    case '1':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_ID);
        break;
    case '2':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_afalbetica);
        break;
    case '3':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_prioridade);
        break;
    case '4':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_data_criacao);
        break;
    case '5':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_data_entrega);
        break;
    default:
        printf("\nOpcao invalida, tente novamente.\n");
        liberar_memoria_duplamente_encadeada(&aux, false);
        pausar_terminal();
        return;
        break;
    }


    liberar_fila(f, false);
    Lista_encadeada *fila_encadeada = NULL;
    copiar_duplamente_para_lista(aux, &fila_encadeada);
    atribuir_Lista_encadeada_a_fila(fila_encadeada, f);
    liberar_memoria_duplamente_encadeada(&aux, false);

}

void concluir_tarefa(TAREFA *tarefa)
{
    if (tarefa == NULL)
    {
        return;
    }

    if (adicionar_elemento_circular(&usuario_logado->historico, tarefa, INFO_TAREFA) > 10)
    {
        remover_primeiro_elemento_circular(&usuario_logado->historico, true);
    }

    excluir_INFO(buscar_lista_encadeada((*geral)->tarefas, tarefa->ID, INFO_TAREFA), INFO_TAREFA, false);

    reoganizar_tarefas(&tarefas_do_usuario, &ultima_organizacao_do_usuario);

}

void menu_oque_fazer_com_a_INFO_usuario(void *info, TIPO_INFO tipo)
{
    char opcao;

    do
    {
        limpar_terminal();
        printar_INFO_convertido(tipo, info);

        printf("O que deseja fazer com a informacao?\n");

        printf("1. Concluir tarefa\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        limpar_buffer();
        scanf(" %c", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case '1':
            concluir_tarefa((TAREFA *)info);
            break;
        case '0':
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }
    } while (opcao != '0' && opcao != '1');
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

        if (tipo == INFO_TAREFA)
        {
            printf("3. Atribuir a um usuario\n");
        }

        if (tipo == INFO_USUARIO)
        {
            printf("3. Atribuir uma tarefa\n");
        }

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
                excluir_INFO(buscar_lista_encadeada((*geral)->tarefas, retornar_ID_convertido(tipo, info), tipo), tipo, true);
            }
            else
            {

                excluir_INFO(buscar_lista_encadeada((*geral)->usuarios, retornar_ID_convertido(tipo, info), tipo), tipo, true);
            }
            break;
        case '3':

            if (tipo == INFO_TAREFA)
            {
                atribuir_tarefa_usuario((TAREFA *)info, (*geral)->usuarios);
            }
            else
            {
                atribuir_usuarior_tarefa((USUARIO *)info, (*geral)->tarefas);
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

    copiar_lista_para_duplamente(lista, &lista_dupla);

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

void listar_tarefas(Lista_encadeada **lista, TIPO_CONTA tipo_de_conta)
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

    limpar_terminal();

    
        bool listagem = false;
        short int qual_lista = 0;

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

                    if (opcao == 1)
                    {
                        printf("p2\n");
                        aux = busca_binaria_duplamente_encadeada(lista_dupla[0], digitar_ID(), INFO_TAREFA);
                    }
                    else
                    {

                        aux = buscar_elemento_duplamente_encadeada_por_ID(lista_dupla[0], digitar_ID(), INFO_TAREFA);
                    }

                    if (aux != NULL)
                    {

                        if (tipo_de_conta == CONTA_GERENTE)
                        {
                            menu_oque_fazer_com_a_INFO(aux->informacoes, INFO_TAREFA);
                        }
                        else
                        {
                            menu_oque_fazer_com_a_INFO_usuario(aux->informacoes, INFO_TAREFA);
                        }
                    }
                    else
                    {
                        printf("ID nao encontrado\n");
                        pausar_terminal();
                    }
                }
                else
                {
                    printf("Selecione um metodo de listagem primeiro\n");
                    opcao = 1;
                    pausar_terminal();
                }
                limpar_terminal();

                break;

            case 0:
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
                listagem = false;
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

void listar_usuarios(Lista_encadeada *lista)
{
    limpar_terminal();

    if (lista == NULL)
    {
        printf("Nao ha informacoes\n");
        pausar_terminal();
        return;
    }

    Lista_duplamente_encadeada *lista_ID = NULL;
    Lista_duplamente_encadeada *lista_afalbetica = NULL;
    Lista_duplamente_encadeada *lista_criacao = NULL;

    copiar_lista_para_duplamente(lista, &lista_ID);
    copiar_lista_para_duplamente(lista, &lista_afalbetica);
    copiar_lista_para_duplamente(lista, &lista_criacao);

    selection_sort_lista_duplamente_encadeada(&lista_ID, comparar_ID);
    selection_sort_lista_duplamente_encadeada(&lista_afalbetica, comparar_afalbetica);

    short int opcao;
    bool listagem = false;

    do
    {
        printf("Como deseja listar as informacoes?\n");
        printf("1. Por ID\n");
        printf("2. Alfabetica\n");
        printf("3. Por criacao\n");
        printf("4. Selecionar por ID\n");
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
            printar_lista_duplamente_encadeada(lista_ID);
            listagem = true;
            break;
        case 2:
            limpar_terminal();
            printar_lista_duplamente_encadeada(lista_afalbetica);
            listagem = true;
            break;
        case 3:
            limpar_terminal();
            printar_lista_duplamente_encadeada(lista_criacao);
            listagem = true;
            break;
        case 4:
        {
            if(listagem){
            Lista_duplamente_encadeada *aux = NULL;

            if (opcao == 1)
            {
                aux = busca_binaria_duplamente_encadeada(lista_ID, digitar_ID(), INFO_USUARIO);
            }
            else
            {
                aux = buscar_elemento_duplamente_encadeada_por_ID(lista_ID, digitar_ID(), INFO_USUARIO);
            }

            if (aux != NULL)
            {
                menu_oque_fazer_com_a_INFO(aux->informacoes, INFO_USUARIO);
            }
            else
            {
                printf("ID nao encontrado\n");
                pausar_terminal();
            }
            }
            else
            {
                printf("Selecione um metodo de listagem primeiro\n");
                opcao = 1;
                pausar_terminal();
            }
            limpar_terminal();

            break;
        }
        case 0:
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            listagem = false;
            pausar_terminal();
            limpar_terminal();
            break;
        }
    } while (opcao != 0 && opcao != 4);
}

void buscar_nomes_parecidos(Lista_encadeada *list, char *nome, TIPO_INFO tipo, TIPO_CONTA conta)
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
            limpar_terminal();
            printf("Informacoes encontradas\n");
            printar_lista_encadeada(aux);

            printf("Digite o ID da informacao que desejas.\n");

            Endereco_lista_encadeada *endereco = buscar_lista_encadeada(aux, digitar_ID(), tipo);

            if (endereco != NULL && endereco->no != NULL)
            {
                if (conta == CONTA_GERENTE)
                {
                    menu_oque_fazer_com_a_INFO(endereco->no->informacoes, tipo);
                }
                else
                {
                    menu_oque_fazer_com_a_INFO_usuario(endereco->no->informacoes, tipo);
                }

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

void buscar_por_ID(Lista_encadeada *list, short int ID, TIPO_INFO tipo, TIPO_CONTA conta)
{
    Endereco_lista_encadeada *endereco = buscar_lista_encadeada(list, ID, tipo);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar a informacao\n");
        pausar_terminal();
        return;
    }

    if (conta == CONTA_GERENTE)
    {
        menu_oque_fazer_com_a_INFO(endereco->no->informacoes, tipo);
    }
    else
    {
        menu_oque_fazer_com_a_INFO_usuario(endereco->no->informacoes, tipo);
    }

    liberar_endereco_lista_encadeada(&endereco);
}

void menu_buscar(Lista_encadeada *lista, TIPO_INFO tipo, TIPO_CONTA conta)
{
    limpar_terminal();
    if (lista == NULL)
    {
        printf("Nao ha informacoes\n");
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

            buscar_por_ID(lista, digitar_ID(), tipo, conta);
            break;
        case '2':
        {
            char *nome = digitar_nome();

            if (nome == NULL)
            {
                break;
            }

            buscar_nomes_parecidos(lista, nome, tipo, conta);

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

bool menu_gerente()
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
            menu_buscar((*geral)->tarefas, INFO_TAREFA, CONTA_GERENTE);
            break;
        case '3':
            listar_tarefas(&(*geral)->tarefas, CONTA_GERENTE);
            break;
        case '4':
            criar_usuario_gerente(&(*geral)->usuarios);
            break;
        case '5':
            menu_buscar((*geral)->usuarios, INFO_USUARIO, CONTA_GERENTE);
            break;
        case '6':
            listar_usuarios((*geral)->usuarios);
            break;
        case '7':
            break;
        case '8':
            // Implementar função de desfazer última ação
            break;
        case '0':
            msg_saindo();
            return true;
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

    } while (opcao != '0' && opcao != '7');

    return false;
}

void organizar_tarefas(Fila **f, char *ultimo)
{
    limpar_terminal();

    if (*f == NULL || (*f)->inicio == NULL)
    {
        printf("Nao ha tarefas\n");
        pausar_terminal();
        return;
    }

    Lista_duplamente_encadeada *aux = NULL;

    copiar_lista_para_duplamente((*f)->inicio, &aux);
    char opcao;

    printf("Como deseja organizar as tarefas?\n");
    printf("1. Por ID\n");
    printf("2. Alfabetica\n");
    printf("3. Por prioridade\n");
    printf("4. Data de criacao\n");
    printf("5. Data de entrega\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    limpar_buffer();

    scanf(" %c", &opcao);
    limpar_buffer();

    switch (opcao)
    {
    case '1':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_ID);
        break;
    case '2':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_afalbetica);
        break;
    case '3':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_prioridade);
        break;
    case '4':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_data_criacao);
        break;
    case '5':
        selection_sort_lista_duplamente_encadeada(&aux, comparar_data_entrega);
        break;
    case '0':
        liberar_memoria_duplamente_encadeada(&aux, false);
        return;
        break;
    default:
        printf("\nOpcao invalida, tente novamente.\n");
        liberar_memoria_duplamente_encadeada(&aux, false);
        pausar_terminal();
        return;
        break;
    }

    *ultimo = opcao;
    liberar_fila(f, false);
    Lista_encadeada *fila_encadeada = NULL;
    copiar_duplamente_para_lista(aux, &fila_encadeada);
    atribuir_Lista_encadeada_a_fila(fila_encadeada, f);
    liberar_memoria_duplamente_encadeada(&aux, false);
    
}

void ver_proxima_tarefa(Fila **tarefas)
{
    limpar_terminal();

    if (*tarefas == NULL || (*tarefas)->inicio == NULL)
    {
        printf("Nao ha tarefas\n");
        pausar_terminal();
        return;
    }

   menu_oque_fazer_com_a_INFO_usuario((*tarefas)->inicio->informacoes, INFO_TAREFA);

    
}



bool menu_usuario(USUARIO *usuario)
{
    char opcao;

    usuario_logado = usuario;
    Lista_encadeada *fila_encadeada = NULL;
    ultima_organizacao_do_usuario = '1';

    copiar_lista_encadeada(&fila_encadeada, usuario->tarefas_associadas);
    atribuir_Lista_encadeada_a_fila(fila_encadeada, &tarefas_do_usuario);

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
            menu_buscar(usuario->tarefas_associadas, INFO_TAREFA, CONTA_USUARIO);
            break;
        case '2':
            organizar_tarefas(&tarefas_do_usuario, &ultima_organizacao_do_usuario);
            break;
        case '3':
            ver_proxima_tarefa(&tarefas_do_usuario);
            break;
        case '4':
            listar_tarefas(&usuario->tarefas_associadas, CONTA_USUARIO);
            break;
        case '5':

            break;
        case '0':
            msg_saindo();
            liberar_fila(&tarefas_do_usuario, false);
            return true;
            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

    } while (opcao != '0' && opcao != '5');

    liberar_fila(&tarefas_do_usuario, false);

    return false;
}

void selecionar_usuario(bool *sair)
{

    if ((*geral)->usuarios == NULL)
    {
        printf("Nao ha usuarios\n");
        pausar_terminal();
        return;
    }

    limpar_terminal();

    printar_lista_encadeada((*geral)->usuarios);

    printf("Selecione um usuario\n");

    Endereco_lista_encadeada *endereco = buscar_lista_encadeada((*geral)->usuarios, digitar_ID(), INFO_USUARIO);

    if (endereco == NULL || endereco->no == NULL)
    {
        printf("Nao foi possivel encontrar o usuario\n");
        pausar_terminal();
        return;
    }

    USUARIO *usuario = (USUARIO *)endereco->no->informacoes;

    if (usuario == NULL)
    {
        printf("Nao foi possivel encontrar o usuario\n");
        pausar_terminal();
        return;
    }

    *sair = menu_usuario(usuario);

    liberar_endereco_lista_encadeada(&endereco);
}

void menu_inicial(GERENTE **gerente)
{
    geral = gerente;

    char opcao;
    bool sair = false;

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
            sair = menu_gerente();
            break;
        case '2':
            selecionar_usuario(&sair);
            break;
        case '0':
            msg_saindo();

            break;
        default:
            printf("\nOpcao invalida, tente novamente.\n");
            pausar_terminal();
            break;
        }

        if (sair)
        {
            return;
        }

    } while (opcao != '0');
}
