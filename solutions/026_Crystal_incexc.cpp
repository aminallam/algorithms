// Problem: http://online-judge.uva.es/p/v110/11014.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11014

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
using namespace std;

//typedef __int64 LL;
//ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}

typedef long long LL;

/////////////////////////////////////////////////////////////////////

/*
// Slower but correct
int Factorize(int m){//m=p1^q1*p2^q2..,np=size of p,q (1-indexed)
	int np=0; int a=m; int i=2;
	while(i*i<=a) {
		if (a%i==0) {
			np++; a/=i;
			if(a%i==0) return 0; // Same prime occurred twice
		}
		i++;
	}
	if(a>1) np++;
	return np; // Number of different primes
}
*/

int Factorize(int m){//m=p1^q1*p2^q2..,np=size of p,q (1-indexed)
	int np=0; int a=m; int i=2;
	if (a%i==0) { // Special case for 2, to be fast
		np++; a/=i;
		if(a%i==0) return 0; // Same prime occurred twice
	}
	i++;
	while(i*i<=a) {
		if (a%i==0) {
			np++; a/=i;
			if(a%i==0) return 0; // Same prime occurred twice
		}
		i+=2; // Faster, as we made special case for 2, we will skip even numbers
	}
	if(a>1) np++;
	return np; // Number of different primes
}

/////////////////////////////////////////////////////////////////////

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
		int np = Factorize(i);
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
	int icase=0;

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
