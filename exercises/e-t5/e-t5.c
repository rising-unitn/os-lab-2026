#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10000000
static int arr[SIZE];

int main(void) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100;
    double t1 = omp_get_wtime();
    long seq_sum = 0;
    for (int i = 0; i < SIZE; i++)
        seq_sum += arr[i];
    double t2 = omp_get_wtime();
    printf("Sequential: %ld (%.4fs)\n",
           seq_sum, t2 - t1);

t1 = omp_get_wtime();
    long par_sum = 0;
    #pragma omp parallel for reduction(+:par_sum)
    for (int i = 0; i < SIZE; i++)
        par_sum += arr[i];
    t2 = omp_get_wtime();
    printf("Parallel:   %ld (%.4fs)\n",
           par_sum, t2 - t1);
    return 0;
}
