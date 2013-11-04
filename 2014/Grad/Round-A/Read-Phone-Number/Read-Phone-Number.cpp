// Read-Phone-Number.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#define MAX_LEN 1024

string call[] = {"double","triple","quadruple","quintuple","sextuple","septuple","octuple",
				"nonuple","decuple"};

string name[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};

string readNumber(vector<int>& number,int start,int end)
{
	string dest = "";
	int dup_num = 1;
	int old = number[start];
	for (int i = start + 1;i < end;i++)
	{
		if (number[i] == old)
		{
			dup_num++;
		}
		else
		{
			if (dup_num > 1 && dup_num <= 10)
			{
				dest += call[dup_num-2];
				dest += " ";
				dest += name[old];
				dest += " ";
			}
			else
			{
				if (dup_num > 10)
				{
					for (int j = 0;j < dup_num;j++)
					{
						dest += name[old];
						dest += " ";
					}
				}
				else
				{
					dest += name[old];
					dest += " ";
				}
			}

			if (i == end - 1)
			{
				dest += name[number[i]];
				if(end < number.size())
					dest += " ";
			}
			
			old = number[i];
			dup_num = 1;
		}
	}

	if (dup_num > 1 && dup_num <= 10)
	{
		dest += call[dup_num-2];
		dest += " ";
		dest += name[old];
		if(end < number.size())
			dest += " ";
	}
	else
	{
		if (dup_num > 10)
		{
			for (int j = 0;j < dup_num;j++)
			{
				dest += name[old];
				if (j == dup_num-1)
				{
					if (end < number.size())
						dest += " ";
				}
				else
					dest += " ";
			}
		}
	}
		
	if (dest == "")
	{
		dest += name[old];
		if(end < number.size())
			dest += " ";
	}

	return dest;
}


int main(int argc, char* argv[])
{
	FILE* in_file = fopen("A-large-practice.in","rb");
	FILE* out_file = fopen("A-large-practice.out","wb");

	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 1;
	char number[MAX_LEN];
	char format[MAX_LEN];
	while (i <= T)
	{
		vector<int> e_number;
		vector<int> i_number;
		fscanf(in_file,"%s ",number);
		fscanf(in_file,"%s ",format);
		char* old = format;
		char* p = strstr(old,"-");
		while(p != NULL)
		{
			*p = '\0';
			e_number.push_back(atoi(old));
			old = p + 1;
			p = strstr(old,"-");
		}
		if (*old != '\0')
		{
			e_number.push_back(atoi(old));
		}

		old = number;
		while (*old != '\0')
		{
			i_number.push_back(*old - '0');
			old++;
		}

		int index = 0;
		string dest = "";
		for (int j = 0;j < e_number.size();j++)
		{	
			dest += readNumber(i_number,index,index + e_number[j]);
			index += e_number[j];
		}	
		fprintf(out_file,"Case #%d: %s\n",i,dest.c_str());
		i++;
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}

