#include "chol.h"

#define SIZE 100l
#define DEBUGSIZE 11            /* maximum size to print matrix and validate result */
float *A;
float *ASAVE;                   /* Matrix */

float compute(long int Count)
{
    int N = (int)Count;

    /* TODO */
    /* Modify this function to implement a parallel version with openmp */

    return (0.);
}

int prepare(long int Count)
{
    int i, j, n = Count;
    int Rcond;                  /* Condition number of A */

    int Matrix_elements = Count * Count;
    int Matrix_bytes = sizeof(float) * Matrix_elements;

    std::cout << "allocating 2 times " << Matrix_bytes / (1.0 * 1024 *
                                                          1024) << " MB" <<
        std::endl;

    /* Allocate the matrices */
    A = (float *)malloc(Matrix_bytes);
    if (A == NULL)
    {
        std::cout << "Could not allocate matrix A" << Count << std::endl;
        return -1;
    }

    ASAVE = (float *)malloc(Matrix_bytes);
    if (ASAVE == NULL)
    {
        std::cout << "Could not allocate matrix ASAVE" << Count << std::endl;
        return -1;
    }

    /* Generate condition number of A */
    Rcond = 1.0 + rand() % 1000;

    /* Initialize the matrices */
    for (i = 0; i < Matrix_elements; i++)
    {
        A[i] = rand() % 100;
        A[i] = (2.0 * A[i] - 1.0) * (Rcond - 1.0) / ((Rcond + 1.0) * n * 1000);
    }

    for (i = 0; i < n; i++)
        A[i + i * n] = 1.0 - A[i + i * n];

    /* make it really symmetric */
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            A[i * n + j] = A[j * n + i];

    /* save matrix into ASAVE */
    for (i = 0; i < Matrix_elements; i++)
        ASAVE[i] = A[i];

    return (0);
}

int cleanup(long int N)
{
    int i, j, k;
    float Standard;
    float S, Max;

    if (N < DEBUGSIZE)
    {
        printf("The Cholesky factor U  \n");
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
                printf("%9.5f ", A[j + i * N]);
            printf("\n");
        }
        printf("\nSAVE  \n");
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
                printf("%9.5f ", ASAVE[j + i * N]);
            printf("\n");
        }

        Max = 0;
        for (i = 0; i < N; i++)
        {
            for (j = i; j < N; j++)
            {
                for (S = 0., k = 0; k <= j && k <= i; k++)
                {
                    S += A[i * N + k] * A[j * N + k];
                }
                S -= ASAVE[i * N + j];
                if (ASAVE[i * N + j] != 0.)
                    S = fabs(S / ASAVE[i * N + j]);
                if (S > Max)
                    Max = S;
            }
        }
        std::
            cout << "Max % deviation from original matrix " << Max << std::endl;
    }

    /* Free the matrices */
    free(A);
    return (0);
}

int main(int argc, char *argv[])
{
    long int Count = SIZE;
    int Error;

    if (argc > 1)
    {
        Count = std::atoi(argv[1]);
        if (Count <= 0)
        {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: " << argv[0] << "N" << std::endl;
            std::cerr << "       N = size" << std::endl;
            return 1;
        }
    }

    std::cout << "counts:" << Count << std::endl;
    std::cout << "preparation starting" << std::endl;
    if (Error = prepare(Count) != 0)
        return Error;
    std::cout << "preparation done" << std::endl;
    unsigned long long start_ticks = my_getticks();
    Error = compute(Count);
    unsigned long long end_ticks = my_getticks();
    unsigned long long ticks = end_ticks - start_ticks;

    if (Error == 0)
        std::cout << "succeeded in ";
    else
        std::cout << "failed in ";
    std::cout << my_ticks_to_seconds(ticks) << " seconds." << std::endl;
    std::cout << "starting cleanup" << std::endl;
    return cleanup(Count);
}