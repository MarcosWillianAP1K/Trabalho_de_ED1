#include <stdio.h>
#include <stdlib.h>
#include "INTERATIVIDADE/Sistema.h"


int main()
{
    GERENTE *gerente = NULL;

    inicializacao_do_sistema(&gerente);

    menu_inicial(&gerente);

    liberacao_da_memoria_sistema(&gerente);

    return 0;
}