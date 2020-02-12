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

int main(int argc, char **argv)
{
    
    int numtasks,rank,source,dest,rows,offset,i,j,k;
    
    struct timeval start, stop;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    if (rank == 0) {
        // khoi tao du lieu
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                a[i][j]= 1;
                b[i][j]= 1;
            }
        }
        
        gettimeofday(&start, 0);
        
        // so hang ma tran khac rank 0 se tinh
        rows = N / (numtasks - 1 );
        
        offset = 0;
        
        for (dest=1; dest<=numtasks - 1; dest++)
        {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
            MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            offset = offset + rows;
        }
        
        // truong hop process chan va con mot so hang cua ma tran chua duoc tinh
        // neu rows = N / (numtasks - 1) bi lam tron xuong thi rows*(numtasks -1) nho hon N
        // Nen 1 so hang van chua duoc tinh
        if(rows*(numtasks-1) < N){
            // se tinh tu dong thu i-th den dong thu N-th do N khong chia het cho N
            // nen dong thu i-th = N dong - so dong chua duoc tinh
            
            for(i = N - ( N % rows ); i < N; i++)
                for(j = 0; j < N; j++){
                    int c_ij = 0;
                    for( k = 0; k < N; k++ )
                        c_ij += a[j][k]*b[k][j];
                    
                    // gan lai gia tri
                    c[i][j] = c_ij;
            }
        }
        
        // nhan du lieu tu cac process khac
        for (i=1; i<=numtasks - 1; i++)
        {
            
            MPI_Recv(&offset, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
        }
        
        gettimeofday(&stop, 0);
        
        printf("Here is the result matrix:\n");
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++)
                printf("%6.2f   ", c[i][j]);
            printf ("\n");
        }
        
        fprintf(stdout,"Time = %.6f\n\n",
                (stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
        
    }
    
    // cac process khac root se nhan
    if (rank > 0) {
        source = 0;
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        
        // thuc hien viec nhan ma tran
        for (k=0; k<N; k++)
            for (i=0; i<rows; i++) {
                c[i][k] = 0.0;
                for (j=0; j<N; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
