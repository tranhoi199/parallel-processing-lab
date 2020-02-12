#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMTHRDS 8 
#define VECLEN 100000
pthread_mutex_t mutexsum;
int *a, *b;
long sum = 0.0;

void *dotprod(void *arg){
	/* Each thread works on a different set of data
	the offset is specified by the arg parameter. The size of
	the data for each thread is indicated by VECLEN*/
	int i , start, end, offset, len;
	long tid;
	tid = (long) arg;
	offset = tid;	
	len = VECLEN;
	start = offset*len;
	end = start + len;
	
	//perform my section of the dot prodcut
	printf("thread: %ld starting. start = %d end = %d\n",tid,start, end-1);
	for(i = start; i < end; i++){
		pthread_mutex_lock(&mutexsum);
		sum +=(a[i]*b[i]);
		pthread_mutex_unlock(&mutexsum);
	}
	printf("thread: %ld done. Global sum now is = %li\n", tid, sum);
	pthread_exit((void*) 0);
}
int main(int argc, char *argv[]){
	long i;
	void* status;
	pthread_t threads[NUMTHRDS];
	pthread_attr_t attr;	
	// Assign storage and initializs values 
	a = (int*) malloc(NUMTHRDS*VECLEN*sizeof(int));
	b = (int*) malloc(NUMTHRDS*VECLEN*sizeof(int));
	for(i = 0; i <VECLEN*NUMTHRDS; i++)
		a[i] = b[i] = 1;
	// initialize mutex variable 
	pthread_mutex_init(&mutexsum, NULL);
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(i = 0; i < NUMTHRDS; i++)
		pthread_create(&threads[i], &attr, dotprod, (void *)i);
	pthread_attr_destroy(&attr);
	
	// wait on the other threads for final result
	for(i = 0; i < NUMTHRDS; i++)
		pthread_join(threads[i], &status);
	
printf("Fianl Global Sum = %li\n", sum);
free(a);
free(b);

pthread_mutex_destroy(&mutexsum);
pthread_exit(NULL);

}
