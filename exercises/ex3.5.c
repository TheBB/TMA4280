#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

double random_double()
{
    return (double)rand() / RAND_MAX;
}

// Converts a local index to a global one
size_t loc_to_glob(size_t loc, size_t rank, size_t nprocs)
{
    return rank + loc * nprocs;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int nprocs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 3) {
        // Only one process needs to print usage output
        if (rank == 0) {
            printf("Usage: ex2.5 n g\n");
            printf("  n = vector/matrix size\n");
            printf("  g = constant gamma\n");
        }

        MPI_Finalize();
        return 1;
    }

    // All processes can read arguments
    int n = atoi(argv[1]);
    double gamma = atof(argv[2]);

    // The total number of elements associated to this process
    // It will own elements rank, rank+nprocs, rank+2*nprocs, ...
    int np = 0;
    for (int i = rank; i < n; i += nprocs)
        np++;

    // Allocate vectors and matrices (this is valid C99)
    // We only allocate the elements owned by this process
    double a[np], b[np], x[np], A[n][np];

    // Fill a, b and A with random data in [0,1]
    // We do this on each process separately
    srand(time(NULL) + rank);
    for (size_t i = 0; i < np; i++) {
        a[i] = random_double();
        b[i] = random_double();
        for (size_t j = 0; j < n; j++)
            A[j][i] = random_double();
    }

    // Compute x
    // ----------------------------------------------------------

    // There is no need to communicate x to other processes
    for (size_t i = 0; i < np; i++)
        x[i] = a[i] + gamma * b[i];

    // Compute y
    // ----------------------------------------------------------

    // Each process contributes data to all elements in y,
    // so we need to allocate n elements
    double y_temp[n];
    for (size_t i = 0; i < n; i++) {
        y_temp[i] = 0.0;
        for (size_t j = 0; j < np; j++)
            y_temp[i] += A[i][j] * b[j];
    }

    // Add in the contribution from the local a
    for (size_t i = 0; i < np; i++)
        y_temp[loc_to_glob(i, rank, nprocs)] += a[i];

    // Sum over all processes to get the actual y
    // Since each process needs it in the next part,
    // we have to use MPI_Allreduce
    double y[n];
    MPI_Allreduce(y_temp, y, n, MPI_DOUBLE,
                  MPI_SUM, MPI_COMM_WORLD);

    // Compute alpha
    // ----------------------------------------------------------

    double alpha_temp = 0.0;
    for (size_t i = 0; i < np; i++)
        alpha_temp += x[i] * y[loc_to_glob(i, rank, nprocs)];

    // Sum over all processes
    // This time it's only important that root gets the answer
    double alpha;
    MPI_Reduce(&alpha_temp, &alpha, 1, MPI_DOUBLE,
               MPI_SUM, 0, MPI_COMM_WORLD);

    // Final output
    // ----------------------------------------------------------

    if (rank == 0)
        printf("alpha = %f\n", alpha);

    MPI_Finalize();
    return 0;
}
