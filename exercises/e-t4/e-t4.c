#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_N 512
static int N, M;
static double A[MAX_N][MAX_N];
static double B[MAX_N][MAX_N], C[MAX_N][MAX_N];

typedef struct { int start; int end; } range_t;

void *multiply(void *arg) {
    range_t *r = (range_t *)arg;
    for (int i = r->start; i < r->end; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <M>\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]); M = atoi(argv[2]);
    if (N <= 0 || N > MAX_N || M <= 0) return 1;
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;  B[i][j] = rand() % 100;
        }

clock_t t0 = clock();
pthread_t thr[M];
range_t ranges[M];
int rows_per = N / M;
for (int i = 0; i < M; i++) {
    ranges[i].start = i * rows_per;
    ranges[i].end = (i == M-1) ? N : (i+1)*rows_per;
    pthread_create(&thr[i], NULL,
                   multiply, &ranges[i]);
}

for (int i = 0; i < M; i++)
        pthread_join(thr[i], NULL);
    printf("Time: %.4fs\n",
           (double)(clock() - t0) / CLOCKS_PER_SEC);
    return 0;
}
