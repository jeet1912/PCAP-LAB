#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size;
	int a=20,b=5,res;
	//printf("Enter two numbers : ");
	//scanf("%d%d",&m,&n);
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("My rank is %d in total %d process\n",rank,size);
	switch(rank)
	{
		case 0: res= a+b;
				printf("Sum: %d\n",res);
				break;
		case 1: res= a-b;
				printf("Difference: %d\n",res);
				break;
		case 2: res= a*b;
				printf("Product: %d\n",res);
				break;
		case 3: res= a/b;
				printf("Quotient: %d\n",res);
				break;
		case 4: res= a%b;
				printf("Mod: %d\n",res);
				break;
	}
	MPI_Finalize();
	return 0;
}