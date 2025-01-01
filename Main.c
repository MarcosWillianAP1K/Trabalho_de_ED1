#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas
#include "BIBLIOTECAS/LISTA_CIRCULAR_BIB.h"
#include "BIBLIOTECAS/LISTA_ENCADEADA_BIB.h"
#include "BIBLIOTECAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.h"
#include "BIBLIOTECAS/ORDENACAO_BIB.h"
#include "BIBLIOTECAS/FILA_BIB.h"
#include "BIBLIOTECAS/Struct_info.h"



int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste -pthread ../TESTES/testes_fila.c ../BIBLIOTECAS/Struct_info.c ../BIBLIOTECAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS/FILA_BIB.c");
    system("teste.exe");
    return 0;
}