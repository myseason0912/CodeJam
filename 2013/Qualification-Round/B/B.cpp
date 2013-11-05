// B.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <vector>
using namespace std;

int decide(int** data,int M,int N)
{
	int ret = 0;
	vector<int> r_max ;
	r_max.resize(M,0);
	vector<int> c_max;
	c_max.resize(N,0);
	for(int i  = 0;i < M;i++)
	{
		for(int j = 0;j < N;j++)
		{
			if(data[i][j] > r_max[i])
				r_max[i] = data[i][j];
			if(data[i][j] > c_max[j])
				c_max[j] = data[i][j];
		}
	}

	int** dest = new int*[M];
	for(int i = 0;i < M;i++)
	{
		dest[i] = new int[N];
		for(int j = 0;j < N;j++)
			dest[i][j] = r_max[i];
	}

	for(int i = 0;i < N;i++)
		for(int j = 0;j < M;j++)
			if(dest[j][i] > c_max[i])
				dest[j][i] = c_max[i];

	for(int i = 0;i < M;i++)
	{
		for(int j = 0;j < N;j++)
		{
			if(data[i][j] != dest[i][j])
			{
				ret = -1;
				break;
			}
		}
		if(ret == -1)
			break;
	}

	for(int i = 0;i < M;i++)
		delete[] dest[i];
	
	delete[] dest;
	return ret;
}

int main(int argc, char* argv[])
{
	freopen("B-large-practice.in", "rb", stdin);
	freopen("B-large-practice.out", "wb", stdout);

	int T = 0;
	scanf("%d ",&T);
	int i = 1;
	while(i <= T)
	{
		int M = 0;
		int N = 0;
		scanf("%d ",&M);
		scanf("%d ",&N);
		int** data = new int*[M];
		for(int j = 0;j < M;j++)
		{
			data[j] = new int[N];
			for(int k = 0;k < N;k++)
				scanf("%d ",&data[j][k]);
		}
		
		int ret = decide(data,M,N);
		if(ret == 0)
			printf("Case #%d: YES\n",i);
		else
			printf("Case #%d: NO\n",i);
		
		for(int j = 0;j < M;j++)
			delete[] data[j];
		delete[] data;
		i++;
	}
	return 0;
}

