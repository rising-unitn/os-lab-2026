#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define MEALS 3
static pthread_mutex_t forks[N];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id, right = (id + 1) % N;
    int first = (left < right) ? left : right;
    int second = (left < right) ? right : left;
    for (int m = 0; m < MEALS; m++) {
        usleep(rand() % 5000);  // think
        pthread_mutex_lock(&forks[first]);
        pthread_mutex_lock(&forks[second]);

printf("Philosopher %d eating (round %d)\n",
               id, m + 1);
        usleep(rand() % 5000);  // eat
        pthread_mutex_unlock(&forks[second]);
        pthread_mutex_unlock(&forks[first]);
    }
    return NULL;
}

int main(void) {
    srand(42);
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);
    pthread_t thr[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&thr[i], NULL,
                       philosopher, &ids[i]);
    }

for (int i = 0; i < N; i++)
        pthread_join(thr[i], NULL);
    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&forks[i]);
    printf("All philosophers done.\n");
    return 0;
}
