#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>
#include <time.h>

#define N 12         // size of array

__global__ void linalg(int *a,int *b, int *c, int *scalar) {
	int tid = blockIdx.x *  blockDim.x + threadIdx.x;
		int s = *scalar;
        if(tid < N){
          c[tid] = s * a[tid] + b[tid];
        }
}

int main(int argc, char *argv[])  {
	int T = 10, B = 1;            // threads per block and blocks per grid
	int a[N],b[N],c[N], *scalar;

	scalar = (int*)malloc(sizeof(int));
	int *dev_a, *dev_b, *dev_c, *dev_scalar;

	printf("Enter the scalar:\n");
	scanf("%d", scalar);

	printf("Size of array = %d\n", N);
	do {
		printf("Enter number of threads per block: ");
		scanf("%d",&T);
		printf("\nEnter number of blocks per grid: ");
		scanf("%d",&B);
		if (T * B != N) printf("Error T x B != N, try again");
	} while (T * B != N);

	cudaMalloc((void**)&dev_a,N * sizeof(int));
	cudaMalloc((void**)&dev_b,N * sizeof(int));
	cudaMalloc((void**)&dev_c,N * sizeof(int));
	cudaMalloc((void**)&dev_scalar, sizeof(int));

	for(int i=0;i<N;i++) {    // load arrays with some numbers
		a[i] = i;
		b[i] = i*1;
	}

	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_scalar, scalar, sizeof(int), cudaMemcpyHostToDevice);

	linalg<<<B,T>>>(dev_a, dev_b, dev_c, dev_scalar);

	cudaMemcpy(c,dev_c,N*sizeof(int),cudaMemcpyDeviceToHost);

	for(int i=0;i<N;i++) {
		printf("(%d * %d) + %d = %d\n", *scalar, a[i], b[i], c[i]);
	}

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	return 0;
}
