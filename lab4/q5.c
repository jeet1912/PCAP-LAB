#include <stdio.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(){
	int n, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MCW, &n);
	MPI_Comm_rank(MCW, &rank);
	int mat[n][n];
	if(rank == 0){
		printf("Enter %d * %d matrix\n", n, n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				scanf("%d", &mat[i][j]);
	}
	// Scatter n rows to n processes
	int row[n], presum[n];
	MPI_Scatter(mat, n, MPI_INT, row, n, MPI_INT, 0, MCW);
	MPI_Scan(row, presum, n, MPI_INT, MPI_SUM, MCW);
	printf("%d->\n", rank);
	fflush(stdout);
	for(int i=0; i<n; i++){
		printf("%d\t", presum[i]);
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
	MPI_Finalize();
	return 0;
}