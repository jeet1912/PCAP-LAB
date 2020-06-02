#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void q2a(int *a, int *b,int *res, int m, int n) 
{
	int id=threadIdx.x;
	for(int i=0; i<n; i++)
		res[id*n+i]=a[id*n+i]+b[id*n+i];

}

__global__ void q2b(int *a, int *b,int *res, int m, int n) 
{
	int id=threadIdx.x;
	for(int i=0; i<n; i++)
		res[i*n+id]=a[i*n+id]+b[i*n+id];
}

__global__ void q2c(int *a, int *b,int *res, int m, int n) 
{
	int id=blockIdx.x*blockDim.x+threadIdx.x;
	res[id]=a[id]+b[id];
}
void display(int *res,int m,int n)
{
	printf("Result: \n");	
	for(int i=0; i<m;i++)
	{
		for(int j=0; j<n;j++)
		{
			printf("%d\t",res[i*n+j]);
		}
		printf("\n");
	}
}

int main() {
	int *a, *b, m,n, i;
	int *d_a,*d_b, *d_res;

	printf("Enter value of m: ");scanf("%d",&m);
	printf("Enter value of n: ");scanf("%d",&n);
	int size= sizeof(int)*m*n;
	a=(int*)malloc(size);

	int *resa=(int*)malloc(size);
	int *resb=(int*)malloc(size);
	int *resc=(int*)malloc(size);

	printf("ENter input matrix A : \n");
	for(i=0; i<m*n;i++)
		scanf("%d",&a[i]);

	b=(int*)malloc(size);
	printf("ENter input matrix B : \n");
	for(i=0; i<m*n;i++)
		scanf("%d",&b[i]);
	
	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_res,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	
	//CALL A
	q2a<<<1,m>>>(d_a,d_b,d_res,m,n);	
	cudaMemcpy(resa,d_res,size,cudaMemcpyDeviceToHost);
	display(resa,m,n);
	//CALL B
	q2b<<<1,n>>>(d_a,d_b,d_res,m,n);	
	cudaMemcpy(resb,d_res,size,cudaMemcpyDeviceToHost);
	display(resb,m,n);
	//CALL C
	q2c<<<m,n>>>(d_a,d_b,d_res,m,n);	
	cudaMemcpy(resc,d_res,size,cudaMemcpyDeviceToHost);
	display(resc,m,n);
	

	cudaFree(d_a);
	cudaFree(d_res);
	return 0;
}