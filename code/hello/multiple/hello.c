#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Need at least one parameter: ");
        printf("the number of times to print.\n");
        return 1;
    }

    int ntimes = atoi(argv[1]);
    for (int i = 0; i < ntimes; i++)
        print_hello();

    return 0;
}
