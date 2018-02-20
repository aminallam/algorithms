// Problem: http://icpcres.ecs.baylor.edu/onlinejudge/index.php?option=com_onlinejudge&page=show_problem&problem=1955
// Submit: Same As Previous
// Problem Number: 11014

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long LL;

/////////////////////////////////////////////////////////////////////

void Sieve(int n,bool prime[],int min_prime[]){ // min_prime[i]=minimum prime factor of i
	int i, k; for(i=0;i<=n;i++) {prime[i]=true;min_prime[i]=i;}
	prime[0]=prime[1]=false; int m=(int)sqrt(n);
	for(i=2;i<=m;i++,i|=1) if(prime[i])
		for(k=i*i;k<=n;k+=i) {prime[k]=false; if(i<min_prime[k]) min_prime[k]=i;}
}
void TraverseFactors(int n,int min_prime[]){ // prime factors (ordered)
	while(n>1){
		int cur_factor=min_prime[n];
		n/=cur_factor;
	}
}

int GetFactors(int n, int min_prime[]){ // prime factors ordered from smallest to largest
	int last_factor=0, np=0;
	while(n>1){
		int cur_factor=min_prime[n];
		if(cur_factor==last_factor)return 0;
		n/=cur_factor;np++;
		last_factor=cur_factor;
	}
	return np;
}

/////////////////////////////////////////////////////////////////////

#define MAX_N 200000

bool prime[MAX_N+1];
int min_prime[MAX_N+1];
int num_different_factors[MAX_N+1];

int n;

// f(k)=# of points(x,y,z) where x,y,z are >0 and <=n and are multiples of k
LL f3d(int k) {return (LL)(n/k)*(n/k)*(n/k);}	
LL f2d(int k) {return (LL)(n/k)*(n/k);}	

LL Compute()
{
	int i;
	
	// Apply principle of inclusion-exclusion

	// First, include all possible points with +ve coords
	LL val3d = f3d(1), val2d = f2d(1);

	// Then, exclude all points that are multiples of ONE prime: f(2)+f(3)+f(5)+...
	
	// Then, include all points that are multiples of TWO primes, as they
	//		were excluded twice in previous step: f(2*3)+f(2*5)+f(3*5)+...

	// Then, exclude all points that are multiples of THREE primes, as they
	//		were included twice in previous step: f(2*3*5)+f(2*5*7)+f(3*5*7)+...

	// etc ...

	for(i=2;i<=n;i++)
	{
		int np = num_different_factors[i];
		if(np==0) continue;
		
		if(np%2==0) // Even Number of different primes
		{
			val3d += f3d(i);
			val2d += f2d(i);
		}
		else // Odd Number of different primes
		{
			val3d -= f3d(i);
			val2d -= f2d(i);
		}
	}

	// (0) in following equations indicates that this coordinate is 0
	//		It is 1 possibility

	// 2 in following equations indicates that this coordinate may be positive or negative
	//		It is Two possibilities

	// val3d contains number in the +ve x,y,z of 3d space
	//		(8 of them because: 2*2*2)
	
	// val2d contains number in the +ve x,y of 2d space 
	//		(12 of them because: (0)*2*2 + 2*(0)*2 + 2*2*(0))

	// we have only 1 in +ve x of 1d space
	//		(6 of them because: 2*(0)*(0) + (0)*2*(0)+ (0)*(0)*(2))

	return val3d*8 + val2d*12 + 6;
}

/////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("Crystal.in", "r", stdin);
	int i, icase=0;

	Sieve(MAX_N, prime, min_prime);
	for(i=0;i<=MAX_N;i++) num_different_factors[i]=GetFactors(i,min_prime);

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
