// Moist.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <vector>
using namespace std;

int sort_count(vector<string>& names)
{
	int dollar = 0;
	string max = names[0];
	for (int i = 1;i < names.size();i++)
	{
		if (names[i].compare(max) < 0)
		{
			dollar++;
		}
		else
		{
			max = names[i];
		}
	}
	return dollar;
}

int main(int argc,char* argv[])
{
	FILE* in_file = fopen("C-small-practice-2.in","rb");
	FILE* out_file = fopen("C-small-practice-2.out","wb");
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 1;
	char name[1024];
	while(i <= T)
	{
		int N;
		fscanf(in_file,"%d ",&N);
		vector<string> names;
		for(int j = 0;j < N;j++)
		{
			fgets(name,1024,in_file);
			names.push_back(name);
		}
		int ret = sort_count(names);
		fprintf(out_file,"Case #%d: %d\n",i,ret);
		i++;
	}
	fclose(in_file);
	fclose(out_file);

}
