#include <stdio.h>
#include <stdlib.h>

// Teste de compatilibidade, se é possivel utilizar todas as bibliotecas

int main()
{
    int sucesso;
    // System acessa o CMD não o powershell, tem diferença de comandos

    //Para teste inviduais
    // sucesso = system("gcc -o teste -pthread ../TESTES/testes_ordenacao.c ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c");

    //Para teste geral
    sucesso = system("gcc -o Sistema -pthread ../BIBLIOTECAS_LISTAS/FILA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_DUPLAMENTE_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.c ../BIBLIOTECAS_LISTAS/ORDENACAO_BIB.c ../BIBLIOTECAS_LISTAS/PILHA_BIB.c ../BIBLIOTECAS_SISTEMA/Struct_data_hora.c  ../BIBLIOTECAS_SISTEMA/Struct_tarefa.c ../BIBLIOTECAS_SISTEMA/Struct_usuario.c ../BIBLIOTECAS_SISTEMA/Tipos_bib.c ../BIBLIOTECAS_SISTEMA/Utilidades_sistema.c ../INTERATIVIDADE/Sistema.c ../main.c");

    
    if (sucesso != 0)
    {
        return 1;
    }
    
    // sucesso = system("teste.exe");
    sucesso = system("Sistema.exe");

    if (sucesso != 0)
    {
        printf("Erro na execucao do programa\n");
        return 1;
    }
    return 0;
}