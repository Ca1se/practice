#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define n 4096

double A[n][n];
double B[n][n];
double C[n][n];

float tdiff(struct timeval* start, struct timeval* end)
{
    return (end->tv_sec - start->tv_sec)
           + 1e-6 * (end->tv_usec - start->tv_usec);
}

int main()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double) rand() / (double) RAND_MAX;
            B[i][j] = (double) rand() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int s = 32;

#pragma omp parallel for collapse(2)
    for (int ih = 0; ih < n; ih += s) {
        for (int jh = 0; jh < n; jh += s) {
            for (int kh = 0; kh < n; kh += s) {
                for (int i = 0; i < s; i++) {
                    for (int k = 0; k < s; k++) {
                        for (int j = 0; j < s; j++) {
                            C[ih + i][jh + j] += A[ih + i][kh + k] * B[kh + k][jh + j];
                        }
                    }
                }
            }
        }
    }

    gettimeofday(&end, NULL);
    printf("%0.6f\n", tdiff(&start, &end));

    return 0;
}
