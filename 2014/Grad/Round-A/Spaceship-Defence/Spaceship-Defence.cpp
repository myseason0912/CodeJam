// Spaceship-Defence.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define INT_MAX 1000000000

struct edge{
	int end;
	int weight;
	edge(int e,int w)
	{
		end = e;
		weight = w;
	}
	bool operator<(const edge& a) const
	{
		if (weight == a.weight)
			return end > a.end;
		return weight > a.weight;
	}
};

void dfs(vector<edge>* data,int N ,int s,int e,int& len,int& min)
{
	if (s == e && len < min)
	{
		min = len;
		return;
	}

	/*¼ôÖ¦*/
	if(len > min)
		return;

	for (int i = 0;i < data[s].size();i++)
	{
		if (data[s][i].weight != -1)
		{
			int tmp = data[s][i].weight;
			int i_tmp = INT_MAX;
			data[s][i].weight = -1;
			if (data[i][s].weight != -1)
			{
				i_tmp = data[i][s].weight;
				data[i][s].weight = -1;
			}
			len += tmp;
			dfs(data,N,data[s][i].end,e,len,min);
			len -= tmp;
			data[s][i].weight = tmp;
			if(i_tmp != INT_MAX)
				data[i][s].weight = i_tmp;
		}
	}
}

int dij(vector< edge >* data,int N,int s,int e)
{
	int ret = -1;
	if (s == e)
		return 0;
	int* dis = new int[N];
	bool* visited = new bool[N];
	memset(visited,0,N);
	priority_queue<edge> q;
	int k = 0;
	for (int i = 0;i < N;i++)
		dis[i] = INT_MAX;
	dis[s] = 0;

	q.push(edge(s,dis[s]));
	while(!q.empty())
	{
		k = q.top().end;q.pop();
		if (!visited[k])
		{
			visited[k] = true;
			for (int j = 0;j < data[k].size();j++)
			{
				int index = data[k][j].end;
				if (dis[index] > dis[k] + data[k][j].weight)
				{
					dis[index] = dis[k] + data[k][j].weight;
					q.push(edge(index,dis[index]));
				}
			}
		}
	}
	if (dis[e] == INT_MAX)
		ret = -1;
	else
		ret = dis[e];
	delete[] dis;
	delete[] visited;
	return ret;
}

int SPFA(vector< edge >* data,int N,int s,int e)
{
	int ret = -1;
	if (s == e)
		return 0;
	int* dis = new int[N];
	bool* visited = new bool[N];
	memset(visited,0,N);
	queue<int> q;
	int k = 0;
	for (int i = 0;i < N;i++)
		dis[i] = INT_MAX;
	dis[s] = 0;

	q.push(s);
	while(!q.empty())
	{
		k = q.front();q.pop();
		visited[k] = false;
		for (int j = 0;j < data[k].size();j++)
		{
			int index = data[k][j].end;
			if (dis[index] > dis[k] + data[k][j].weight)
			{
				dis[index] = dis[k] + data[k][j].weight;
				if (!visited[index])
				{
					visited[index] = true;
					q.push(index);
				}
			}
		}
	}
	if (dis[e] == INT_MAX)
		ret = -1;
	else
		ret = dis[e];
	delete[] dis;
	delete[] visited;
	return ret;
}

int bellman(vector<edge>* data,int N,int s,int e)
{
	int ret = -1;
	if (s == e)
		return 0;
	int* dis = new int[N];
	for (int i = 0;i < N;i++)
		dis[i] = INT_MAX;
	dis[s] = 0;

	for (int i = 0;i <= N - 1;i++)
		for (int j = 0;j < N;j++)
			for (int k = 0;k < data[j].size();k++)
			{
				int index = data[j][k].end;
				dis[index] = min(dis[index],dis[j]+data[j][k].weight);
			}

	for (int j = 0;j < N;j++)
		for (int k = 0;k < data[j].size();k++)
		{
			int index = data[j][k].end;
			if (dis[j]+data[j][k].weight < dis[index])
			{
				return -1;
			}
		}


	if (dis[e] == INT_MAX)
		ret = -1;
	else
		ret = dis[e];
	delete[] dis;
	return ret;
}

int main(int argc, char* argv[])
{
	FILE* in_file = fopen("E-small-practice.in","rb");
	FILE* out_file = fopen("E-small-practice.out","wb");
	if (!in_file || !out_file)
	{
		printf("open file error.\n");
		return 0;
	}
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 1;
	char color[5];
	while(i <= T)
	{
		int N = 0;
		fscanf(in_file,"%d ",&N);
		vector<string> colors;
		vector< edge >* map = new vector<edge>[N];
		for (int j = 0;j < N;j++)
		{
			fscanf(in_file,"%s ",color);
			colors.push_back(color);
			int index = colors.size() - 1;
			for (int k = 0;k < colors.size() - 1;k++)
			{
				if (colors[k] == colors[index])
				{
					map[k].push_back(edge(index,0));
					map[index].push_back(edge(k,0));
				}
			}
		}
		int M = 0;
		fscanf(in_file,"%d ",&M);
		for (int j = 0;j < M;j++)
		{
			int a = 0;
			int b = 0;
			int cost = 0;
			fscanf(in_file,"%d ",&a);
			fscanf(in_file,"%d ",&b);
			fscanf(in_file,"%d ",&cost);

			map[a-1].push_back(edge(b-1,cost));
		}

		int S = 0;
		fscanf(in_file,"%d ",&S);
		fprintf(out_file,"Case #%d:\n",i);
		for (int j = 0;j < S;j++)
		{
			int start = 0;
			int end = 0;
			fscanf(in_file,"%d ",&start);
			fscanf(in_file,"%d ",&end);
			int dis = INT_MAX;
			dis = bellman(map,N,start-1,end-1);
			fprintf(out_file,"%d\n",dis);

		}
		printf("Case #%d:\n",i);
		delete[] map;
		i++;
	}
	fclose(in_file);
	fclose(out_file);
	return 0;
}

