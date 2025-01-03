#include <stdio.h>
#include <stdlib.h>

//Teste de compatilibidade, se é possivel utilizar todas as bibliotecas




int main()
{
    //Acessa o cmd não o powershell, tem diferença de comandos
// system("gcc -o teste -pthread ../BIBLIOTECAS_LISTAS/FILA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c ../BIBLIOTECAS_LISTAS/PILHA_BIB.c");

system("gcc -o teste -pthread ../TESTES/testes_ordenacao.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c");
system("teste.exe");
    return 0;
}