#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas




int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste -pthread ../TESTES/testes_lista_encadeada.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c");
    system("teste.exe");
    return 0;
}