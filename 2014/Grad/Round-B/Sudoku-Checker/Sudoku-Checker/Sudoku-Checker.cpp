// Sudoku-Checker.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool checkArray(vector<int>& data,int MAX)
{
	sort(data.begin(),data.end());
	bool ret = true;
	for (int i = 0;i != data.size();i++)
	{
		if (data[i] != i + 1)
		{
			ret = false;
			break;
		}
	}
	return ret;
}

bool checkMatrix(int** data,int start_m,int end_m,int start_n,int end_n,int MAX)
{
	vector<int> tmp;
	for (int i = start_m;i != end_m;i++ )
		for (int j = start_n;j != end_n;j++)
			tmp.push_back(data[i][j]);
	return checkArray(tmp,MAX);
}

int main(int argc, char* argv[])
{
	FILE* input = fopen("A-large.in","rb");
	FILE* output = fopen("output","wb");
	if (input == NULL || output == NULL)
	{
		printf("open input file error\n");
		return 0;
	}
	int T = 0;
	int N = 0;
	fscanf(input,"%d ",&T);
	int i = 0;
	while (i < T)
	{
		fscanf(input,"%d ",&N);
		int size = N*N;
		int** data = new int*[size];
		for (int j = 0;j != size;j++)
		{
			data[j] = new int[size];
		}

		for (int j = 0;j != size;j++)
			for (int k = 0;k != size;k++)
				fscanf(input,"%d ",&data[j][k]);

		bool yes = true;
		/*检查行*/
		for (int j = 0;j != size;j++)
		{
			vector<int> tmp;
			tmp.resize(size);
			for (int k = 0;k != size;k++)
			{
				tmp[k] = data[j][k];
			}
			if (!checkArray(tmp,size))
			{
				yes = false;
				goto NO;
			}
		}

		/*检查列*/
		for (int j = 0;j != size;j++)
		{
			vector<int> tmp;
			tmp.resize(size);
			for (int k = 0;k != size;k++)
			{
				tmp[k] = data[k][j];
			}
			if (!checkArray(tmp,size))
			{
				yes = false;
				goto NO;
			}
		}

		/*检查matrix*/
		for (int j = 0;j != size;j += N)
		{
			for (int k = 0;k != size;k += N)
			{
				if (!checkMatrix(data,j,j+N,k,k+N,size))
				{
					yes = false;
					goto NO;
				}
			}
		}

NO:
		if (yes)
		{
			printf("Case #%d: Yes\n",i+1);
			fprintf(output,"Case #%d: Yes\n",i+1);
		}
		else
		{
			printf("Case #%d: No\n",i+1);
			fprintf(output,"Case #%d: No\n",i+1);
		}

		for (int j = 0;j != size;j++)
		{
			delete[] data[j];
		}
		delete[] data;
		i++;
	}
	fclose(input);
	fclose(output);

	return 0;
}

