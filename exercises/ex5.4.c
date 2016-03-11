#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"

double random_double()
{
    return (double) rand() / RAND_MAX;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int nprocs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 2) {
        if (rank == 0) {
            printf("Usage: ex2.5 n\n");
            printf("  n = vector/matrix size\n");
        }

        MPI_Finalize();
        return 1;
    }

    int n = atoi(argv[1]);

    // Compute the number of indices owned by each process
    int ncols[nprocs];
    for (size_t i = 0; i < nprocs; i++)
        ncols[i] = n / nprocs;
    int leftover = n % nprocs;
    for (size_t i = 1; i <= leftover; i++)
        ncols[nprocs - i]++;

    // Compute the displacements for each process (the first index owned by each of them)
    // It is useful to have the displacement for the nonexistent n+1'th process too
    int displ[nprocs + 1];
    displ[0] = 0;
    for (size_t i = 1; i <= nprocs; i++)
        displ[i] = displ[i-1] + ncols[i-1];

    // Allocate matrix and vector parts on each process
    double *loc_vec = malloc(ncols[rank] * sizeof(double));
    double *loc_mx = malloc(n * ncols[rank] * sizeof(double));

    // Double index pointers into the matrix
    // Note that we use column-major storage so the indices are flipped
    double **loc_mx_p = malloc(ncols[rank] * sizeof(double *));
    for (size_t i = 0; i < ncols[rank]; i++)
        loc_mx_p[i] = &loc_mx[n*i];

    // Fill with random data
    srand(time(NULL) + rank);
    for (size_t i = 0; i < ncols[rank]; i++)
        for (size_t j = 0; j < n; j++) {
            loc_mx_p[i][j] = random_double();
            loc_vec[i] = random_double();
        }

    // Compute the local matrix-vector product
    double *temp = calloc(n, sizeof(double));
    for (size_t i = 0; i < ncols[rank]; i++)
        for (size_t j = 0; j < n; j++)
            temp[j] += loc_mx_p[i][j] * loc_vec[i];

    // Sum over all those producs to get the global matrix-vector product
    // It is possible to do this in-place (i.e. without a separate receive buffer)
    // for some kinds of communicators, but I do not consider that here
    double *global = malloc(n * sizeof(double));
    MPI_Allreduce(temp, global, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    free(temp);

    // Pick out the relevant part of the global vector for each process
    for (size_t i = 0; i < ncols[rank]; i++)
        loc_vec[i] = global[displ[rank] + i];
    free(global);

    // The matrix-vector product is now stored across processes in
    // the same way that the original vector was

    MPI_Finalize();
    return 0;
}
