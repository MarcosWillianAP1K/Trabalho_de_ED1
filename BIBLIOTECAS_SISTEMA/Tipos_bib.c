#include "Tipos_bib.h"
#include "Struct_tarefa.h"
#include "Struct_usuario.h"

#include <stdio.h>
#include <stdlib.h>


void error_tipo()
{
    printf("Tipo invalido\n");
    exit(1);
}

void conferir_tipos(TIPO_INFO tipo1, TIPO_INFO tipo2, void *info1, void *info2)
{
    if (info1 == NULL || info2 == NULL)
    {
        return;
    }

    if (tipo1 != tipo2)
    {
        error_tipo();
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

    default:
        error_tipo();
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

    default:
        error_tipo();
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

    default:
        error_tipo();
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

    default:
        error_tipo();
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

    default:
        error_tipo();
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
        // printar_usuario((USUARIO *)info);
        break;

    default:
        error_tipo();
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

    default:
        error_tipo();
        break;
    }

    return NULL;
}
