#include <stdio.h>
#include <pthread.h>

int global_variable = 0;
pthread_mutex_t mutex;

void *thread_function(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex); // Verrouillage du mutex avant l'accès à la variable globale
        global_variable++; // Accès en écriture à la variable globale
        pthread_mutex_unlock(&mutex); // Déverrouillage du mutex après l'accès à la variable globale
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL); // Initialisation du mutex

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Valeur finale de la variable globale : %d\n", global_variable);

    pthread_mutex_destroy(&mutex); // Destruction du mutex

    return 0;
}