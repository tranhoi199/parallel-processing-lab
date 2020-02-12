#include "mat_mul_pthread.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <malloc/malloc.h>
// Define struct for matrix
typedef struct {
    int id;
    int dim;    // Dimension of matrices
    double **m_a;
    double **m_b;
    double **m_r;
    int *rows;  // Num of rows that each thread handles
} param_t;

/* The main function requires four arguments.
 ** Argument 1: The name of the function pMult
 ** Argument 2: Dimension of the matrices, N.
 ** Argument 3: The number of threads to use, C.
 ** Argument 4: A bool to determine if the matrices should be printed or not.
 **/
int main(int argc, const char *argv[]){
    if(argc >= 3){
        printf("1. Get parameters from users...\n");
        // Dimensions of matrices
        int dim = atoi(argv[1]);
        // Num of threads to run this program
        int num_threads = atoi(argv[2]);
        // Flag to choose for printing or not printing matrices
        int print_flag;
        if(argc == 4)
            print_flag = atoi(argv[3]);
        else
            print_flag = 0;

        /* Stores the number of rows which each thrtead will have to calculate
         * the results.*/
        int num_rows_per_thread[num_threads];
        int i, j;
        int row;
        int col;
        /* Used to determine which threads will handle which rows.*/
        int t_left = num_threads;
        int r_left = dim;
        /* Check success of pthread_create or pthread_join */
        long rc;
        /* Status of threads */
        void *status;

        /* Declare matrices and allocate memory */
        printf("2. Initialize matrices...\n");
        double **matrix_a;
        double **matrix_b;
        double **result;
        matrix_a = malloc(dim * sizeof(double *));
        matrix_b = malloc(dim * sizeof(double *));
        result = malloc(dim * sizeof(double *));

        /*
         ** for each of the pointeres in the tree matrices we want to allocate
         ** storage for the array's of floats */
        for(row = 0; row < dim; ++row) {
            matrix_a[row] = malloc(dim * sizeof(double));
        }

        for(row = 0; row < dim; ++row) {
            matrix_b[row] = malloc(dim * sizeof(double));
        }

        for(row = 0; row < dim; ++row) {
            result[row] = malloc(dim * sizeof(double));
        }

        for (row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                matrix_a[row][col] = rand() % 1000;

        for (row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                matrix_b[row][col] = rand() % 1000;

        for(row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                result[row][col] = 0;

        /* Initialize pthread and attributes */
        printf("3. Initialize pthreads...\n");
        pthread_t *thread;
        pthread_attr_t attr;
        thread = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        printf("4. Partitioning workload for each thread...\n");
        for(i = 0; i < num_threads; i++){
            num_rows_per_thread[i] = r_left / t_left;
            r_left -= num_rows_per_thread[i];
            --t_left;
        }

        /* Initialize data for threads and matrices */
        printf("5. Calculating...\n");
        //////////////////////////////////////////////////////////
        // TODO: comment out these lines below and write your code

        for(i = 0;i < num_threads;i++){
            param_t *p;
            p = (param_t*) malloc(sizeof(param_t));
            p->id = i;
            p->dim = dim;
            p->rows = num_rows_per_thread[i];
            p->m_a = matrix_a;
            p->m_b = matrix_b;
            p->m_r = result;
            pthread_create(&thread[i], NULL, worker,(void *)p);
        }
        for ( i = 0; i < num_threads; ++i ) {
            pthread_join( thread[i], NULL );
        }
        //mul_mat(0, &rows, dim, matrix_a, matrix_b, result);

        //////////////////////////////////////////////////////////

        /* Print matrices */
        if(print_flag == 1){
            printf("Printing out Matrix A: \n");
            print_matrix( matrix_a, dim );
            printf("Printing out Matrix B: \n");
            print_matrix( matrix_b, dim );
            printf("Printing out the result from A * B: \n");
            print_matrix( result, dim );
        }
        printf("6. Completed the main program. Exitting now.\n");
        return 1;

    }else{
        printf("Usage: ./mat_mul_pthread DIM NUM_THREADS [PRINT_FLAG]\n");
        printf("\t ./mat_mul_pthread 10 2 1\n");
        printf("\t ./mat_mul_pthread is run with matrix 10x10, 2 threads, print_flag = 1\n");
        return 0;
    }
}

void *worker(void *arg){
    param_t *p = (param_t *) arg;
    //printf("Thread %d: id = %d - num of handled rows = %d\n", p->id, p->id, *p->rows);
    mul_mat(p->id, p->rows, p->dim, p->m_a, p->m_b, p->m_r);
    pthread_exit(0);
}

void mul_mat(int id, int *rows, int dim, double **matrix_a, double **matrix_b, double **result){
    int i, k;
    int row, col, rowstart, rowend;
    double sum;

    //////////////////////////////////////////////////////////
    // TODO
    // Comment out these line below and write your code with a parallel version
    rowstart = id * (int)rows;
    rowend = (id + 1) * (int)rows;
    for(row = rowstart; row < rowend; row++){
        for(col = 0; col < dim; col++){
            sum = 0.0;
            for(k = 0; k < dim; k++){
                sum = sum + (matrix_a[row][k] * matrix_b[k][col]);
            }
            result[row][col] = sum;
        }
    }
    //////////////////////////////////////////////////////////
}

void print_matrix( double **matrix, int dim ) {
    int row;
    int col;
    for(row = 0; row < dim; row++) {
        printf("[ ");
        for(col = 0; col < dim; col++) {
            printf(" %f ", matrix[row][col]);
        }
        printf(" ]\n");
    }
    printf("\n");
}
