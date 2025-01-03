#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"
#include "../BIBLIOTECAS_LISTAS/LISTA_CIRCULAR_BIB.h"

#ifndef Struct_usuario_h
#define Struct_usuario_h


typedef struct USUARIO
{
    int ID;
    char *login;
    
    Lista_encadeada *tarefas_associadas;
    Lista_circular *historico;

} USUARIO;

USUARIO *criar_USUARIO();

void liberar_USUARIO(USUARIO **info);

USUARIO *escrever_usuario();


#endif // Struct_usuario_h