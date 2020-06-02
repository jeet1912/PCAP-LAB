#include <stdio.h>
#include "mpi.h"
#define MCW MPI_COMM_WORLD

int main(){
	int n, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MCW, &n);
	MPI_Comm_rank(MCW, &rank);
	// printf("Rank = %d\tSize = %d\n", rank, n);
	int num = rank+1;
	int factNum;
	MPI_Scan(&num, &factNum, 1, MPI_INT, MPI_PROD, MCW);
	// printf("%d->factNum = %d\n", rank, factNum);
	int ans;
	MPI_Reduce(&factNum, &ans, 1, MPI_INT, MPI_SUM, 0, MCW);
	if(rank == 0){
		printf("Final ans = %d\n", ans);
	}
	MPI_Finalize();
	return 0;
}