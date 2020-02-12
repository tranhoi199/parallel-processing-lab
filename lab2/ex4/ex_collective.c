#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "mpi.h"
#define N 100
MPI_Status status;

double a[N][N],b[N][N],c[N][N];
int main(int argc, char**argv){
    int numtasks,rank,source,dest,rows,offset,i,j,k;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    if(rank == 0){
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                a[i][j]= 1;
                b[i][j]= 1;
            }
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Scatter(&a, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&mat_a[0], rows * N, MPI_INT, mat_a_recv, nRowEachP * N, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(&b, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    int c_send[rows][N];
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < N; j++){
            int temp = 0;
            for(int k = 0; k < N; k++)
                temp += a[
            
        }
    }
    
    
}
