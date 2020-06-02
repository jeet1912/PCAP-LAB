#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void q1(int *a, int *res, int m, int n) 
{
	int id=blockIdx.x*blockDim.x+threadIdx.x;
	res[id]=powf(a[id],blockIdx.x+1);
}

int main() {
	int *a, *res, m,n, i,j;
	int *d_a, *d_res;

	printf("Enter value of m: ");scanf("%d",&m);
	printf("Enter value of n: ");scanf("%d",&n);
	int size= sizeof(int)*m*n;
	a=(int*)malloc(size);
	res=(int*)malloc(size);
	printf("ENter input matrix : \n");
	for(i=0; i<m*n;i++)
		scanf("%d",&a[i]);
	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_res,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	q1<<<m,n>>>(d_a,d_res,m,n);	

	cudaMemcpy(res,d_res,size,cudaMemcpyDeviceToHost);

	printf("Result: \n");	
	for(i=0; i<m;i++)
	{
		for(j=0; j<n;j++)
		{
			printf("%d\t",res[i*n+j]);
		}
		printf("\n");
	}
	cudaFree(d_a);
	cudaFree(d_res);
	return 0;
}