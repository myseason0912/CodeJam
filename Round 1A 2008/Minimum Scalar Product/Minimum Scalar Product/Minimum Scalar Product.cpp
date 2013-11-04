// Minimum Scalar Product.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <algorithm>
using namespace std;

bool bigger(int a,int b)
{
	return a > b;
}

bool smaller(int a,int b)
{
	return a < b;
}

int main(int argc, char* argv[])
{
	FILE* input = fopen("A-large-practice.in","rb");
	FILE* output = fopen("output","wb");
	if (input == NULL || output == NULL)
	{
		printf("open input file error\n");
		return 0;
	}
	int T = 0;
	fscanf(input,"%d ",&T);
	int i = 0;
	while (i < T)
	{
		int n = 0;
		fscanf(input,"%d ",&n);
		int* x = (int*)calloc(n,sizeof(n));
		int* y = (int*)calloc(n,sizeof(n));
		for (int j = 0;j < n;j++)
		{
			fscanf(input,"%d ",&x[j]);
		}

		for (int j = 0;j < n;j++)
		{
			fscanf(input,"%d ",&y[j]);
		}

		sort(x,x+n,smaller);
		sort(y,y+n,bigger);

		long long sum = 0;
		for (int j = 0;j < n;j++)
		{
			sum += (long long)x[j]*y[j];
		}
		free(x);
		free(y);

		fprintf(output,"Case #%d: %lld\n",i+1,sum);
		i++;
	}

	fclose(input);
	fclose(output);
	return 0;
}

