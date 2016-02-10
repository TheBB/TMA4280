#include <stdio.h>

#ifdef HAS_MKL
#include "mkl_cblas.h"
#else
#include "cblas.h"
#endif

void print_matrix(char* desc, int m, int n, double* a, int lda)
{
    int i, j;
    printf( "\n %s\n", desc );
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf(" %8.2f", a[i+j*lda]);
        printf("\n");
    }
}


void print_int_vector(char* desc, int n, int* a) {
    int j;
    printf("\n %s\n", desc);
    for(j = 0; j < n; j++)
        printf(" %8i", a[j]);
    printf("\n");
}


void cblas_test()
{
    const int lda = 3, ldb = 3, ldc = 3;
    int m = 3, n = 3, k = 3;
    double alpha = 1.0, beta = 1.0;
    double a[] = {0.11, 0.21, 0.12,
                  0.15, 0.13, 0.17,
                  0.22, 0.13, 0.23};
    double b[] = {1011, 1021, 1018,
                  1031, 1012, 1021,
                  1022, 1032, 1015};
    double c[] = {0.00, 0.00, 0.00,
                  0.00, 0.00, 0.00,
                  0.00, 0.00, 0.00};

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);

    print_matrix("Multiplication result", m, n, c, 1);
}


void lapack_test()
{
    int n = 5, nrhs = 3, lda = 5, ldb = 5, info;

    int ipiv[5];
    double a[25] = {
        6.80, -2.11,  5.66,  5.97,  8.23,
        -6.05, -3.30,  5.36, -4.44,  1.08,
        -0.45,  2.58, -2.70,  0.27,  9.04,
        8.32,  2.71,  4.35, -7.17,  2.14,
        -9.67, -5.14, -7.26,  6.08, -6.87
    };
    double b[15] = {
        4.02,  6.19, -8.22, -7.57, -3.03,
        -1.56,  4.00, -8.67,  1.75,  2.86,
        9.81, -4.09, -4.57, -8.61,  8.99
    };

    dgesv_(&n, &nrhs, a, &lda, ipiv, b, &ldb, &info);

    print_matrix("Solution", n, nrhs, b, ldb);
    print_matrix("Details of LU factorization", n, n, a, lda);
    print_int_vector("Pivot indices", n, ipiv);
}


int main(int argc, char **argv)
{
    cblas_test();
    lapack_test();

    return 0;
}
