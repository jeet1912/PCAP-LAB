#include <mpi.h>
#include <stdio.h>
int prime(int n)
{
	for(int i=2; i<n;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("Rank: %d, Size: %d\n",rank,size);
	if(rank==0)
	{
		for(int i=2;i<51;i++)
		{
			if(prime(i))
				printf("%d ",i);
		}
	}
	else
	{
		for(int i=52;i<=100;i++)
		{
			if(prime(i))
				printf("%d ",i);
		}
	}
	MPI_Finalize();
	return 0;
}