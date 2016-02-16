#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(int argc, char **argv)
{
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        printf("Hello world from thread %d\n", omp_get_thread_num());
        sleep(2);
    }

    double end = omp_get_wtime();
    printf("Elapsed time: %.2f seconds\n", end - start);

    return 0;
}
