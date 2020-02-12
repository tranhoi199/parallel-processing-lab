

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int *matrix, int N){
    for (int i = 0; i < N * N; i++){
        printf("%d %d ", i, matrix[i]);
    }
    printf("\n");
}

int main(int argc, char **argv){
    int N = 100; //Matrix size
    int MASTER = 0;

    int size, rank, nWorkers, source, dest;
    int nRowEachP; //rows for each process
    int i, j, k; //counter
    //int i, rank, size;

    int *mat_a;
    int *mat_b;
    int *mat_c;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double startTime = MPI_Wtime(); 

    if (rank == MASTER){
        mat_a = (int*) malloc(N * N * sizeof(int));
        mat_b = (int*) malloc(N * N * sizeof(int));
        mat_c = (int*) malloc(N * N * sizeof(int));

        for (i = 0; i < N * N; i++){
            mat_a[i] = 1;
            mat_b[i] = 1;
        }
        //printMatrix(mat_a, N);
        //printMatrix(mat_b, N);
        nRowEachP = N / size;
    }

    MPI_Bcast(&nRowEachP, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(&mat_b, N * N, MPI_INT, MASTER, MPI_COMM_WORLD);

    int * mat_a_recv = (int*) malloc(nRowEachP * N * sizeof(int));
    int * mat_c_recv = (int*) malloc(nRowEachP * N * sizeof(int));
    
    MPI_Scatter(&mat_a, nRowEachP * N, MPI_INT, mat_a_recv, nRowEachP * N, MPI_INT, MASTER, MPI_COMM_WORLD);

    if (rank != MASTER){
        mat_b = (int*) malloc(N * N * sizeof(int));
    }

    //each process multiply
    for (i = 0; i < nRowEachP; i++){
        for (j = 0; j < N; j++){
            int temp = 0;
            for (k = 0; k < N; k++){
                temp += mat_a_recv[i * N + k] * mat_b[k * N + j];
            }
            mat_c_recv[i * N + j] = temp;
        }
    }

    MPI_Gather(mat_c_recv, nRowEachP * N, MPI_INT, mat_c, nRowEachP * N, MPI_INT, 0, MPI_COMM_WORLD);

    //multiply for the rest of mat_a
    if (rank == 0){
        for (i = size * nRowEachP; i < N; i++){
            for (j = 0; j < N; j++){
                int temp = 0;
                for (k = 0; k < N; k++){
                    temp += mat_a[i * nRowEachP + k] * mat_b[k * N + j];
                }
                mat_c[i * N + j] = temp;
            }
        }
    }

    printf("Time: %f\n", MPI_Wtime() - startTime);

    MPI_Finalize();
    return 0;
}
