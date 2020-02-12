#define N 10
__global__ void add(int *a, int *b, int *c){
    int tid = threadIdx.x;
    
    if(tid < N){
        c[tid] = a[tid] + c[tid];
    }
}
int main(){
    int a[N] , b[N], c[N]; //host variable
    
    int *dev_a, *dev_b, *dec_c;
    
    for(int = 0; i < N; i++){
        a[i] = -i;
        b[i] = i*i;
    }
    
    cudaMalloc((void**) &dev_a, N*sizeof(int));
    cudaMalloc((void**) &dev_b, N*sizeof(int));
    cudaMalloc((void**) &dev_c, N*sizeof(int));
    
    // copy data from host to device
    cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemoryHostToDevice);
    cudaMemcpy(dec_c, b, N*sizeof(int), cudaMemoryHostToDevice);
    
    // launch the kernel code from the host
    add<<<N, 1>>>(dev_a, dev_b, dec_c);
    
    // Move the results from device back to host'smemory
    cudaMemcpy(c, dec_c, N*sizeof(int), cudaMemoryDeviceToHost);
    
    for(int i = 0; i < N; i++){
        printf("%d + %d = %d", a[i], b[i], c[i]);
    }
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dec_c);
    
}
