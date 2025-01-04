#include <stdio.h>
#include <stdlib.h>

// Teste de compatilibidade, se é possivel utilizar todas as bibliotecas

int main()
{
    // Acessa o cmd não o powershell, tem diferença de comandos
    //Para teste inviduais
    // system("gcc -o teste -pthread ../TESTES/testes_ordenacao.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c");
    // system("teste.exe");

    //Para teste geral
    system("gcc -o Sistema -pthread ../BIBLIOTECAS_LISTAS/FILA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c ../BIBLIOTECAS_LISTAS/PILHA_BIB.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c  ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_usuario.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../INTERATIVIDADE/Sistema.c ../main.c");
    system("Sistema.exe");

    return 0;
}