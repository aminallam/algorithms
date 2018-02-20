// Problem: http://acm.pku.edu.cn/JudgeOnline/problem?id=2063
// Submit:  As before
// Problem Number:  2063

#include <cstring>	// for memset
#include <cstdio>	// for freopn and scanf
#include <iostream>	// for cout
using namespace std;

#define max(x,y) (((x)>(y))?(x):(y))

int money, nyears, nbonds;
int P[60000];	// [money/1000]

int val[10];	// value of bond (size)
int inter[10];	// interest of bond (profit)

void Compute()
{
	int i;

	memset(P,0,sizeof(P));
	
	int next_start_money=0;

	for(i=0;i<nyears;i++)
	{
		for(int ibond=nbonds-1;ibond>=0;ibond--)
		{
			for(int cmoney=next_start_money;cmoney<=money/1000;cmoney++)
			{
				if(val[ibond]<=cmoney)
				{
					P[cmoney]=max(P[cmoney],inter[ibond]+P[cmoney-val[ibond]]);
				}
			}
		}

		next_start_money=money/1000+1;
		money+=P[money/1000];
	}

	cout << money << "\n";
}

int main()
{
	// Comment before submit
	//freopen("Investment.in", "r", stdin);

	int cases;

	scanf("%d ", &cases);

	int k, i;

	for(k=0;k<cases;k++)
	{
		scanf("%d %d %d ", &money, &nyears, &nbonds);

		for(i=0;i<nbonds;i++)
		{
			scanf("%d %d ", &val[i], &inter[i]);
			val[i]/=1000; // Since val[i] must be multiple of 1000
							// What is the benefit of this statement?
		}
		
		Compute();
	}

	return 0;
}
