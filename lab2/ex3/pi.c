#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#define PI 3.1415926535897
void Get_input(int argc, char* argv[], int myRank, long* totalNumTosses_p);
int calPI(long iter, int rank);




int main(int argc, char** argv)
{
    int size,rank;
    long  pi_part, pi_sum, numPoint, pointProcess;

    numPoint = atoi(argv[1]);
    
    //*---------------------------------------*//
    //time(&start); // Start counting time
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    pointProcess = numPoint / size;
    MPI_Barrier(MPI_COMM_WORLD);
    //start = MPI_Wtime();
    pi_part = calPI(pointProcess,rank);
    //finish = MPI_Wtime();
    MPI_Reduce(&pi_part,&pi_sum,1, MPI_LONG, MPI_SUM,0,MPI_COMM_WORLD);
    
    if(rank == 0){
        //*---------------------------------------*//
        double pi = 4.0*(double)pi_sum/numPoint;
        printf("Gia tri cua pi: %.10lf \n", pi);          // Print PI Number
    }
    MPI_Finalize();
    return 0;
}


int calPI(long iter, int rank) {
    int numPi;
    unsigned int seed = rand()%32767;
    for(uint64_t i = 0; i < iter; ++i) {
        // Create point
        double x = (double)rand_r(&seed)/(double)RAND_MAX;
        double y = (double)rand_r(&seed)/(double)RAND_MAX;
        // Calculator radius
        double r = sqrt(x*x + y*y);
        // Is it in a circle
        if(r <= 1) numPi=numPi+1;
    }
    return numPi;
}
