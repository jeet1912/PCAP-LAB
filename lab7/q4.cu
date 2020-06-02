#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>
#include <time.h>

#define N 16         // size of array

__global__ void calcsin(double *a, double *c) {
	int tid = blockIdx.x *  blockDim.x + threadIdx.x;
        if(tid < N){
        	c[tid] = sin(a[tid]);
        }
}

int main(int argc, char *argv[])  {
	int T = 10, B = 1;            // threads per block and blocks per grid
	double a[N], c[N];
	double *dev_a, *dev_c;

	printf("Size of array = %d\n", N);
	do {
		printf("Enter number of threads per block: ");
		scanf("%d",&T);
		printf("\nEnter nuumber of blocks per grid: ");
		scanf("%d",&B);
		if (T * B != N) printf("Error T x B != N, try again");
	} while (T * B != N);

	cudaMalloc((void**)&dev_a,N * sizeof(double));
	cudaMalloc((void**)&dev_c,N * sizeof(double));

	for(int i = 0; i < N; i++) {    // load array with some numbers
		a[i] = (double)i;
	}

	cudaMemcpy(dev_a, a , N*sizeof(double),cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c , N*sizeof(double),cudaMemcpyHostToDevice);

	calcsin<<<B,T>>>(dev_a,dev_c);

	cudaMemcpy(c,dev_c,N*sizeof(double),cudaMemcpyDeviceToHost);


	for(int i = 0; i < N; i++) {
		printf("sin(%lf) = %lf\n",a[i], c[i]);
	}
	// clean up
	cudaFree(dev_a);
	cudaFree(dev_c);
	return 0;
}
