#include <stdio.h>
#include <stdlib.h>

#include "../BIBLIOTECAS/Struct_info.h"

int main()
{

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