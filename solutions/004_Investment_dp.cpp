// Problem: http://acm.pku.edu.cn/JudgeOnline/problem?id=2063
// Submit:  As before
// Problem Number:  2063

#include <cstring>	// for memset
#include <cstdio>	// for freopn and scanf
#include <iostream>	// for cout
using namespace std;

#define max(x,y) (((x)>(y))?(x):(y))

int money, nyears, nbonds;
int P[10][60000];	// [bond][money/1000]

int val[10];	// value of bond (size)
int inter[10];	// interest of bond (profit)

/*
int GetP(int ibond, int cmoney) // Current bond, available money
{
	if(ibond==nbonds) return 0;

	int& prof=P[ibond][cmoney];
	if(prof!=-1) return prof;

	if(val[ibond]>cmoney) prof=GetP(ibond+1, cmoney);
	else prof=max(GetP(ibond+1, cmoney), inter[ibond]+GetP(ibond, cmoney-val[ibond]));

	return prof;
}
*/

void Compute()
{
	int i;

	// This is bottom up dynamic programming
	// It is the same logic of memoization using GetP()
	//  except that we count values in the order such that I will not make
	//  queries for un-computed cells. (Try to understand why this will fail
	//  if we make, for example:
	//             for(int cmoney=money/1000;cmoney>=next_start_money;cmoney--)

	// Now, we made bottom up but we did not observe its power
	// The power is that you can use some P smaller than P[10][60000];
	// You need only the ibond+1 while processing. You do not need
	//        ibond+2, ibond+3. So, you need to save only information related
	//			to the ibond+1. Does this make sence? Please Implement it P[2][60000].
	// Another space improvement: Make it P[60000] and it will work. Can you know
	//			wht it worked? Simple, but needs thinking.. Implement it.

	// Try to understand what this variable do?
	int next_start_money=0;

	for(i=0;i<nyears;i++)
	{
		for(int ibond=nbonds-1;ibond>=0;ibond--)
		{
			for(int cmoney=next_start_money;cmoney<=money/1000;cmoney++)
			{
				if(val[ibond]>cmoney)
				{
					if(ibond+1>=nbonds) P[ibond][cmoney]=0;
					else P[ibond][cmoney]=P[ibond+1][cmoney];
				}
				else
				{
					P[ibond][cmoney]=max(
						(ibond+1>=nbonds)?0:P[ibond+1][cmoney],
						inter[ibond]+P[ibond][cmoney-val[ibond]]
						);
				}
			}
		}

		next_start_money=money/1000+1;
		money+=P[0][money/1000];

		//money+=GetP(0,money/1000); // Old way (memoization)
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
