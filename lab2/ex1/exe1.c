# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>


int PrintPrime( int n, int id, int p )
{
    int i;
    int j;
    int count;
    for ( i = 2 + id; i <= n; i = i + p )
    {
        count = 0;
        for ( j = 2; j*j<= i; j++ )
        {
            if ( ( i % j ) == 0 )
            {
                count = count +1;
                break;
            }
        }
        if(count == 0)
            printf(" %d \t,",i);
    }
    return 1;
}
int main ( int argc, char *argv[] )
{
    int id;
    int n;
    int maxvalue;
    int numprocess;
    maxvalue = 1000;
    
    MPI_Init ( &argc, &argv );
    MPI_Comm_size ( MPI_COMM_WORLD, &numprocess );
    MPI_Comm_rank ( MPI_COMM_WORLD, &id );
    if(id == 0)
        printf("Prime number from 1 to %d\n",maxvalue);
    
    n = maxvalue;
    MPI_Bcast( &n, 1, MPI_INT, 0, MPI_COMM_WORLD );
    PrintPrime( n, id, numprocess );
    MPI_Finalize();
    
    return 0;
}




