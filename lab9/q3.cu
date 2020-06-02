#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void q3a(int *a, int *b,int *c, int wa, int wb) 
{
	int id=threadIdx.x , sum;
	for(int i=0; i< wb; i++)
	{
		sum=0;
		for(int j=0; j< wa;j++)
		{
			sum+=(a[id*wa+j]*b[j*wb+i]);
		}
		c[id*wb+i]=sum;
	}
}

__global__ void q3b(int *a, int *b,int *c, int ha, int wa, int wb) 
{
	int id=threadIdx.x ,sum;
	for(int i=0; i< ha; i++)
	{
		sum=0;
		for(int j=0; j< wa;j++)
		{
			sum+=(a[i*wa+j]*b[j*wb+id]);
		}
		c[i*wb+id]=sum;
	}
}

__global__ void q3c(int *a, int *b,int *c, int wa, int wb) 
{
	int rid=threadIdx.y;
	int cid=threadIdx.x;
	int sum=0;
	for(int i=0; i< wa;i++)
	{
		sum+=a[rid*wa+i]*b[i*wb+cid];
	}
	c[rid*wb+cid]=sum;

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
	int *a, *b, m,n,q, i;
	int *d_a,*d_b, *d_res;

	printf("Enter value of m: ");scanf("%d",&m);
	printf("Enter value of n: ");scanf("%d",&n);
	printf("Enter value of q: ");scanf("%d",&q);
	int size= sizeof(int)*m*n;
	a=(int*)malloc(size);

	int *resa=(int*)malloc(size);
	int *resb=(int*)malloc(size);
	int *resc=(int*)malloc(size);

	printf("ENter input matrix A (m*n): \n");
	for(i=0; i<m*n;i++)
		scanf("%d",&a[i]);

	b=(int*)malloc(size);
	printf("ENter input matrix B (p*q): \n");
	for(i=0; i<n*q;i++)
		scanf("%d",&b[i]);
	
	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_res,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	
	// ha= m , wa=n=p wb= q
	//CALL A
	q3a<<<1,m>>>(d_a,d_b,d_res,n,q);	
	cudaMemcpy(resa,d_res,size,cudaMemcpyDeviceToHost);
	display(resa,m,q);
	//CALL B
	q3b<<<1,q>>>(d_a,d_b,d_res,m,n,q);	
	cudaMemcpy(resb,d_res,size,cudaMemcpyDeviceToHost);
	display(resb,m,q);
	//CALL C
	dim3 blo(1,1);
	dim3 thr(q,m);
	q3c<<<blo,thr>>>(d_a,d_b,d_res,n,q);	
	cudaMemcpy(resc,d_res,size,cudaMemcpyDeviceToHost);
	display(resc,m,q);
	

	cudaFree(d_a);
	cudaFree(d_res);
	return 0;
}