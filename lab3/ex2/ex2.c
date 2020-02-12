#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int sum_digit(unsigned long int x){
    int sum = 0;
    while(x != 0){
        sum += x % 10;
        x = x/10;
    }
    return sum;
}

int check_same_consec(unsigned long int x){
    int num1, num2;
    int result = 0;
    while(x != 0){
        num1 = x % 10;
        x = x/10;
        num2 = x%10;
        if(num1-num2 == 0){
            result = 1;
            break;
        }
    }
    return result;
}
int main(int argc, char** argv){
    int numtasks, rank;
    unsigned long int count = 0, total;
    unsigned long int begin = 100000, last = 999999, number_per_proc;
    //printf("%d\n", check_same_consec(1123456789));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    number_per_proc = 900000/numtasks;
    
    for(unsigned long int i = begin+(rank)*number_per_proc; i < begin + (rank+1)*number_per_proc; i++){
            if(sum_digit(i) != 7 && sum_digit(i) != 11 && sum_digit(i) != 13)
                if(!check_same_consec(i))
                    count = count + 1;
    }
    MPI_Reduce(&count, &total, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0)
    printf("total number satifaction %d\n", total);
    MPI_Finalize();
    return 0;
    
}
