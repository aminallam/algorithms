// Problem: http://icpcres.ecs.baylor.edu/onlinejudge/index.php?option=com_onlinejudge&page=show_problem&problem=1955
// Submit: Same As Previous
// Problem Number: 11014

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long LL;

/////////////////////////////////////////////////////////////////////

#define MAX_N 200000

LL s[MAX_N+1];
LL p[MAX_N+1];
LL r[MAX_N+1];

int n;

void Initialize()
{
	int i,j;

	s[0]=1; p[0]=0;

	for(i=1;i<=MAX_N;i++)
	{
		LL a=2*i+1, b=2*(i-1)+1;
		s[i]=a*a*a-b*b*b;
		p[i]=s[i];
	}

	for(i=1;i<=MAX_N;i++)
	{
		for(j=2;j<=MAX_N/i;j++) p[i*j]-=p[i];
	}

	r[0]=p[0];

	for(i=1;i<=MAX_N;i++)
	{
		r[i]=r[i-1]+p[i];
	}
}

LL Compute()
{
	return r[n];
}

/////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("Crystal.in", "r", stdin);
	int icase=0;

	Initialize();

	while(true)
	{
		scanf("%d ", &n);
		if(n==0) break;
		n=n/2; // We need only +ve part
		icase++;
		cout << "Crystal " << icase << ": " << Compute() << "\n";
	}

	return 0;
}

/*
Crystal 1: 98
Crystal 2: 26
Crystal 3: 1144243350562754
*/
