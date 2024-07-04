#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <omp.h>

#define N 4096

double A[N][N];
double B[N][N];
double C[N][N];

float tdiff(struct timeval* start, struct timeval* end)
{
    return (end->tv_sec - start->tv_sec)
           + 1e-6 * (end->tv_usec - start->tv_usec);
}

void mm_base(double *restrict C, int n_C,
             double *restrict A, int n_A,
             double *restrict B, int n_B,
             int n)
{
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i * n_C + j] += A[i * n_A + k] * B[k * n_B + j];
}

void mm_dac(double *restrict C, int n_C,
            double *restrict A, int n_A,
            double *restrict B, int n_B,
            int n)
{
    assert((n & (-n)) == n);
    if (n <= 32) {
        mm_base(C, n_C, A, n_A, B, n_B, n);
    } else {
#define X(M,r,c) (M + (r * (n_ ## M) + c) * (n / 2))
#pragma omp task
        {
            mm_dac(X(C, 0, 0), n_C, X(A, 0, 0), n_A, X(B, 0, 0), n_B, n / 2);
        }
#pragma omp task
        {
            mm_dac(X(C, 0, 1), n_C, X(A, 0, 0), n_A, X(B, 0, 1), n_B, n / 2);
        }
#pragma omp task
        {
            mm_dac(X(C, 1, 0), n_C, X(A, 1, 0), n_A, X(B, 0, 0), n_B, n / 2);
        }
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 0), n_A, X(B, 0, 1), n_B, n / 2);
#pragma omp taskwait

#pragma omp task
        {
            mm_dac(X(C, 0, 0), n_C, X(A, 0, 1), n_A, X(B, 1, 0), n_B, n / 2);
        }
#pragma omp task
        {
            mm_dac(X(C, 0, 1), n_C, X(A, 0, 1), n_A, X(B, 1, 1), n_B, n / 2);
        }
#pragma omp task
        {
            mm_dac(X(C, 1, 0), n_C, X(A, 1, 1), n_A, X(B, 1, 0), n_B, n / 2);
        }
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 1), n_A, X(B, 1, 1), n_B, n / 2);
#pragma omp taskwait
    }
}

int main()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double) rand() / (double) RAND_MAX;
            B[i][j] = (double) rand() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

#pragma omp parallel
    {
#pragma omp single
        {
            mm_dac((double*) C, N, (double*) A, N, (double*) B, N, N);
        }
    }


    gettimeofday(&end, NULL);
    printf("%0.6f\n", tdiff(&start, &end));

    return 0;
}
