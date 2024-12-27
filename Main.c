#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas
#include "BIBLIOTECAS/LISTA_CIRCULAR_BIB.h"
#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"


int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste ../TESTES/testes_lista_duplamente_encadeada.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c");
    system("teste.exe");
    return 0;
}