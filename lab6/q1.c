#include <stdio.h>
#include <time.h>
#include <string.h>
#include <CL/cl.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x10000)

int main(void)
{
	time_t start,end;
	start=clock();
	int i,n;
	char str[100];
	printf("Enter string ");
	gets(str);
	printf("ENter how many repeat \n");
	scanf("%d",&n);
	int len = strlen(str);
	//printf("\n Length of entered string is = %d",len);
	char *results = (char *)malloc(len *n* sizeof(char));
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp=fopen("q1.cl","r");

	if(!fp)
	{
		fprintf(stderr, "Failed to load kernel\n");
		getchar();
		exit(1);
	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size=fread(source_str,1,MAX_SOURCE_SIZE,fp);
	//printf("\n Number of bytes read from the file = %d",source_size);

	fclose(fp);
	cl_platform_id platform_id=NULL;
	cl_device_id device_id=NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret=clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret=clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);
	//printf("\n Return value after reading the device ids = %d",ret);
	//printf("\n DeviceID = %d",device_id);

	cl_context context= clCreateContext(NULL,1,&device_id, NULL, NULL, &ret);
	cl_command_queue command_queue=clCreateCommandQueue(context, device_id,CL_QUEUE_PROFILING_ENABLE, &ret);
	//printf("\n Return value after clCreateCommandQueue = %d",ret);

	cl_mem inp_mem=clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char),NULL,&ret);
	//printf("\n Return value after in clCreateBuffer = %d",ret);
	cl_mem n_mem=clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int),NULL,&ret);
	cl_mem len_mem=clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int),NULL,&ret);
	cl_mem out_mem=clCreateBuffer(context, CL_MEM_READ_WRITE, len*n*sizeof(char),NULL,&ret);
	//printf("\n Return value after out clCreateBuffer = %d",ret);

	ret= clEnqueueWriteBuffer(command_queue, inp_mem, CL_TRUE, 0, len*sizeof(char),str,0,NULL,NULL);
	ret= clEnqueueWriteBuffer(command_queue, n_mem, CL_TRUE, 0, sizeof(int),&n,0,NULL,NULL);
	ret= clEnqueueWriteBuffer(command_queue, len_mem, CL_TRUE, 0, sizeof(int),&len,0,NULL,NULL);
	//printf("\n Return value after clEnqueueWriteBuffer = %d",ret);

	cl_program program=clCreateProgramWithSource(context,1,(const char**)&source_str, (const size_t*)&source_size,&ret);
	ret=clBuildProgram(program,1,&device_id, NULL, NULL, NULL);
	//printf("\n Return value after clBuildProgram and deviceID = %d and %d",ret, device_id);

	cl_kernel kernel=clCreateKernel(program, "copy_str",&ret);
	ret= clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&inp_mem);
	ret= clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&n_mem);
	ret= clSetKernelArg(kernel,2,sizeof(cl_mem),(void *)&len_mem);
	ret= clSetKernelArg(kernel,3,sizeof(cl_mem),(void *)&out_mem);

	size_t global_item_size =n;
	size_t local_item_size=1;
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size,0, NULL, NULL);
	ret = clFinish(command_queue);
	cl_ulong time_start, time_end;
	double total_time;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start,NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end,NULL);
	total_time = (double)(time_end-time_start);
	ret=clEnqueueReadBuffer(command_queue, out_mem, CL_TRUE, 0, len*n*sizeof(char), results, 0, NULL, NULL);

	printf("\nResult after execution of Kernel code is %s \n",results);

	ret=clFlush(command_queue);
	ret=clReleaseKernel(kernel);
	ret=clReleaseProgram(program);
	ret=clReleaseMemObject(inp_mem);
	ret=clReleaseMemObject(out_mem);
	ret=clReleaseCommandQueue(command_queue);
	ret=clReleaseContext(context);

	free(results);
	getchar();
	return 0;
}
