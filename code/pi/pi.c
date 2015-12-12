#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Requires argument: number of intervals.");
        return 1;
    }

    int nprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nintervals = atoi(argv[1]);
    double time_start;
    if (rank == 0) {
        time_start = MPI_Wtime();
    }

    double h = 1.0 / (double)nintervals;
    double sum = 0.0;
    int i;
    for (i = rank; i < nintervals; i += nprocs) {
        double x = h * ((double)i + 0.5);
        sum += 4.0 / (1.0 + x * x);
    }
    double my_pi = h * sum;

    double pi;
    MPI_Reduce(&my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double duration = MPI_Wtime() - time_start;
        double error = fabs(pi - 4.0 * atan(1.0));
        printf("pi=%e, error=%e, duration=%e\n", pi, error, duration);
    }

    MPI_Finalize();

    return 0;
}
