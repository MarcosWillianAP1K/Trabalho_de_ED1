#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas




int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste -pthread ../TESTES/testes_pilha.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS/PILHA_BIB.c");
    system("teste.exe");
    return 0;
}