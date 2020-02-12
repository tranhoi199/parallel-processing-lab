
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define N  100
int a[N][N], b[N][N], finalC[N][N] ;

int main(int argc, char *argv[])
{
    int  pid, size , i, j, k;
    int nRow;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // max number of processors
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); // our rank
    
    // root se khoi tao bien
    if (pid ==0 ) {
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                a[i][j]= 1;
                b[i][j]= 1;
            }
        }
    }
    
    nRow = N/ size;
    MPI_Barrier(MPI_COMM_WORLD);
    
    int recA[nRow][N];
    int recC[nRow][N];
    
    MPI_Scatter( a ,  nRow*N , MPI_INT , recA , N * nRow, MPI_INT , 0, MPI_COMM_WORLD ) ;
    MPI_Bcast ( b, N*N , MPI_INT , 0 , MPI_COMM_WORLD ) ;
    
    for ( i=0 ; i< (nRow) ; i++ )
    for (  j = 0 ; j<N ; j++ )
    {
        recC[i][j] = 0 ;
        for (  k = 0 ; k<N ; k++ )
        recC[i][j] += recA[i][k]*b[k][j];
        
    }
    if(N % size != 0){
        if(pid == 0){
            // se tinh tu dong thu i-th den dong thu N-th do N khong chia het cho N
            // nen dong thu i-th = N dong - so dong chua duoc tinh
            
            for(i = N - ( N % nRow ); i < N; i++)
            for(j = 0; j < N; j++){
                int c_ij = 0;
                for( k = 0; k < N; k++ ){
                    c_ij += a[j][k]*b[k][j];
                }
                finalC[i][j] = c_ij;
                
                // gan lai gia tri
                
            }
        }
    }
    
    MPI_Gather( recC , N*nRow , MPI_INT , &finalC , nRow * N , MPI_INT , 0, MPI_COMM_WORLD ) ;
    MPI_Barrier(MPI_COMM_WORLD);
    if (pid == 0) {
        printf("Here is the result matrix:\n");
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++)
            printf("%d   ", finalC[i][j]);
            printf ("\n");
        }
    }
    
    MPI_Finalize();
    
    return 0;
}


