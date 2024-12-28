#include <stdio.h>
#include <stdlib.h>

#include "../BIBLIOTECAS/Struct_info.h"

// Comando para rodar esse teste
// gcc -o teste -pthread ../TESTES/testes_Struct_info.c ../BIBLIOTECAS/Struct_info.c

int main()
{
    // INFO *info = criar_info();

    // atribuir_nome(&info->nome, "teste1");

    // info->ID = 1;

    INFO *info = escrever_dados();
    printf("\n\n");

    printar_dados(info);
    printf("\n\n");

    editar_dados(&info);
    printf("\n\n");

    printar_dados(info);

    liberar_INFO(&info);

    return 0;
}