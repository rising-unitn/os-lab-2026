#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#define N_THR 8
#define ITERS 500000
static int   unsafe = 0;
static int   safe_m = 0;
static atomic_int safe_a = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *inc_unsafe(void *a) { (void)a;
    for (int i=0;i<ITERS;i++) unsafe++;
    return NULL; }

void *inc_mutex(void *a) { (void)a;
    for (int i=0;i<ITERS;i++) {
        pthread_mutex_lock(&mtx);
        safe_m++;
        pthread_mutex_unlock(&mtx); }
    return NULL; }

void *inc_atomic(void *a) { (void)a;
    for (int i=0;i<ITERS;i++)
        atomic_fetch_add(&safe_a, 1);
    return NULL; }

#include <time.h>
double run(void *(*fn)(void*)) {
    pthread_t t[N_THR];
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i=0;i<N_THR;i++)
        pthread_create(&t[i],NULL,fn,NULL);
    for (int i=0;i<N_THR;i++)
        pthread_join(t[i],NULL);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return (t1.tv_sec-t0.tv_sec)
           +(t1.tv_nsec-t0.tv_nsec)*1e-9;
}

int main(void) {
    int expect = N_THR * ITERS;
    double t;
    t = run(inc_unsafe);
    printf("Unsafe : %7d (exp %d)  %.3fs\n",
           unsafe, expect, t);
    t = run(inc_mutex);
    printf("Mutex  : %7d (exp %d)  %.3fs\n",
           safe_m, expect, t);
    t = run(inc_atomic);
    printf("Atomic : %7d (exp %d)  %.3fs\n",
           (int)atomic_load(&safe_a), expect, t);
    return 0;
}
