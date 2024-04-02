#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m5 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mo = PTHREAD_MUTEX_INITIALIZER; // For output synchronization

int myrand(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void* philosopher(void* arg) {
    int ph = *(int*)arg;
    for (;;) { // Infinite loop
        int duration = myrand(200, 800);
        {
            pthread_mutex_lock(&mo);
            printf("%d thinks %dms\n", ph, duration);
            pthread_mutex_unlock(&mo);
        }
        usleep(duration * 1000); // Convert milliseconds to microseconds
        
        pthread_mutex_lock(&mo);
        printf("\t\t%d is hungry\n", ph);
        pthread_mutex_unlock(&mo);

        pthread_mutex_t *firstFork = (ph == 5) ? &m1 : &m2; // Adjust according to philosopher number
        pthread_mutex_t *secondFork = (ph == 5) ? &m5 : &m3; // Adjust accordingly

        pthread_mutex_lock(firstFork);
        pthread_mutex_lock(secondFork);

        duration = myrand(200, 800);
        {
            pthread_mutex_lock(&mo);
            printf("\t\t\t\t%d eats %dms\n", ph, duration);
            pthread_mutex_unlock(&mo);
        }

        usleep(duration * 1000); // Sleeping while eating

        pthread_mutex_unlock(secondFork);
        pthread_mutex_unlock(firstFork);
    }
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    printf("Dining Philosophers in C with Resource hierarchy\n");

    pthread_t threads[5];
    int ids[5] = {1, 2, 3, 4, 5};

    pthread_create(&threads[0], NULL, philosopher, &ids[0]);
    pthread_create(&threads[1], NULL, philosopher, &ids[1]);
    pthread_create(&threads[2], NULL, philosopher, &ids[2]);
    pthread_create(&threads[3], NULL, philosopher, &ids[3]);
    pthread_create(&threads[4], NULL, philosopher, &ids[4]);

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}