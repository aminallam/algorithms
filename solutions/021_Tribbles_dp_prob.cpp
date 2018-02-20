// Problem: http://online-judge.uva.es/p/v110/11021.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11021

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double type; // I made this because I was trying also (long double)

int n;
type p[1000];
type Prob[1000+1];

type GetProb(int m)
{
	if(m==0) return 0;
	if(Prob[m]!=-1) return Prob[m];
	
	int i;
	type val=0;
	
	type pm=GetProb(m-1);
	type acc=1;

	for(i=0;i<n;i++)
	{
		// p[i]=prob of generating i tribes in next generation
		// acc=pow(GetProb(m-1),i)=prob all generated tribbles die at most after m-1 geners

		val+=p[i]*acc;	// Avoid this: val+=p[i]*pow(pm,i); as pow() is slow
		acc*=pm;
	}
	
	Prob[m]=val;
	return val;
}

//////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("ProbWorm.in", "r", stdin);

	int i, j, m, k, cases;
	scanf("%d ", &cases);

	for(i=0;i<cases;i++)
	{
		scanf("%d %d %d ", &n, &k, &m);

		for(j=0;j<n;j++)
			scanf("%lf ", &p[j]);

		for(j=0;j<=m;j++) Prob[j]=-1;
		
		//Prob[0]=0;		// Faster than: if(m==0) return 0; at begin of GetProb()
							// But, it is not very readable.

		cout.setf(ios::showpoint|ios::fixed);
		cout.precision(7);

		cout << "Case #" << i+1 << ": " << pow(GetProb(m),k) << "\n";
	}

	return 0;
}
