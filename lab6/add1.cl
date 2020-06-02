__kernel void copy_str(__global char *str, __global int *n,__global int *len, __global char *results)
{
	size_t id = get_global_id(0);
	int i;
	int l=*len;
	for (i = id; i < l * (*n); i += l) 
	{
		results[i] = str[id];
	}
}