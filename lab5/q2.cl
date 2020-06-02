__kernel void complement(__global int *A, __global int *C)
{
	int i=get_global_id(0);\
	int p=1;
	C[i]=0;
	while(A[i]>0)
	{
		C[i]=C[i]+p*!(A[i]%10);
		A[i]/=10;
		p*=10;
	}
}