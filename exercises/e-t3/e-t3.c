#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct { int id; int total; } thread_arg_t;

void *report(void *arg) {
    thread_arg_t *a = (thread_arg_t *)arg;
    printf("Thread %d of %d reporting for duty!\n",
           a->id, a->total);
    return NULL;
}

int main(void) {
    char *env = getenv("NUM_THREADS");
    int n = (env && atoi(env) > 0) ? atoi(env) : 2;
    pthread_t tids[n];
    thread_arg_t args[n];
    for (int i = 0; i < n; i++) {
        args[i] = (thread_arg_t){ i + 1, n };
        pthread_create(&tids[i], NULL, report, &args[i]);
    }
    for (int i = 0; i < n; i++) pthread_join(tids[i], NULL);
    return 0;
}
