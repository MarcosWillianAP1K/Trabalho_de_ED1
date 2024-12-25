#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

pthread_mutex_t mutex; // Mutex para sincronização
int counter = 0;       // Variável compartilhada

void* thread_function(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    counter++; // Incrementa a variável compartilhada
    printf("Thread %d: Counter = %d\n", id, counter);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex

    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            printf("Erro ao criar a thread %d\n", i + 1);
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroi o mutex
    printf("Todas as threads terminaram.\n");

    return 0;
}