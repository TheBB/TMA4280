#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double start = MPI_Wtime();

    sleep(2);

    int sum;
    MPI_Allreduce(&rank, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Sum: %d\n", sum);

    double end = MPI_Wtime();
    if (rank == 0)
        printf("Elapsed time: %.2f seconds\n", (end - start));

    MPI_Finalize();
    return 0;
}
