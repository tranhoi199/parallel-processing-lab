#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

    
void mul_mat( int id, int *rows, int dim, double **matrix_a, double **matrix_b, double **result );
void *worker(void *arg);
void print_matrix( double **matrix, int dim);
