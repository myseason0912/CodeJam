#include <stdio.h>
#include <math.h>

int main(int argc,char* argv[])
{
	FILE* in_file = fopen("B-small-practice.in","rb");
	FILE* out_file = fopen("B-small-practice.out","wb");
	int T = 0;
	fscanf(in_file,"%d ",&T);
	int i = 1;
	double g = 9.8;
	double PI = 3.1415926;
	while(i <= T)
	{
		double v = 0.0;
		double d = 0.0;
		fscanf(in_file,"%lf %lf ",&v,&d);
		double theta = asin(g * d / (v * v)) / 2.0;
		theta = theta * 180 / PI;
		fprintf(out_file,"Case #%d: %.7lf\n",i,theta);
		i++;
	}
	fclose(in_file);
	fclose(out_file);
	return 0;
}