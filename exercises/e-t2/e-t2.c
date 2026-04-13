#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *compute_square(void *arg) {
    int idx = *(int *)arg;
    int *result = malloc(sizeof(int));
    *result = idx * idx;
    pthread_exit((void *)result);
}

#define DEFAULT_N 4

int main(int argc, char *argv[]) {
    int n = (argc > 1) ? atoi(argv[1]) : DEFAULT_N;
    if (n <= 0) n = DEFAULT_N;
    pthread_t threads[n];
    int indices[n];
    for (int i = 0; i < n; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL,
                       compute_square, &indices[i]);
    }

for (int i = 0; i < n; i++) {
        void *retval;
        pthread_join(threads[i], &retval);
        int *res = (int *)retval;
        printf("Thread %d returned %d\n", i, *res);
        free(res);
    }
    return 0;
}
