#include<mpi.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int r,c,mat[100],rec[100],avgt[100],avg=0;
	if(rank==0)
	{
		printf("Enter order");
		scanf("%d %d",&r,&c);
		printf("Enter elements");
		for(int i=0;i<r*c;i++)
			scanf("%d",&mat[i]);
	}
	MPI_Bcast(&c,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(mat,c,MPI_INT,rec,c,MPI_INT,0,MPI_COMM_WORLD);
	int sum=0;
	for(int i=0;i<c;i++)
		sum+=rec[i];
	int avgg=0;
	avgg=sum/c;
	//for(int i=0;i<r;i++)
	MPI_Gather(&avgg,1,MPI_INT,avgt,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Average row wise:");
		for(int i=0;i<r;i++)
			printf("\nRow: %d, Avg: %d",i,avgt[i]);
		int sumt=0;
		for(int i=0;i<r;i++)
			sumt+=avgt[i];
		avg=sumt/c;
		printf("\n Totes avg=%d",avg);
	}
	MPI_Finalize();
}