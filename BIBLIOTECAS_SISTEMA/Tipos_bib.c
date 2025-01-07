#include "Tipos_bib.h"
#include "Struct_tarefa.h"
#include "Struct_usuario.h"
#include "Struct_gerente.h"

#include <stdio.h>
#include <stdlib.h>


void error_tipo(TIPO_INFO tipo)
{
    printf("Tipo invalido\n");
    const char *tipo_str;
    switch (tipo) {
        case INFO_TAREFA:
            tipo_str = "INFO_TAREFA";
            break;
        case INFO_USUARIO:
            tipo_str = "INFO_USUARIO";
            break;
        case INFO_GERENTE:
            tipo_str = "INFO_GERENTE";
            break;
        default:
            tipo_str = "UNKNOWN";
            break;
    }
    printf("O tipo e: %s\n", tipo_str);
    exit(1);
}

DATA_HORA *retornar_data_entrega_convertida(TIPO_INFO tipo, void *info)
{
    if (info == NULL)
    {
        return NULL;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        return ((TAREFA *)info)->data_entrega;
        break;

    case INFO_USUARIO:
    case INFO_GERENTE:
        return NULL;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}


DATA_HORA *retornar_data_criacao_convertida(TIPO_INFO tipo, void *info)
{
    if (info == NULL)
    {
        return NULL;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        return ((TAREFA *)info)->data_criacao;
        break;

    case INFO_USUARIO:
    case INFO_GERENTE:
        return NULL;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

DATA_HORA *retornar_data_conclusao_convertida(TIPO_INFO tipo, void *info)
{

if (info == NULL)
    {
        return NULL;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        return ((TAREFA *)info)->data_conclusao;
        break;

    case INFO_USUARIO:
    case INFO_GERENTE:
        return NULL;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}



void *retorna_info_convertida(TIPO_INFO tipo, void *info)
{
    switch (tipo)
    {
    case INFO_TAREFA:
        return (TAREFA *)info;
        break;

    case INFO_USUARIO:
        return (USUARIO *)info;
        break;

    case INFO_GERENTE:
        return (GERENTE *)info;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

short int retornar_ID_convertido(TIPO_INFO tipo, void *info)
{
    if (info == NULL)
    {
        return -1;
    }
    

    switch (tipo)
    {
    case INFO_TAREFA:
        return ((TAREFA *)info)->ID;
        break;

    case INFO_USUARIO:
        return ((USUARIO *)info)->ID;
        break;

    case INFO_GERENTE:
        return -1;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

char *retornar_nome_convertido(TIPO_INFO tipo, void *info)
{
    if (info == NULL)
    {
        return NULL;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        return ((TAREFA *)info)->nome;
        break;

    case INFO_USUARIO:
        return ((USUARIO *)info)->login;
        break;

    case INFO_GERENTE:
        return NULL;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

void atribuir_ID_convertido(TIPO_INFO tipo, void *info, short int ID)
{
    if (info == NULL)
    {
        return;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        ((TAREFA *)info)->ID = ID;
        break;

    case INFO_USUARIO:
        ((USUARIO *)info)->ID = ID;
        break;

    case INFO_GERENTE:
        return;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

void liberar_INFO_convertido(TIPO_INFO tipo, void **info)
{
    if (*info == NULL)
    {
        return;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        liberar_TAREFA((TAREFA **)info);
        break;

    case INFO_USUARIO:
        liberar_USUARIO((USUARIO **)info);
        break;

    case INFO_GERENTE:
        return;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

void printar_INFO_convertido(TIPO_INFO tipo, void *info)
{
    if (info == NULL)
    {
        return;
    }

    switch (tipo)
    {
    case INFO_TAREFA:
        printar_tarefa((TAREFA *)info);
        break;

    case INFO_USUARIO:
        printar_usuario((USUARIO *)info);
        break;

    case INFO_GERENTE:
        return;
        break;

    default:
        error_tipo(tipo);
        break;
    }
}

void *editar_INFO_convertido(TIPO_INFO tipo, void **info, bool liberar_info_antiga)
{
    
    if (info == NULL)
    {
        return NULL;
    }
   

    switch (tipo)
    {
    case INFO_TAREFA:
        return editar_tarefa((TAREFA **)info, liberar_info_antiga);
        break;

    case INFO_USUARIO:
        // return editar_usuario((USUARIO **)info, liberar_info_antiga);
        break;

    case INFO_GERENTE:
        return NULL;
        break;

    default:
        error_tipo(tipo);
        break;
    }

    return NULL;
}
