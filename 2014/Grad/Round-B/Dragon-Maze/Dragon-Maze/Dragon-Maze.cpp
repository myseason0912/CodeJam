// Dragon-Maze.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <queue>
using namespace std;
#define MAX 4

#define INT_MAX 1000000
#define INT_MIN 0

const int dx[] = {0, 0, 1, -1}, dy[] = {-1, 1, 0, 0};

void getMaxEnergy(int** data,int M,int N,int x,int y,int end_x,int end_y,int s,int e,int& min_s,int& max_e)
{
	e += data[x][y];
	s += 1;
	if (min_s != 0 && s > min_s)
		return;
	if (x == end_x && y == end_y)
	{
		if(min_s == 0)
			min_s = s;
		if (s < min_s)
			max_e = e;
		else if(s == min_s && e > max_e)
			max_e = e;
		return;
	}
	int tmp = data[x][y];
	data[x][y] = -1;

	for (int i = 0;i < 4;i++)
	{
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx >= 0 && tx < M && ty >= 0 && ty < N && data[tx][ty] > 0)
		{
			getMaxEnergy(data,M,N,tx,ty,end_x,end_y,s,e,min_s,max_e);
		}
	}
	data[x][y] = tmp;
}

struct node{
	int dis;
	int energy;
	node()
	{
		dis = INT_MAX;
		energy = INT_MIN;
	}
};

void bfs(int** data,int M,int N,int s_x,int s_y,int end_x,int end_y,int& max_e)
{
	node** step = new node*[M];
	for (int i = 0;i < M;i++)
	{
		step[i] = new node[N];
	}

	queue<pair<int,int> > nodes;
	nodes.push(make_pair(s_x,s_y));
	step[s_x][s_y].dis = 0;
	step[s_x][s_y].energy = data[s_x][s_y];
	while (!nodes.empty())
	{
		int x = nodes.front().first;
		int y = nodes.front().second;
		nodes.pop();
		for (int i = 0;i < 4;i++)
		{
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx >= 0 && tx < M && ty >= 0 && ty < N && data[tx][ty] > 0)
			{
				if (step[tx][ty].dis < step[x][y].dis + 1)
					continue;
				if(step[tx][ty].dis == INT_MAX)
					nodes.push(make_pair(tx,ty));
				step[tx][ty].energy = max(step[tx][ty].energy, step[x][y].energy + data[tx][ty]);
				step[tx][ty].dis = step[x][y].dis + 1;
			}
		}

	}
	max_e = step[end_x][end_y].energy;
	for (int i = 0;i < M;i++)
	{
		delete[] step[i];
	}
	delete[] step;
}

int main(int argc, char* argv[])
{
	FILE* input = fopen("D-large-practice.in","rb");
	FILE* output = fopen("output","wb");
	if (input == NULL || output == NULL)
	{
		printf("open input file error\n");
		return 0;
	}
	int T = 0;
	int N = 0;
	int M = 0;
	fscanf(input,"%d ",&T);
	int i = 0;
	while (i < T)
	{
		fscanf(input,"%d %d",&M,&N);
		int* loc = new int[MAX];
		for (int j = 0;j != MAX;j++)
			fscanf(input,"%d ",&loc[j]);
		
		int** data = new int*[M];
		for (int j = 0;j != M;j++)
		{
			data[j] = new int[N];
		}

		for (int j = 0;j != M;j++)
			for (int k = 0;k != N;k++)
				fscanf(input,"%d ",&data[j][k]);
		i++;
		int max_e = 0;
		int min_s = 0;
		//getMaxEnergy(data,M,N,loc[0],loc[1],loc[2],loc[3],0,0,min_s,max_e);
		bfs(data,M,N,loc[0],loc[1],loc[2],loc[3],max_e);
		if (max_e == 0)
			fprintf(output,"Case #%d: Mission Impossible.\n",i);
		else
			fprintf(output,"Case #%d: %d\n",i,max_e);
		delete[] loc;
		for (int j = 0;j != M;j++)
		{
			delete[] data[j];
		}
		delete[] data;
	}
	fclose(input);
	fclose(output);
	return 0;
}

