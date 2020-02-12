/*
 @author: Nguyen Viet Sang
 ID: 1512798
 @date: 24/10/2018
 **/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100

int a[N][N], b[N][N], c[N][N];

int main(int argc, char **argv){
   
    
    int size, rank, nWorkers, source, dest, i, j, k;
    int nRowEachP; //rows for each process
    //int i, j, k; //counter
    //int i, rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        for ( i = 0; i < N * N; i++){
            for(j = 0; j < N; j++){
                a[i][j] = 1;
                b[i][j] = 1;
            }
        }
        //printMatrix(mat_a, N);
        //printMatrix(mat_b, N);
        
    }
    MPI_Barrier(MPI_COMM_WORLD);
    nRowEachP = N / size;
    MPI_Bcast(&b, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Bcast(N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Bcast(&nRowEachP, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD);
    int a_recv[nRowEachP][N] ;
    int c_recv[nRowEachP][N] ;
    
    MPI_Scatter(a, nRowEachP * N, MPI_INT, &a_recv, nRowEachP * N, MPI_INT, 0, MPI_COMM_WORLD);
    //each process multiply
    for (i = 0; i < nRowEachP; i++){
        for (j = 0; j < N; j++){
            int temp = 0;
            for (k = 0; k < N; k++){
                temp += a_recv[j][k] * b[k][j];
            }
            c_recv[i][j] = temp;
        }
    }
    
    MPI_Gather(&c_recv, nRowEachP * N, MPI_INT, c, nRowEachP * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    //multiply for the rest of mat_a
    if (rank == 0){
        for (i = size * nRowEachP; i < N; i++){
            for (j = 0; j < N; j++){
                int temp = 0;
                for (k = 0; k < N; k++){
                    temp += a[j][k] * b[k][j];
                }
                c[i][j] = temp;
            }
        }
        for (i=0; i<N; i++) {
            for (int j=0; j<N; j++)
            printf("%6.2f   ", c[i][j]);
            printf ("\n");
        }
    }
    MPI_Finalize();
    return 0;
}

