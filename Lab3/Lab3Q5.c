#include<mpi.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int arr[100],rec[100],n,n2,rec2[100];
	if(rank==0)
	{
		printf("Enter no of elements");
		scanf("%d",&n);
		printf("Enter elements");
		for(int i=0;i<n;i++)
			scanf("%d",&arr[i]);
		n2=n/size;
	}
	MPI_Bcast(&n2,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,n2,MPI_INT,rec,n2,MPI_INT,0,MPI_COMM_WORLD);
	for(int i=0;i<n2;i++)
	{
		if(rec[i]%2==0)
			rec[i]=1;
		else
			rec[i]=0;
	}
	MPI_Gather(rec,n2,MPI_INT,rec2,n2,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		int even=0,odd=0;
		for(int i=0;i<n;i++)
		{
			if(rec2[i]==0)
				odd+=1;
			else
				even+=1;
			printf("%d ",rec2[i]);
		}
		printf("\nEven(Count)=%d",even);
		printf("\nOdd(Count)=%d",odd);
	}
	MPI_Finalize();
}