// Bad-Horse.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define MAX_NAME_LEN 1024

enum {B,R};

bool isDivide(vector< vector<int> >& g,vector<int>& nodes)
{
	/*对所有的节点进行bfs，尝试着色*/
	int start = 0;
	while(true)
	{
		queue<int> d_node;
		d_node.push(start);
		nodes[start] = B;
		while (!d_node.empty())
		{
			int id = d_node.front();
			d_node.pop();
			for (int j = 0;j < g[id].size();j++)
			{
				int index = g[id][j];
				if (nodes[index] == -1)
				{
					nodes[index] = 1 - nodes[id];
					d_node.push(index);
				}
				else
				{
					if (nodes[index] == nodes[id])
					{
						return false;
					}
				}
			}
		}

		bool end = true;
		for (int i = 0;i < nodes.size();i++)
		{
			if (nodes[i] == -1)
			{
				start = i;
				end = false;
				break;
			}
		}

		if(end)
			break;

	}

	return true;
}

int main(int argc, char* argv[])
{
	FILE* in_file = fopen("A-small-practice-2.in","rb");
	FILE* out_file = fopen("A-small-practice-2.out","wb");
	if (!in_file || !out_file)
	{
		printf("open file error.\n");
		return 0;
	}
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 1;
	char name1[MAX_NAME_LEN];
	char name2[MAX_NAME_LEN];
	while(i <= T)
	{
		int M = 0;
		fscanf(in_file,"%d ",&M);
		map<string,int> name2id;
		int id = 0;
		vector< vector<int> > g;
		vector<int> nodes;
		for (int j = 0;j < M;j++)
		{
			fscanf(in_file,"%s %s ",name1,name2);
			map<string,int>::iterator iter = name2id.find(name1);
			int id_1 = 0;
			if(iter == name2id.end())
			{
				id_1 = id;
				name2id.insert(make_pair(name1,id++));
			}
			else
				id_1 = iter->second;

			int id_2 = 0;
			iter = name2id.find(name2);
			if(iter == name2id.end())
			{
				id_2 = id;
				name2id.insert(make_pair(name2,id++));
			}
			else
				id_2 = iter->second;
		
			int bigger = max(id_1,id_2);
			if (g.size() <= bigger)
				g.resize(bigger+1);
			g[id_1].push_back(id_2);
			g[id_2].push_back(id_1);

		}
		nodes.resize(id,-1);

		bool ret = isDivide(g,nodes);
		if (ret)
			fprintf(out_file,"Case #%d: Yes\n",i);
		else
			fprintf(out_file,"Case #%d: No\n",i);

		i++;

	}
	fclose(in_file);
	fclose(out_file);
	return 0;
}

