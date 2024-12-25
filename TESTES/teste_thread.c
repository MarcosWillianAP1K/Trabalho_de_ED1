#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void* calculate_sum(void* arg) {
    int n = *(int*)arg;
    int* result = malloc(sizeof(int)); // Alocando memória para o resultado
    *result = (n * (n + 1)) / 2; // Soma dos primeiros n números
    return (void*)result;
}

int main() {
    pthread_t thread;
    int n = 10;
    int *sum;

    // Criando a thread
    if (pthread_create(&thread, NULL, calculate_sum, (void*)&n) != 0) {
        printf("Erro ao criar a thread\n");
        return 1;
    }

    // Esperando a thread terminar e capturando o resultado
    if (pthread_join(thread, (void**)&sum) != 0) {
        printf("Erro ao esperar pela thread\n");
        return 1;
    }

    printf("Soma dos primeiros %d numeros: %d\n", n, *sum);

    // Liberando a memória alocada pela thread
    free(sum);

    return 0;
}