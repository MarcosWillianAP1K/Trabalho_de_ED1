#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas




int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
    system("gcc -o teste -pthread ../TESTES/testes_Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c");
    system("teste.exe");
    return 0;
}