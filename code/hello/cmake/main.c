#include "hello_utils.h"
#include "goodbye_utils.h"
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
    if (ntimes < 2) {
        printf("Parameter must be at least 2.\n");
        return 2;
    }

    for (int i = 0; i < ntimes/2; i++)
        print_hello();
    for (int i = ntimes/2; i < ntimes; i++)
        print_goodbye();

    return 0;
}
