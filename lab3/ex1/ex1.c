#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int numtasks, rank;
    int sendbuf, recvbuf;
    int count = 1, recvcount ;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    sendbuf = rank + 1;
    MPI_Reduce(&sendbuf, &recvbuf, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0){
        printf("irecv = %d\n", recvbuf);
        printf("Check with p(p+1)/2 = %d\n", numtasks*(numtasks+1)/2);
    }
    MPI_Finalize();
    return 0;
}
