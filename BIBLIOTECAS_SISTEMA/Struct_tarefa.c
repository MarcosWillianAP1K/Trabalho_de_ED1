#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "Struct_tarefa.h"

void liberar_TAREFA(TAREFA **tarefa)
{
    free((*tarefa)->nome);
    liberar_DATA_HORA(&(*tarefa)->data_entrega);
    liberar_DATA_HORA(&(*tarefa)->data_criacao);
    liberar_memoria_encadeada(&(*tarefa)->usuarios_associados, false);
    free(*tarefa);
    *tarefa = NULL;
}


bool selecionar_s_ou_n()
{
    char c;

    do
    {
        limpar_buffer();
        scanf("%c", &c);
        limpar_buffer();

        if (c == 's' || c == 'S')
        {
            return true;
        }

        if (c != 'n' && c != 'N' && c != 's' && c != 'S')
        {
            printf("Digite um valor valido: ");
        }

    } while (c != 'n' && c != 'N' && c != 's' && c != 'S');

    return false;
}


bool confirmar_tarefa(TAREFA *tarefa)
{
    printar_tarefa(tarefa);

    printf("\nDeseja confirmar a tarefa? (s/n): ");

    return selecionar_s_ou_n();
}

bool reescrever_tarefa()
{
    printf("\nDeseja reescrever os dados? (s/n): ");

    return selecionar_s_ou_n();
}


char *criar_nome(int tam)
{
    char *nome = (char *)malloc((tam + 1) * sizeof(char));

    verificar_alocacao(nome);

    return nome;
}

TAREFA *criar_tarefa()
{
    TAREFA *tarefa = (TAREFA *)malloc(sizeof(TAREFA));

    verificar_alocacao(tarefa);

    tarefa->ID = 0;
    tarefa->nome = criar_nome(1);
    tarefa->nome[0] = '\0';
    tarefa->nivel_prioridade = 0;
    tarefa->data_criacao = criar_data_hora();
    tarefa->data_entrega = criar_data_hora();
    tarefa->usuarios_associados = NULL;

    pegar_data_atual(tarefa->data_criacao);

    return tarefa;
}

void atribuir_nome(char **nome1, char *nome2)
{
    if (nome2 == NULL)
    {
        return;
    }

    free(*nome1);
    *nome1 = criar_nome(strlen(nome2));
    strcpy(*nome1, nome2);
}

void copiar_tarefas(TAREFA **tarefa1, TAREFA *tarefa2)
{

    if (tarefa2 == NULL)
    {
        return;
    }

    if (*tarefa1 == NULL)
    {
        *tarefa1 = criar_tarefa();
    }

    (*tarefa1)->ID = tarefa2->ID;
    atribuir_nome(&(*tarefa1)->nome, tarefa2->nome);

    (*tarefa1)->nivel_prioridade = tarefa2->nivel_prioridade;

    (*tarefa1)->data_entrega->minuto = tarefa2->data_entrega->minuto;
    (*tarefa1)->data_entrega->hora = tarefa2->data_entrega->hora;
    (*tarefa1)->data_entrega->dia = tarefa2->data_entrega->dia;
    (*tarefa1)->data_entrega->mes = tarefa2->data_entrega->mes;
    (*tarefa1)->data_entrega->ano = tarefa2->data_entrega->ano;

    (*tarefa1)->data_criacao->minuto = tarefa2->data_criacao->minuto;
    (*tarefa1)->data_criacao->hora = tarefa2->data_criacao->hora;
    (*tarefa1)->data_criacao->dia = tarefa2->data_criacao->dia;
    (*tarefa1)->data_criacao->mes = tarefa2->data_criacao->mes;
    (*tarefa1)->data_criacao->ano = tarefa2->data_criacao->ano;
}

void printar_tarefa(TAREFA *tarefa)
{
    if (tarefa == NULL)
    {
        return;
    }

    printf("ID: %03d\n", tarefa->ID);
    printf("Nome: %s\n", tarefa->nome);
    printf("Nivel de Prioridade: %d\n", tarefa->nivel_prioridade);
    printf("Data de Entrega: %02d/%02d/%04d\n", tarefa->data_entrega->dia, tarefa->data_entrega->mes, tarefa->data_entrega->ano);
    printf("Hora de Entrega: %02d:%02d\n", tarefa->data_entrega->hora, tarefa->data_entrega->minuto);
    printf("Data de Criacao: %02d/%02d/%04d\n", tarefa->data_criacao->dia, tarefa->data_criacao->mes, tarefa->data_criacao->ano);
    printf("Hora de Criacao: %02d:%02d\n", tarefa->data_criacao->hora, tarefa->data_criacao->minuto);
}

// Sequencia de funções para digitar a tarefa

// Digitar ID e apenas para testes, não sera implementado no produto final
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

char *digitar_nome()
{
limpar_buffer();
#define TAM_PADRAO 20

    int tam, cont = 0;
    char *nome = criar_nome(TAM_PADRAO);

    printf("Digite o nome: ");

    if (fgets(nome, TAM_PADRAO * sizeof(char), stdin) != NULL)
    {

        tam = strlen(nome);

        while (nome[tam - 1] != '\n')
        {
            cont++;
            char *temp = (char *)realloc(nome, (TAM_PADRAO * cont) * sizeof(char));

            verificar_realocacao(temp);

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
    limpar_buffer();

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

// Seguinte, essa função permite escrever a tarefa e retorna um ponteiro com o endereços da tarefa, ja tem as blindagens necessarias
TAREFA *escrever_tarefa()
{
    TAREFA *tarefa = criar_tarefa();

    while (1)
    {
        // tarefa->ID = digitar_ID();

        // Sera atribuido o ID correto depois
        tarefa->ID = 0;

        // atribuir_nome(&tarefa->nome, digitar_nome());

        free(tarefa->nome);
        tarefa->nome = digitar_nome();

        tarefa->nivel_prioridade = digitar_nivel_prioridade();

        while (1)
        {
            tarefa->data_entrega->minuto = digitar_minuto();

            tarefa->data_entrega->hora = digitar_hora();

            tarefa->data_entrega->dia = digitar_dia();

            tarefa->data_entrega->mes = digitar_mes();

            tarefa->data_entrega->ano = digitar_ano();

            if (!validar_data(tarefa->data_entrega))
            {
                printf("\nData/hora invalida.");
                if (!reescrever_tarefa())
                {
                    liberar_TAREFA(&tarefa);
                    printf("Operacao cancelada.\n");
                    return tarefa;
                }
            }
            else
            {
                break;
            }
        }
        printf("\n");

        pegar_data_atual(tarefa->data_criacao);

        if (confirmar_tarefa(tarefa))
        {
            
            break;
        }

        if (!reescrever_tarefa())
        {
            liberar_TAREFA(&tarefa);
            printf("Operacao cancelada.\n");
            break;
        }
    }

    return tarefa;
}

TAREFA *editar_tarefa(TAREFA **tarefa, bool liberar_tarefa_antiga)
{
    if (*tarefa == NULL)
    {
        printf("\nNao ha tarefa para editar.\n");
        return NULL;
    }

    TAREFA *nova_tarefa = criar_tarefa();

    copiar_tarefas(&nova_tarefa, *tarefa);

    char c;

    do
    {
        printar_tarefa(nova_tarefa);
        // printar_tarefa(*tarefa);

        printf("\nSelecione o que deseja editar:\n");
        printf("1 - Nome\n");
        printf("2 - Nivel de Prioridade\n");
        printf("3 - Data\n");
        printf("4 - Hora\n");
        printf("5 - Confirmar\n");
        printf("6 - Cancelar\n");

        limpar_buffer();
        scanf("%c", &c);
        limpar_buffer();

        switch (c)
        {
        case '1':
            // atribuir_nome(&nova_tarefa->nome, digitar_nome());
            free(nova_tarefa->nome);
            nova_tarefa->nome = digitar_nome();
            break;

        case '2':
            nova_tarefa->nivel_prioridade = digitar_nivel_prioridade();
            break;

        case '3':
        {
            DATA_HORA *data = criar_data_hora();

            data->minuto = nova_tarefa->data_entrega->minuto;
            data->hora = nova_tarefa->data_entrega->hora;

            while (1)
            {
                data->dia = digitar_dia();

                data->mes = digitar_mes();

                data->ano = digitar_ano();

                if (validar_data(data))
                {
                    nova_tarefa->data_entrega->dia = data->dia;
                    nova_tarefa->data_entrega->mes = data->mes;
                    nova_tarefa->data_entrega->ano = data->ano;
                    free(data);
                    break;
                }
                else
                {
                    printf("\nData invalida.");
                    printf("\nDeseja reescrever a data? (s/n): ");

                    if (!selecionar_s_ou_n())
                    {
                        free(data);
                        break;
                    }
                }
            }
        }
        break;

        case '4':
        {
            DATA_HORA *data = criar_data_hora();

            data->dia = nova_tarefa->data_entrega->dia;
            data->mes = nova_tarefa->data_entrega->mes;
            data->ano = nova_tarefa->data_entrega->ano;

            while (1)
            {
                data->hora = digitar_hora();

                data->minuto = digitar_minuto();

                if (validar_data(data))
                {
                    nova_tarefa->data_entrega->hora = data->hora;
                    nova_tarefa->data_entrega->minuto = data->minuto;
                    free(data);
                    break;
                }
                else
                {
                    printf("\nHora invalida.");
                    printf("\nDeseja reescrever a hora? (s/n): ");

                    if (!selecionar_s_ou_n())
                    {
                        free(data);
                        break;
                    }
                }
            }
        }

        break;

        case '5':
            printf("\n");
            if (confirmar_tarefa(nova_tarefa))
            {
                

                if (liberar_tarefa_antiga)
                {
                    copiar_tarefas(tarefa, nova_tarefa);
                    liberar_TAREFA(&nova_tarefa);
                }
                else
                {
                    TAREFA *temp = NULL;
                    copiar_tarefas(&temp, *tarefa);
                    copiar_tarefas(tarefa, nova_tarefa);
                    copiar_tarefas(&nova_tarefa, temp);
                    liberar_TAREFA(&temp);
                }
                
                
                printf("Tarefa alterada com sucesso.\n");

                return nova_tarefa;
            }

            break;

        case '6':

            printf("Deseja cancelar a operacao? (s/n): ");

            if (selecionar_s_ou_n())
            {
                
                liberar_TAREFA(&nova_tarefa);
                printf("Operacao cancelada.\n");
            }
            else
            {
                c = '0';
            }

            break;

        default:
            printf("Digite um valor valido: ");
            break;
        }

    } while ( c != '6');

    return NULL;
}
