#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

double wall_time()
{
    struct timeval tmp_time;
    gettimeofday(&tmp_time, NULL);
    return tmp_time.tv_sec + tmp_time.tv_usec/1e6;
}

double dot(double *u, double *v, int len)
{
    double result = 0;
    for (int i = 0; i < len; i++)
        result += u[i] * v[i];
    return result;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Need two parameters: ");
        printf("the number of times to loop, and ");
        printf("the vector length.\n");
        return 1;
    }

    int ntimes = atoi(argv[1]);
    int len = atoi(argv[2]);

    double *u = (double*)malloc(len * sizeof(double));
    srand(wall_time());
    for (int i = 0; i < len; i++)
        u[i] = (double)rand() / RAND_MAX;

    printf("Performing %i loops\n", ntimes);
    printf("Vector length: %i\n", len);

    double b = 0;
    double now = wall_time();
    for (int i = 0; i < ntimes; i++)
        b += dot(u, u, len);

    printf("Used %f seconds, sum: %f\n", wall_time() - now, b);
    free(u);
    return 0;
}
