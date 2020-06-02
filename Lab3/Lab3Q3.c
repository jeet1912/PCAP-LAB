#include<mpi.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	char str[100],rec[100];
	int n,totcount[100];
	if(rank==0)
	{
		printf("Enter string\n");
		fgets(str,100,stdin);
		n=strlen(str)/size;
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str,n,MPI_CHAR,rec,n,MPI_CHAR,0,MPI_COMM_WORLD);
	int count=0;
	for(int i=0;i<n;i++)
	{
		if(rec[i]=='a'||rec[i]=='e'||rec[i]=='i'||rec[i]=='o'||rec[i]=='u')
		{
			continue;
		}
		count+=1;
	}
	MPI_Gather(&count,1,MPI_INT,totcount,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		int sum=0;
		for(int i=0;i<size;i++)
			sum+=totcount[i];
		printf("Total number of non-vowels: %d",sum);
	}
	MPI_Finalize();
}
