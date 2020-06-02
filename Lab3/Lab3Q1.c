#include<mpi.h>
#include<stdio.h>
#include<string.h>
int calcFact(int a,int pos)
{
	int f=1;
	for(int i=1;i<=a;i++)
	{
		f*=i;
	}
	return f;
}
int main(int argc,char* argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int num[100],fact[100],fac,sum=0,n;
	if(rank==0)
	{
		printf("Enter n");
		scanf("%d",&n);
		printf("Enter numbers");
		for(int i=0;i<n;i++)
			scanf("%d",&num[i]);
	}
	MPI_Scatter(num,1,MPI_INT,&fac,1,MPI_INT,0,MPI_COMM_WORLD);
	fac=calcFact(fac,rank);
	MPI_Gather(&fac,1,MPI_INT,fact,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		for(int i=0;i<n;i++)
			sum+=fact[i];
		printf("Sum=%d",sum);
	}
	MPI_Finalize();
}