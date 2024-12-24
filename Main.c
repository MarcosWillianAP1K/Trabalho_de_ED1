#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste ../TESTES/testes_lista_circular.c  ../BIBLIOTECAS/LISTA_CIRCULAR_BIB.c ../BIBLIOTECAS/Struct_info.c");
    system("teste.exe");
    return 0;
}