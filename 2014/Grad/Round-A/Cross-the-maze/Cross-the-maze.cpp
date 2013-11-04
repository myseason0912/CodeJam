// Cross-the-maze.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#define MAX 4

bool getPath(char** data,int N,int s_x,int s_y,int e_x,int e_y,int& step,string& path)
{
	if (s_x == e_x && s_y == e_y)
	{
		return true;
	}
	step += 1;

	
}

int main(int argc, char* argv[])
{
	FILE* in_file = fopen("C-large-practice.in","rb");
	FILE* out_file = fopen("output","wb");
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 0;
	while (i < T)
	{
		int N = 0;
		fscanf(in_file,"%d ",&N);
		char** data = new char*[N];
		for (int j = 0;j < N;j++)
		{
			data[j] = new char[N];
		}

		for (int j = 0;j < N;j++)
		{
			for (int k = 0;k < N;k++)
			{
				fscanf(in_file,"%c ",&data[j][k]);
			}
		}
		int* loc = new int[MAX];
		for (int j = 0;j != MAX;j++)
		{
			fscanf(in_file,"%d ",&loc[j]);
			loc[j] -= 1;
		}
		int step = 0;
		string path = "";
	

		delete[] loc;
		for (int j = 0;j < N;j++)
		{
			delete[] data[j];
		}
		delete[] data;
		i++;
	}
	fclose(out_file);
	fclose(in_file);
	return 0;
}

