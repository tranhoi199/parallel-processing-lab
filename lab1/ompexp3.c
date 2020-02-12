#include <omp.h>
#include <stdio.h>

#define N 1000
#define CHUNKSIZE 100
#define OMP_NUM_THREADS 12
#define MAX_THREADS 48

// global variables

int count[MAX_THREADS];

int main(int argc, char** argv){
    int i, chunk;
    float a[N], b[N], c[N], d[N];
    
    //some initialize
    for(i=0; i< N ;i++){
        a[i] = i*1.0;
        b[i] = i + 2.0;
        
    }
    for(i = 0 ; i<OMP_NUM_THREADS;i++)
        count[i] = 0;
    chunk = CHUNKSIZE;
#pragma omp parallel shared(a,b,c,d) private(i)
{
        omp_set_num_threads(OMP_NUM_THREADS);
#pragma omp sections nowait
        {
#pragma omp section
    for(i = 0; i<N;i++){
        int tid_s1 = omp_get_thread_num();
        printf("\tIter %d running from thread %d\n",i, tid_s1);
        c[i] = a[i] + b[i];
        count[tid_s1]++;
            }
#pragma omp section
    for(i = 0; i < N; i++){
        int tid_s2 = omp_get_thread_num();
        printf("\t Iter %d running from thread %d \n",i,tid_s2);
        d[i] = a[i] + b[i];
        count[tid_s2]++;
            }
        }
}
    printf("Vector c: \n\t"); for(i = 0; i < 10; i++){
        printf("%f ", c[i]);
    }
    printf("...\n");
    printf("Vector d: \n\t");
    for(i = 0; i < 10; i++){
        printf("%f ", d[i]);
    }
        printf("...\n");
        /* Statistic */
        printf("Num of iter with thread:\n"); for(i = 0; i < MAX_THREADS; i++){
            if (count[i] != 0)
            printf("\tThread %d run %d iter.\n", i, count[i]);
        }
        return 0;
}
