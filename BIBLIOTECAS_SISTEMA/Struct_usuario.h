#include "../BIBLIOTECAS_LISTAS/LISTA_ENCADEADA_BIB.h"

#ifndef Struct_usuario_h
#define Struct_usuario_h


typedef struct USUARIO
{
    int ID;
    char *login;
    
    Lista_encadeada *tarefas;
    

} USUARIO;



#endif // Struct_usuario_h