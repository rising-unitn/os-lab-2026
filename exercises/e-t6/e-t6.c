#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
static volatile int running = 1;
static volatile long counters[NUM_THREADS];

void handle_sigusr1(int sig) {
    (void)sig;
    printf("\n--- Counter values ---\n");
    for (int i = 0; i < NUM_THREADS; i++)
        printf("  Thread %d: %ld\n", i, counters[i]);
}

void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}

void handle_sigusr2(int sig) {
    (void)sig;
    int max_i = 0;
    for (int i = 1; i < NUM_THREADS; i++)
        if (counters[i] > counters[max_i]) max_i = i;
    printf("\nHighest: thread %d (%ld)\n",
           max_i, counters[max_i]);
}

void *worker(void *arg) {
    int id = *(int *)arg;
    while (running) counters[id]++;
    return NULL;
}

void setup_handler(int sig, void (*fn)(int)) {
    struct sigaction sa = { .sa_handler = fn };
    sigemptyset(&sa.sa_mask);
    sigaction(sig, &sa, NULL);
}

int main(void) {
    setup_handler(SIGUSR1, handle_sigusr1);
    setup_handler(SIGUSR2, handle_sigusr2);
    setup_handler(SIGINT, handle_sigint);
    printf("PID: %d\n", getpid());

    pthread_t thr[NUM_THREADS];
    int ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&thr[i], NULL, worker, &ids[i]);
    }

for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(thr[i], NULL);
    printf("\nAll threads stopped.\n");
    return 0;
}
