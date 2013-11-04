// Sorting.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	FILE* in_file = fopen("C-large-practice.in","rb");
	FILE* out_file = fopen("C-large-practice.out","wb");

	int T = 0;
	fscanf(in_file,"%d",&T);
	int i = 1;
	while (i <= T)
	{
		int n = 0;
		fscanf(in_file,"%d ",&n);
		int* data = new int[n];
		vector<int> odd;
		vector<int> even;
		for (int j = 0;j < n;j++)
		{
			fscanf(in_file,"%d ",&data[j]);
			if ((data[j] & 0x1 ) == 1)
			{
				odd.push_back(data[j]);
			}
			else
			{
				even.push_back(data[j]);
			}
		}
		sort(odd.begin(),odd.end());
		sort(even.begin(),even.end());

		int o_index = 0;
		int e_index = even.size() - 1;
		fprintf(out_file,"Case #%d: ",i);
		for (int j = 0;j < n;j++)
		{
			if ((data[j] & 0x1 ) == 1)
			{
				data[j] = odd[o_index++];
			}
			else
			{
				data[j] = even[e_index--];
			}
			fprintf(out_file,"%d",data[j]);
			if (j != n - 1)
				fprintf(out_file," ");
		}
		fprintf(out_file,"\n");
		delete[] data;
		i++;
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}

