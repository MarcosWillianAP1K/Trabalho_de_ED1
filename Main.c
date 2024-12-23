#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste ../testes_lista_encadeada.c  ../BIBLIOTECAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS/Struct_info.c");
    system("teste.exe");
    return 0;
}