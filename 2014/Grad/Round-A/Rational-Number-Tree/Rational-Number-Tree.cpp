// Rational-Number-Tree.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <vector>
using namespace std;

int problem1(unsigned long long n,unsigned long long& p,unsigned long long& q)
{
	vector<bool> left;
	while (n != 1)
	{
		if ((n & 0x1) == 1)
		{
			/*ÆæÊý*/
			left.push_back(false);
		}
		else
		{
			/*Å¼Êý*/
			left.push_back(true);
		}
		n = n/2;
	}
	p = 1;
	q = 1;
	for (int i = left.size() - 1;i >= 0;i--)
	{
		if (left[i])	
		{
			/*×óº¢×Ó*/
			p = p;
			q = p+q;
		}
		else
		{
			/*ÓÒº¢×Ó*/
			p = p + q;
			q = q;
		}
	}
	return 0;
}

int problem2(unsigned long long& n,unsigned long long p,unsigned long long q)
{
	vector<bool>  left;
	while(!(p == 1 && q == 1))
	{
		if (p > q)
		{
			/*ÓÒº¢×Ó*/
			left.push_back(false);
			p = p - q;
			q = q;
		}
		else
		{
			/*×óº¢×Ó*/
			left.push_back(true);
			q = q - p;
			p = p;
		}
	}
	n = 1;
	for (int i = left.size() - 1;i >= 0;i--)
	{
		if (left[i])
			n *= 2;
		else
			n = n*2 + 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	FILE* in_file = fopen("B-large-practice.in","rb");
	FILE* out_file = fopen("B-large-practice.out","wb");
	
	int T = 0;
	int i = 1;
	fscanf(in_file,"%d ",&T);
	while(i <= T)
	{
		int pro = 0;
		unsigned long long p = 0;
		unsigned long long q = 0;
		unsigned long long n = 0;
		fscanf(in_file,"%d ",&pro);
		if(pro == 1)
		{			
			fscanf(in_file,"%llu ",&n);
			problem1(n,p,q);
			printf("Case #%d: %llu %llu\n",i,p,q);
			fprintf(out_file,"Case #%d: %llu %llu\n",i,p,q);
		}
		if(pro == 2)
		{
			fscanf(in_file,"%llu ",&p);
			fscanf(in_file,"%llu ",&q);
			problem2(n,p,q);
			printf("Case #%d: %llu\n",i,n);
			fprintf(out_file,"Case #%d: %llu\n",i,n);
		}
		i++;
	}

	fclose(in_file);
	fclose(out_file);

	return 0;
}

