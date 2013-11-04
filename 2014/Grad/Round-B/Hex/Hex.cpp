// Hex.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
enum {B,R,NONE};

#define INI_MIN -2
#define START -1

const int dx[6] = {-1,1,0,0,-1,1};
const int dy[6] = {0,0,1,-1,1,-1};

void getPath(int **data,int N,int x,int y,int value,vector<pair<int,int> >& road,vector< vector<pair<int,int> > >& paths)
{	
	bool path = false;
	if ((value == R && x == N-1) || (value == B && y == N-1))
		path = true;

	if(path)
	{
		/*获得一条路径*/
		vector< pair<int,int> > way;
		way.assign(road.begin(),road.end());
		way.push_back(make_pair(x,y));
		paths.push_back(way);
		return;
	}

	road.push_back(make_pair(x,y));
	int tmp = data[x][y];
	data[x][y] = -1;
	for (int i = 0;i < 6;i++)
	{
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx >= 0 && tx < N && ty >= 0 && ty < N && data[tx][ty] == value)
			getPath(data,N,tx,ty,value,road,paths);

	}
	vector<pair<int,int> >::iterator iter = road.end();
	iter--;
	road.erase(iter);
	
	data[x][y] = tmp;
}

struct node {
	int pre_x;
	int pre_y;
};

void widSearch(int** data,int N,int value,vector< vector<pair<int,int> > >& path)
{
	/*广度搜索*/
	node** flag = new node*[N];
	for (int i = 0;i < N;i++)
	{
		flag[i] = new node[N];
		for (int k = 0;k < N;k++)
		{
			flag[i][k].pre_x = INT_MIN;
			flag[i][k].pre_y = INT_MIN;
		}
	}
	for (int i = 0;i < N;i++)
	{
		deque<pair<int,int> > nodes;
		if (value == R && data[0][i] == value)
		{
			nodes.push_back(make_pair(0,i));
			flag[0][i].pre_x = START;
			flag[0][i].pre_y = START;
		}
		if (value == B && data[i][0] == value)
		{
			nodes.push_back(make_pair(i,0));
			flag[i][0].pre_x = START;
			flag[i][0].pre_y = START;
		}
		while(!nodes.empty())
		{
			pair<int,int> tmp = nodes.front();
			nodes.pop_front();
			int x = tmp.first;
			int y = tmp.second;
			bool found = false;
			if ((value == R && x == N-1) || (value == B && y == N-1))
				found = true;
			if (found)
			{	/*获得一条路径*/
				int pre_x = flag[x][y].pre_x;
				int pre_y =  flag[x][y].pre_y;
				vector<pair<int,int> > way;
				way.push_back(make_pair(x,y));
				while(pre_x != START && pre_y != START)
				{
					way.push_back(make_pair(pre_x,pre_y));
					x = pre_x;
					y = pre_y;
					pre_x = flag[x][y].pre_x;
					pre_y = flag[x][y].pre_y;
				}
				path.push_back(way);
			}

			for (int j = 0;j < 6;j++)
			{
				int tx = x + dx[j];
				int ty = y + dy[j];
				if (tx >= 0 && tx < N && ty >= 0 && ty < N && data[tx][ty] == value)
				{
					if (flag[tx][ty].pre_x == INT_MIN)
					{
						nodes.push_back(make_pair(tx,ty));
						flag[tx][ty].pre_x = x;
						flag[tx][ty].pre_y = y;
					}
				}
			}

		}
		for (int j = 0;j < N;j++)
		{
			for (int k = 0;k < N;k++)
			{
				flag[j][k].pre_x = INT_MIN;
				flag[j][k].pre_y = INT_MIN;
			}
		}
	}

	for (int i = 0;i < N;i++)
	{
		delete[] flag[i];
	}
	delete[] flag;
}

bool hasCutPoint(vector< vector<pair<int,int> > >& paths)
{
	/*所有的路径是否存在割点*/
	for (int i = 0;i != paths[0].size();i++)
	{
		for (int j = 1;j != paths.size();j++)
		{
			if (find(paths[j].begin(),paths[j].end(),paths[0][i]) != paths[j].end())
			{
				if (j == paths.size() - 1)
				{
					return true;
				}
				continue;
			}
			else
			{
				break;
			}
		}
	}
	return false;
}

int decide(int** data,int N)
{
	int blue_count = 0;
	int red_count = 0;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (data[i][j] == B)
			{
				blue_count++;
			}
			if (data[i][j] == R)
			{
				red_count++;
			}
		}
	}
	if (abs(blue_count - red_count) > 1)
		return -1;

	vector< vector<pair<int,int> > > r_paths;
	vector< vector<pair<int,int> > > b_paths;
	widSearch(data,N,R,r_paths);
	widSearch(data,N,B,b_paths);
	//for (int i = 0;i < N;i++)
	//{
	//	if (data[0][i] == R)
	//	{
	//		vector<pair<int,int> > road;
	//		getPath(data,N,0,i,R,road,r_paths);
	//	}
	//	if (data[i][0] == B)
	//	{
	//		vector<pair<int,int> > road;
	//		getPath(data,N,i,0,B,road,b_paths);	
	//	}
	//}

	int ret = -1;
	if (r_paths.size() == 0 && b_paths.size() == 0)
	{
		ret = NONE;
	}
	else
	{
		if (b_paths.size() >= 1 && r_paths.size() == 0)
		{
			if (b_paths.size() == 1 )
				ret = B;
			else
			{
				/*判断是否有割点*/
				if (hasCutPoint(b_paths))
					ret = B;
				else
					ret = -1;
			}
		}
		else
		{
			if (r_paths.size() >= 1 && b_paths.size() == 0)
			{
				if (r_paths.size() == 1 )
					ret = R;
				else
				{
					/*判断是否有割点*/
					if (hasCutPoint(r_paths))
						ret = R;
					else
						ret = -1;
				}
			}
			else
			{
				/*路径数均大于0*/
				ret = -1;
			}
		}
	}
	if (ret == B && blue_count < red_count)
	{
		ret = -1;
	}	
	if (ret == R && red_count < blue_count)
	{
		ret = -1;
	}
	return ret;
}


int main(int argc, char* argv[])
{
	char file_path[] = "C-large-practice.in";
	FILE* in_file = fopen(file_path,"rb");
	if (in_file == NULL)
	{
		printf("open input file %s error\n",file_path);
		return 0;
	}
	FILE* out_file = fopen("output","wb");
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 0;
	while (i < T)
	{
		int N = 0;
		fscanf(in_file,"%d ",&N);
		int** data = (int**)calloc(N,sizeof(int*));
		for (int j = 0;j < N;j++)
		{
			data[j] = (int*)calloc(N,sizeof(int));
		}

		for (int j = 0;j < N;j++)
		{
			for (int k = 0;k < N;k++)
			{
				char c = 'c';
				fscanf(in_file,"%c ",&c);
				switch(c)
				{
					case 'B':
						data[j][k] = B;
						break;
					case 'R':
						data[j][k] = R;
						break;
					case '.':
						data[j][k] = -1;
						break;
					default:
						break;
				}
			}
		}

		int ret = decide(data,N);
		switch(ret)
		{
			case B:
				fprintf(out_file,"Case #%d: Blue wins\r\n",i+1);
				break;
			case R:
				fprintf(out_file,"Case #%d: Red wins\r\n",i+1);
				break;
			case NONE:
				fprintf(out_file,"Case #%d: Nobody wins\r\n",i+1);
				break;
			case -1:
				fprintf(out_file,"Case #%d: Impossible\r\n",i+1);
				break;
			default:
				break;
		}

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

