__kernel void copy_str(__global char *str, __global int *n,__global int *len, __global char *results)
{
	int id = get_global_id(0);
	int i;
	int l=*len;
	for (i = id*l; i < ((id+1)*l); i ++) 
	{
		results[i] = str[i%l];
	}
}