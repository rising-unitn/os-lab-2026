#include <stdio.h>
#include <pthread.h>

#define N_THREADS 4
#define ITERS 1000000

static int counter = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int use_lock = 0;  // toggled by argv

void *incrementer(void *arg) {
    (void)arg;
    for (int i = 0; i < ITERS; i++) {
        if (use_lock) pthread_mutex_lock(&mtx);
        counter++;
        if (use_lock) pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t thr[N_THREADS];
    // --- without lock ---
    counter = 0; use_lock = 0;
    for (int i = 0; i < N_THREADS; i++)
        pthread_create(&thr[i], NULL, incrementer, NULL);
    for (int i = 0; i < N_THREADS; i++)
        pthread_join(thr[i], NULL);
    printf("Without lock: %d (expected %d)\n",
           counter, N_THREADS * ITERS);

// --- with lock ---
    counter = 0; use_lock = 1;
    for (int i = 0; i < N_THREADS; i++)
        pthread_create(&thr[i], NULL, incrementer, NULL);
    for (int i = 0; i < N_THREADS; i++)
        pthread_join(thr[i], NULL);
    printf("With lock:    %d (expected %d)\n",
           counter, N_THREADS * ITERS);
    pthread_mutex_destroy(&mtx);
    return 0;
}
