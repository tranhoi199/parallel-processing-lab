#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    int numtasks,size, rank, dest, source, rc, count, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status Stat; // required variable for receive routines
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /* task 0 sends to task 1 and waits to receive a return message */
    if (rank == 0) {
        dest = 1;
        source = 1;
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
    }
    /* task 1 waits for task 0 message then returns a message */
    else if (rank == 1)
    {
        dest = 0;
        source = 0;
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }
    
    
    


/* query receive Stat variable and print message details */
MPI_Get_count(&Stat, MPI_CHAR, &count);
printf("Task %d: Receive %d char(s) from task %d with tag %d \n", rank, count,
       Stat.MPI_SOURCE, Stat.MPI_TAG);
MPI_Finalize();
return 0;
}
