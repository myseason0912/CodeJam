// C.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <vector>
using namespace std;

#define MAX_LEN 200

vector< vector<char> > fair;

/*�������еĳ˷���û�н�λ����ֻ��Ҫ��Ӿͺã������ǽ�λ*/
vector<char> square(vector<char>& a)
{
	vector<char> result;
	result.resize(a.size()*2,0);
	for(int i = 0;i < a.size();i++)
		for(int j = 0;j < a.size();j++)
			result[i+j] += a[i]*a[j];

	/*ȥ�������0�����ڻ����������һλ��Ϊ0���ʳ˻����һλҲ����Ϊ0*/
	while(result.size() > 1 && result.back() == 0)
		result.pop_back();

	return result;
}

void fill(int p, int l, vector<char> & result, int rest) {
    if (p*2 + 1 == l) {
        int i=0;
        while(i*i <= rest) {
            result[p] = i;
            fill(p+1, l, result, rest - i*i);
            ++i;
        }
    } else if (p*2 + 1 > l) {
        fair.push_back(vector<char>());
        for (int i=0; i<result.size(); ++i) {
            fair.back().push_back(result[i]);
        }
        if ((l & 1) == 0) {
            fair.back().push_back(result.back());
        }
        for (int i=result.size()-2; i>=0; --i) {
            fair.back().push_back(result[i]);
        }
    } else {
        int i=0;
        if (p==0) ++i;
        while (i*i*2 <= rest) {
            result[p] = i;
            fill(p+1, l, result, rest - i*i*2);
            ++i;
        }
    }
}

/*��������1-10^50������ػ���ƽ��Ҳ�ػ�����
�ڳ˻��Ĺ����в����н�λ����ÿһλ��0-3֮�䣬����λ�һػ�
*/
void preprocess()
{
	vector<char> digit(1);
    digit[0] = 0;
    fair.push_back(digit);
    digit[0] = 1;
    fair.push_back(digit);
    digit[0] = 2;
    fair.push_back(digit);
    digit[0] = 3;
    fair.push_back(digit);

	/*ֻ��Ҫȷ��ǰ25λ���ɣ���2λ��ʼ*/
    for (int i=2; i<52; ++i) {
        vector<char> result((i+1)/2);
        fill(0, i, result, 9);
    }

    for (int i=0; i<fair.size(); ++i) {
        fair[i] = square(fair[i]);
    }
}

bool compare(vector<char>& a,vector<char>& b)
{
	if(a.size() != b.size())
		return a.size() < b.size();

	for (int i = 0;i < a.size();i++)
		if(a[i] != b[i])
			return a[i] < b[i];
	return true;
}

int find(vector<char> & a)
{
	int A = 0;
	int B = fair.size();
	int C = 0;
	/*�۰��������ҵ���һ��С��a��fair��,fairΪ��С��������*/
	while(A < B - 1)
	{
		C = (A+B) / 2;
		if(compare(fair[C],a))
			A = C;
		else
			B = C;
	}
	return A;
}


int main(int argc, char* argv[])
{
	freopen("test.txt", "rb", stdin);
	freopen("test.out", "wb", stdout);

	int T = 0;
	scanf("%d ",&T);
	int count = 1;
	char A[MAX_LEN];
	char B[MAX_LEN];
	preprocess();
	while(count <= T)
	{
		scanf("%s %s",A,B);
		vector<char> AA;
		vector<char> BB;
		for(int i = 0;A[i] != '\0';i++)
			AA.push_back(A[i] - '0');

		int i = AA.size() - 1;
		while(i > 0 && AA[i] == 0)
		{
			AA[i] = 9;
			i--;
		}
		AA[i]--;

		for(int i = 0;B[i] != '\0';i++)
			BB.push_back(B[i] - '0');

		int below_A = find(AA);
		int below_B = find(BB);
		printf("Case #%d: %d\n",count,below_B-below_A);
		count++;
	}
	return 0;
}

