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

// How this differs from ordinary knapsack?
int GetP(int ibond, int cmoney) // Current bond, available money
{
	if(ibond==nbonds) return 0;

	int& prof=P[ibond][cmoney];
	if(prof!=-1) return prof;

	if(val[ibond]>cmoney) prof=GetP(ibond+1, cmoney);
	else prof=max(GetP(ibond+1, cmoney), inter[ibond]+GetP(ibond, cmoney-val[ibond]));

	return prof;
}

void Compute()
{
	int i;

	// What will happen if we put this line inside the next loop?
	// Prove that it is correct to put it here
	memset(P,-1,sizeof(P));

	for(i=0;i<nyears;i++)
	{
		money+=GetP(0,money/1000); // We have divided val[] on 1000, so we will
									// work on money on 1000
									// This is called "Scaling". What is the benefit of it?
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
