#include <stdio.h>
#include "common.h"

int main(int argc, char **argv)
{
    int rank, size;
    init_app(argc, argv, &rank, &size);

    Vector vec = createVectorMPI(30, &WorldComm, 1);

    if (rank == 0) {
        for (size_t i = 0; i < size; i++) {
            printf(">> Proc %d owns [%d,%d]\n", i, vec->displ[i],
                   vec->displ[i] + vec->sizes[i] - 1);
        }
    }

    close_app();
    return 0;
}
