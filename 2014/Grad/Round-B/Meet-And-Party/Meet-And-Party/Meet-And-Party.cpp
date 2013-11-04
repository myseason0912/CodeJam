// Meet-And-Party.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 4
struct node
{
	long long x;
	long long y;
};


long long getDisByDim(long long dim,long long* rect,char c)
{
	long long sum = 0;
	int x_s = 0;
	int x_b = 0;
	int y_s = 0;
	int y_b = 0;
	if (c == 'x')
	{
		x_s = 0;
		x_b = 2;
		y_s = 1;
		y_b = 3;
	}
	if (c == 'y')
	{
		x_s = 1;
		x_b = 3;
		y_s = 0;
		y_b = 2;
	}

	if ((dim <= rect[x_s] && dim <= rect[x_b]) || (dim >= rect[x_s] && dim >= rect[x_b]))
	{
		sum = (rect[y_b]-rect[y_s] + 1)*((rect[x_b]-rect[x_s]+1)*(rect[x_b]+rect[x_s])/2 - (rect[x_b]-rect[x_s] + 1)*dim);
		if(sum < 0)
			sum = 0 - sum;
	}
	else
	{
		long long mid = dim - rect[0];
		sum -= (rect[y_b]-rect[y_s] + 1)*((mid+1)*(dim+rect[x_s]) /2 - (mid+1)*dim);
		sum += (rect[y_b]-rect[y_s] + 1)*((rect[x_b]-rect[x_s]-mid)*(rect[x_b]+dim + 1) /2 - (rect[x_b]-rect[x_s]-mid)*dim);
	}

	return sum;
}


/*计算一个点和一个矩形之间的距离*/
long long getDis(node& a,long long* rect)
{
	long long ret_x = getDisByDim(a.x,rect,'x');
	long long ret_y =  getDisByDim(a.y,rect,'y');
	return ret_x + ret_y;
}

long long getPosition(long long** data,int N,int& x,int& y)
{
	long long bestDis = 0x7fffffffffffffff;

	for(int i = 0;i != N;i++)
	{
		for (int j = data[i][0];j <= data[i][2];j++)
		{
			for (int k = data[i][1];k <= data[i][3];k++)
			{
				long long tmp = 0;
				node t_node;
				t_node.x = j;
				t_node.y = k;
				for (int m = 0;m != N;m++)
				{
					tmp += getDis(t_node,data[m]);
				}
				if (tmp < bestDis || (tmp == bestDis && j < x) || (tmp == bestDis && j == x && k < y))
				{
					bestDis = tmp;
					x = j;
					y = k;
				}
			}
		}
	}

	return bestDis;
}


long long getPosition2(long long** data,int N,int& x,int& y)
{
	/*分维度到各个矩阵的距离和*/
	map<int,long long > x_dis;
	map<int,long long> y_dis;
	for (int i = 0;i != N;i++)
	{
		/*遍历所有的x*/
		for (int j = data[i][0];j <= data[i][2];j++)
		{
			if (x_dis.find(j) == x_dis.end())
			{
				long long tmp = 0;
				for (int k = 0;k != N;k++)
				{
					tmp += getDisByDim(j,data[k],'x');
				}
				x_dis.insert(make_pair(j,tmp));
			}
		}
		/*遍历所有的y*/
		for (int j = data[i][1];j <= data[i][3];j++)
		{
			if (y_dis.find(j) == y_dis.end())
			{
				long long tmp = 0;
				for (int k = 0;k != N;k++)
				{
					tmp += getDisByDim(j,data[k],'y');
				}
				y_dis.insert(make_pair(j,tmp));
			}
		}
	}

	long long min_dis = 0x7fffffffffffffff;
	/*遍历所有的节点*/
	for (int i = 0;i != N;i++)
	{
		for (int j = data[i][0];j <= data[i][2];j++)
		{
			for (int k = data[i][1];k <= data[i][3];k++)
			{
				long long tmp = 0;
				map<int,long long >::iterator iter = x_dis.find(j);
				if (iter != x_dis.end())
					tmp += iter->second;
				iter = y_dis.find(k);
				if (iter != y_dis.end())
					tmp += iter->second;

				if(tmp < min_dis || (tmp == min_dis && j < x) || (tmp == min_dis && j == x && k < y))
				{
					min_dis = tmp;
					x = j;
					y = k;
				}

			}
		}
	}
	
	return min_dis;
}

int main(int argc, char* argv[])
{
	FILE* input = fopen("B-large-practice.in","rb");
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
		long long** data = new long long*[N];
		for (int j = 0;j < N;j++)
		{
			data[j] = new long long[MAX];
		}

		for (int j = 0;j != N;j++)
			for (int k = 0;k != MAX;k++)
				fscanf(input,"%lld ",&data[j][k]);

		int x = 0;
		int y = 0;
		long long dis = getPosition2(data,N,x,y);
		printf("Case #%d: %d %d %lld\n",i+1,x,y,dis);
		fprintf(output,"Case #%d: %d %d %lld\n",i+1,x,y,dis);

		for (int j = 0;j != N;j++)
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

