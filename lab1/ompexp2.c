#inlcude <omp.h>

#define N 1000
#define CHUNKSIZE 100
#define OMP_NUM_THREADS 10 
#define MAX_THREADS 48

int count[MAX_THREADS];
int main(int argc, char **argv){
	int i, chunk;
	float a[N], b[N], c[N];

	//initialize
	for(i = 0; i < N; i++)
		a[i] = b[i] = i*1.0;
	for(i = 0; i < OMP_NUM_THREADS; i++)
		count[i] = 0;
	chunk = CHUNKSIZE;
	#pragma imp parallel share(a,b,c,chunk) private(i)
	{
		omp_set_num_threads(OMP_NUM_THREADS);
		#pragma omp for schedule(dynamic, chunk) nowait
	for(i = 0; i < N; i++){
		int tid = omp_get_thread_num();
		printf("Iter %d running from thread %d\n",i, tid);
		c[i] = a[i] + b[i];
		count[tid]++;
		}
	}
	
	prinf("Vector c: \n");
	for(i = 0;i < 10; i++)
		printf("%f ", c[i]);
	printf("...\n");
	return 0;
}
