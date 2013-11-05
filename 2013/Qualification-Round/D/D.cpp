// D.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <vector>
using namespace std;

#define MAX_T 128


int main(int argc, char* argv[])
{
	freopen("test.txt", "rb", stdin);
	freopen("test.out", "wb", stdout);

	int T = 0;
	scanf("%d ",&T);
	int i = 1;
	while(i <= T)
	{
		int K = 0;
		int N = 0;
		scanf("%d ",&K);
		scanf("%d ",&N);
		int* begin_key = new int[K];
		int* keys = new int[N];
		vector<int>* has_keys = new vector<int>[N];
		int* keys_count = new int[MAX_T];
		memset(keys_count,0,MAX_T*sizeof(int));
		vector<int>* keys_for_door = new vector<int>[MAX_T];
		for (int j = 0;j < K;j++)
		{
			scanf("%d ",&begin_key[j]);
			keys_count[begin_key[j]]++;
		}

		for(int j = 0;j < N;j++)
		{
			scanf("%d ",&keys[j]);
			keys_for_door[keys[j]].push_back(j);
			int count = 0;
			scanf("%d ",&count);
			for(int k = 0;k < count;k++)
			{
				int tmp = 0;
				scanf("%d ",&tmp);
				has_keys[j].push_back(tmp);
				keys_count[tmp]++;
			}
		}
		
		bool equal = true;
		for(int j = 0;j < MAX_T;j++)
		{
			if(keys_count[j] != keys_for_door[j].size())
			{
				equal = false;
				break;
			}
		}

		if(!equal)
		{
			printf("Case #%d: IMPOSSIBLE\n",i);
		}
		else
		{
			
		}

		delete[] keys_count;
		delete[] keys_for_door;
		delete[] has_keys;
		delete[] keys;
		delete[] begin_key;
		i++;
	}
	return 0;
}


