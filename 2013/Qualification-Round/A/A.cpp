// A.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <vector>
using namespace std;

#define MAX 4

enum {OK,X,O,NONE,END};

int decide(char** data,char c,int& count)
{
	count = 0;
	int ret = -1;
	vector<int> x_count;
	x_count.resize(MAX*2+2,0);
	int t_x = -1;
	int t_y = -2;
	for (int i = 0;i < MAX;i++)
		for (int j = 0;j < MAX;j++)
		{
			if (data[i][j] == c)
			{
				x_count[i]++;
				x_count[MAX+j]++;
			}
			if(i == j)
			{
				if(data[i][j] == c)
					x_count[MAX*2]++;
			}
			if (i + j == MAX-1)
			{
				if(data[i][j] == c)
					x_count[MAX*2+1]++;			
			}
			if (data[i][j] == 'T')
			{
				t_x = i;
				t_y = j;
			}
			if(data[i][j] != '.')
				count++;
		}
	for (int i = 0;i < MAX;i++)
		if(x_count[i] == MAX || (x_count[i] == MAX - 1 && t_x == i))
			ret = OK;

	if(ret == -1)
		for (int i = 0;i < MAX;i++)
			if(x_count[MAX+i] == MAX || (x_count[MAX+i] == MAX - 1 && t_y == i))
				ret = OK;
	if (ret == -1)
		if (x_count[MAX*2] == MAX || x_count[MAX*2+1] == MAX || (x_count[MAX*2] == MAX-1 && t_x == t_y ) || (x_count[MAX*2 + 1] == MAX-1 && t_x + t_y == MAX - 1))
			ret = OK;

	return ret;
}

int decide(char** data)
{
	int count = 0;
	int ret = decide(data,'X',count);
	if(ret == -1)
		ret = decide(data,'O',count);
	else
		ret = X;

	if(ret == -1)
		if(count == MAX*MAX)
			ret = NONE;
		else
			ret = END;
	else
		if(ret == OK)
			ret = O;
	return ret;
}

int main(int argc, char* argv[])
{
	freopen("A-large-practice.in", "rb", stdin);
	freopen("A-large-practice.out", "wb", stdout);

	int T = 0;
	scanf("%d ",&T);
	int i = 1;
	char** data = new char*[MAX];
	for (int j = 0;j < MAX;j++)
		data[j] = new char[MAX];
	while(i <= T)
	{
		for (int j = 0;j < MAX;j++)
			for (int k = 0;k < MAX;k++)
				scanf("%c ",&data[j][k]);
		int ret = decide(data);


		switch(ret)
		{
		case X:
			printf("Case #%d: X won\n",i);
			break;
		case O:
			printf("Case #%d: O won\n",i);
			break;
		case NONE:
			printf("Case #%d: Draw\n",i);
			break;
		case END:
			printf("Case #%d: Game has not completed\n",i);
			break;
		}

		i++;
	}
	for (int j = 0;j < MAX;j++)
	{
		delete[] data[j];
	}
	delete[] data;
	return 0;
}

