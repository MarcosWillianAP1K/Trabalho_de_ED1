#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"

#ifndef Struct_usuario_h
#define Struct_usuario_h


typedef struct USUARIO
{
    char *nome;
    int ID;
    
    Lista_encadeada *tarefas;


} USUARIO;



#endif // Struct_usuario_h