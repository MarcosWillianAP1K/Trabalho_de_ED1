#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PADRAO 20

int main()
{

    char *nome = (char *)malloc(TAM_PADRAO * sizeof(char));
    int tam, cont = 0;

    if (nome == NULL)
    {
        printf("Erro na alocação de memória\n");
        return 1;
    }

    printf("Digite o nome: ");

    if (fgets(nome, TAM_PADRAO * sizeof(char), stdin) != NULL)
    {

        tam = strlen(nome);

        while (nome[tam - 1] != '\n')
        {
            cont++;
            char *temp = (char *)realloc(nome, (TAM_PADRAO * cont) * sizeof(char));

            if (temp == NULL)
            {
                printf("Erro na alocação de memória\n");
                return 1;
            }

            nome = temp;

            if (fgets(nome + tam, ((TAM_PADRAO * cont) * sizeof(char)) - tam, stdin) == NULL)
            {
                break;
            }

            tam = strlen(nome);
        }
    }

    tam = strlen(nome);

    if (nome[tam - 1] == '\n')
    {
        nome[tam - 1] = '\0';
    }

    printf("\nNome: %s\n\nFoi realocado %d\nTamanho %d\n\n", nome, cont, tam);

    free(nome);

    return 0;
}
