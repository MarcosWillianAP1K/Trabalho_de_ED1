

typedef struct INFO
{
    signed short int ID;
    char *nome;

    signed short int nivel_prioridade;

    signed short int minuto;
    signed short int hora;
    signed short int dia;
    signed short int mes;
    signed short int ano;

    struct INFO *proximo;
} INFO;

void liberar_INFO(INFO *info);