#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 10
#define N_ITEMS  20

static int buffer[BUF_SIZE];
static int in = 0, out = 0;
static sem_t empty_sem, full_sem, mutex_sem;

void *producer(void *arg) {
    (void)arg;
    for (int i = 0; i <= N_ITEMS; i++) {
        sem_wait(&empty_sem);
        sem_wait(&mutex_sem);
        buffer[in] = (i < N_ITEMS) ? i : -1;
        in = (in + 1) % BUF_SIZE;
        sem_post(&mutex_sem);
        sem_post(&full_sem);
    }
    return NULL;
}

void *consumer(void *arg) {
    (void)arg;
    while (1) {
        sem_wait(&full_sem);
        sem_wait(&mutex_sem);
        int item = buffer[out];
        out = (out + 1) % BUF_SIZE;
        sem_post(&mutex_sem);
        sem_post(&empty_sem);
        if (item == -1) break;
        printf("Consumed: %d\n", item);
    }
    return NULL;
}

int main(void) {
    sem_init(&empty_sem, 0, BUF_SIZE);
    sem_init(&full_sem, 0, 0);
    sem_init(&mutex_sem, 0, 1);
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    sem_destroy(&mutex_sem);

printf("All items consumed.\n");
    return 0;
}
