#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main()
{
    char *nome1 = "t";

    char *nome2 = "teste1";
    char *nome3 = "teste";


    if (strstr(nome1, nome2) != NULL)
    {
        printf("Achou1\n");
    }
    else
    {
        printf("Nao achou1\n");
    }

    if (strstr(nome3, nome1) != NULL)
    {
        printf("Achou2\n");
    }
    else
    {
        printf("Nao achou2\n");
    }
    



    return 0;
}