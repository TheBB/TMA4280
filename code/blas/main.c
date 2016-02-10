#include <stdio.h>
#include "cblas.h"

int main(int argc, char **argv)
{
    const int lda = 3, ldb = 3, ldc = 3;
    int m = 3, n = 3, k = 3;
    float alpha = 1.0, beta = 1.0;
    float a[] = {0.11, 0.21, 0.12,
                 0.15, 0.13, 0.17,
                 0.22, 0.13, 0.23};
    float b[] = {1011, 1021, 1018,
                 1031, 1012, 1021,
                 1022, 1032, 1015};
    float c[] = {0.00, 0.00, 0.00,
                 0.00, 0.00, 0.00,
                 0.00, 0.00, 0.00};

    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);

    printf("[ %g, %g, %g\n",   c[0], c[1], c[2]);
    printf("  %g, %g, %g\n",   c[3], c[4], c[5]);
    printf("  %g, %g, %g ]\n", c[6], c[7], c[8]);

    return 0;
}
