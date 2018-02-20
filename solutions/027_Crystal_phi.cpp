// Problem: http://icpcres.ecs.baylor.edu/onlinejudge/index.php?option=com_onlinejudge&page=show_problem&problem=1955
// Submit: Same As Previous
// Problem Number: 11014

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long LL;

/////////////////////////////////////////////////////////////////////

void Sieve(int n,int min_prime[]){ // min_prime[i]=minimum prime factor of i
	int i, k; for(i=0;i<=n;i++) min_prime[i]=i;
	int m=(int)sqrt(n);
	for(i=2;i<=m;i++,i|=1) if(min_prime[i]==i)
		for(k=i*i;k<=n;k+=i) {if(i<min_prime[k]) min_prime[k]=i;}
}

/////////////////////////////////////////////////////////////////////

#define MAX_N 200000

int min_prime[MAX_N+1];

LL phi[MAX_N+1];
LL phi2[MAX_N+1];

LL sum_phi[MAX_N+1];
LL sum_phi2[MAX_N+1];

int n;

void Initialize()
{
	Sieve(MAX_N, min_prime);

	int i;

	phi[0]=0; phi[1]=1;
	
	for(i=2;i<=MAX_N;i++)
	{
		int p=min_prime[i];
		int new_num=i/p;

		//phi[i]=phi[new_num]*i/new_num;
		//if(p!=min_prime[new_num]) phi[i]=phi[i]/p*(p-1);

		if(p==min_prime[new_num]) phi[i]=phi[new_num]*p;
		else phi[i]=phi[new_num]*(p-1);
	}

	// phi2[p]=p^2-1
	// phi2[p^k]=p^2k-p^2(k-1)
	// phi2[m]=m^2 PI(1-1/p^2)

	phi2[0]=0; phi2[1]=1;

	for(i=2;i<=MAX_N;i++)
	{
		int p=min_prime[i];
		int new_num=i/p;

		if(p==min_prime[new_num]) phi2[i]=phi2[new_num]*p*p;
		else phi2[i]=phi2[new_num]*((LL)p*p-1);
	}

	sum_phi[0]=0; sum_phi[1]=1;
	for(i=2;i<=MAX_N;i++) sum_phi[i]=sum_phi[i-1]+2*phi[i];

	sum_phi2[0]=0; sum_phi2[1]=1;
	for(i=2;i<=MAX_N;i++) sum_phi2[i]=sum_phi2[i-1]+3*phi2[i]-3*phi[i];

	// -3*phi[i]; because each relatively prime number to i causes 3 additional terms
	//  (make a test case and try it)
}

LL Compute()
{
	return sum_phi2[n]*8 + sum_phi[n]*12 + 6;
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
Crystal 1: 26
Crystal 2: 26
Crystal 3: 98
Crystal 4: 98
Crystal 5: 290
Crystal 6: 290
Crystal 7: 578
Crystal 8: 578
Crystal 9: 1154
Crystal 10: 1154
Crystal 11: 1730
Crystal 12: 1730
Crystal 13: 2882
Crystal 14: 2882
Crystal 15: 1144243350562754
Crystal 16: 6655340768473154
*/
