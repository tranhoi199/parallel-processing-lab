#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Get_input(int argc, char* argv[], int rank, long* numPoint_p);
long Toss (long Numperpros, int rank);

int main(int argc, char** argv) {
    int rank, size;
    long numPoint, Numperpros, pi_part, pi_sum;
    double  piEstimate;
    double PI25DT = 3.141592653589793238462643;         /* 25-digit-PI*/
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Get_input(argc, argv, rank, &numPoint);
    Numperpros = numPoint/size;
    
    MPI_Barrier(MPI_COMM_WORLD);
    pi_part = Toss(Numperpros, rank);

    MPI_Reduce(&pi_part, &pi_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        piEstimate = (4*pi_sum)/((double) numPoint);
        
        printf("Pi is approximately %.16f\n", piEstimate);
    }
    MPI_Finalize();
    return 0;
}

/* Function gets input from command line for numPoint */
void Get_input(int argc, char* argv[], int rank, long* numPoint_p){
    if (rank == 0) {
        if (argc!= 2){
            fprintf(stderr, "usage: mpirun -np <N> %s <number of tosses> \n", argv[0]);
            fflush(stderr);
            *numPoint_p = 0;
        } else {
            *numPoint_p = atoi(argv[1]);
        }
    }
    // Broadcasts value of numPoint to each process
    MPI_Bcast(numPoint_p, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    // 0 numPoint ends the program
    if (*numPoint_p == 0) {
        MPI_Finalize();
        exit(-1);
    }
}

/* Function implements Monte Carlo version of tossing darts at a board */
long Toss (long processTosses, int rank){
    long toss, numberInCircle = 0;
    double x,y;
    unsigned int seed = (unsigned) time(NULL);
    srand(seed + rank);
    for (toss = 0; toss < processTosses; toss++) {
        x = rand_r(&seed)/(double)RAND_MAX;
        y = rand_r(&seed)/(double)RAND_MAX;
        if((x*x+y*y) <= 1.0 ) numberInCircle++;
    }
    return numberInCircle;
}
