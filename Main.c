#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas
#include "BIBLIOTECAS/LISTA_CIRCULAR_BIB.h"
#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
#include "BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"


int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste -pthread ../TESTES/testes_ordenacao.c ../BIBLIOTECAS/ORDENACAO_BIB.c ../BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS/Struct_info.c");
    system("teste.exe");
    return 0;
}