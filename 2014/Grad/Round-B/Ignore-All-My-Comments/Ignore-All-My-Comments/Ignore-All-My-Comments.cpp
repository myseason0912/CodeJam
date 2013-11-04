// Ignore-All-My-Comments.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

long long ReadFileLongSize(const char* lpszFilename)
{
	long long lSize=0;

    if(!lpszFilename||(strlen(lpszFilename)==0)){
		fprintf(stderr,"File %s doesnot exist!\n",lpszFilename);
         return -1;
	}

	FILE* fp = fopen(lpszFilename,"rb");
	if(fp){
		_fseeki64(fp,0L,SEEK_END);
		lSize = _ftelli64(fp);    
		fclose(fp);
	}
	else
		lSize=-1;

	
    return lSize;
}

long long ReadFileLong(char *FileStr,long long lSize,const char* lpszFilename)
{

    if(!lpszFilename||(strlen(lpszFilename)==0)){
		fprintf(stderr,"File %s doesnot exist!\n",lpszFilename);
        return -1;
	}

	FILE* fp = fopen(lpszFilename,"rb");
	try{
		if(!fp){
			fprintf(stderr,"Openning file %s error!\n",lpszFilename);
			 return -1;
		}//if

        if(lSize>0){

        fread(FileStr,sizeof(char),lSize,fp);

		} //if

        fclose(fp);

	}
	catch(...){
		if(fp)
			fclose(fp);
	}//try

    return lSize;
}

int main(int argc, char* argv[])
{
	char file_path[] = "E-small-practice.in";
	long long file_size = ReadFileLongSize(file_path);
	char* buff = new char[file_size + 1];
	ReadFileLong(buff,file_size,file_path);
	buff[file_size] = '\0';

	FILE* output = fopen("output","wb");
	if (output == NULL)
	{
		printf("open input file error\n");
		return 0;
	}
	string ret = "";
	stack<int> pos;
	char* used = NULL;
	char* end = buff;
	char* old = buff;
	char* p = strstr(old,"/");
	while (p != NULL)
	{
		if (p != buff && !pos.empty() && *(p-1) == '*' && used != p - 1)
		{
			/*case'*\/'*/
			pos.pop();	
			end = p + 1;
		}
		else
		{
			if (*(p+1) == '*')
			{
				if (pos.empty())
				{
					*p = '\0';
					ret += end;
				}
				pos.push(p-buff);
				end = p + 1;
				used = p + 1;
			}
		}
		old = p + 1;
		p = strstr(old,"/");
	}
	if (*end != '\0')
		ret += end;
	fprintf(output,"Case #1:\n");
	fprintf(output,"%s",ret.c_str());
	fclose(output);
	delete[] buff;

	return 0;
}

