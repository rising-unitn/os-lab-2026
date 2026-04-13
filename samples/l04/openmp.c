#include <stdio.h>
#include <omp.h>
#define N 1000000000LL

int main(void) {
    double sum = 0.0;
    double t0 = omp_get_wtime();
    for (long long i = 0; i < N; i++)
        sum += 1.0 / (i + 1);
    printf("Sequential: %.6f  %.3fs\n",
           sum, omp_get_wtime() - t0);

sum = 0.0;
    t0 = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < N; i++)
        sum += 1.0 / (i + 1);
    printf("Parallel:   %.6f  %.3fs\n",
           sum, omp_get_wtime() - t0);
    return 0;
}
