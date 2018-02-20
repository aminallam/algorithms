#pragma warning(disable:4786)
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
int cases_cnt;

/*
Problem Statement 
     
A very rich sultan built an enormous luxurious two-story palace containing several 
staircases. According to an old tradition, each staircase must: 
contain exactly N steps 
have a right angle in its base 
be built using exactly N rectangular blocks of arbitrary size 
Staircases can be built using many different arrangements of blocks. For example, there 
are 5 ways to build a staircase with 3 steps: 


To ensure that his palace is really the most luxurious in the world, the sultan decided to 
build one staircase for each possible arrangement of blocks. 

The sultan is now preparing for a staircase coloring festival. He wants to paint each of 
the staircases in the palace in one of K different colors. Multiple staircases can be 
painted the same color, and it is not necessary to use all K colors. Help the sultan by 
calculating the total number of different ways he can color his staircases. The answer can 
be large, so return the count modulo 1000000123. 
----------------------------------------------------------
Constraints 
- 
N will be between 1 and 1000000000, inclusive. 
- 
K will be between 1 and 1000000000, inclusive. 
*/

typedef long long LL;
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

// d=ax+by=gcd(a,b), x,y are integers(+ve,-ve,0), x*a mod b=1 (x is mul inv a mod b)
void ExtendedEuclid(int a, int b, int& d, int& x, int& y){
	if(b==0) {d=a;x=1;y=0;return;}
	int x1,y1;
	ExtendedEuclid(b, a%b, d, x1, y1);
	x=y1; y=x1-y1*(a/b);
}

// return mul inverse of a mod b
int ModularInverse(int a, int b){
	int d,x,y; ExtendedEuclid(a, b, d, x, y); return (x+b)%b;
}

int PowerMod(int a, int n, int b){
	if(n==0) return 1;
	if(n==1) return a%b;
	int x=PowerMod(a,n/2,b);
	if(n%2==0) return (int)(((LL)x*x)%b);
	return (int)(((((LL)x*x)%b)*(a%b))%b);
}

// return n! (excluding all p's) mod p
int FactMod(int n, int p){
	int i, res=1;
	while(n>=p){
		int cur=1; for(i=2;i<p;i++) cur=(int)(((LL)cur*i)%p); // one cycle (excluding the coeff of p)
		res=(int)(((LL)res*PowerMod(cur,n/p,p))%p); // all cycles
		for(i=2;i<=n%p;i++)res=(int)(((LL)res*i)%p); // the last incomplete cycle
		n/=p; // Now the remaining terms are only the coeffs of removed p's, their size is n/p, compute it as before
	}
	for(i=2;i<=n%p;i++)res=(int)(((LL)res*i)%p); // the last incomplete cycle
	return res;
}

int MaxPowFactorial(int n, int p){ // return max power of p such that n! is divisable by p^ret
	int i=p, q=0;
	while(true){q+=n/i; if(i>n/p) break; i*=p;}
	return q;
}

// Restore the number a3, n3 from its rep (a1,n1) and (a2,n2) where n1 and n2 are relatively primes
//  Start from a1=0, n1=1 and repeat this procedure for each component (ai,ni)
bool ChineseRestore(int a1, int n1, int a2, int n2, int& a3, int& n3){
	int d,x,y; ExtendedEuclid(n1, n2, d, x, y); if(d!=1) return false;
	n3=n1*n2; x=(x+n2)%n2; y=(y+n1)%n1; a3=(int)(((LL)a1*n2%n3*y+(LL)a2*n1%n3*x)%n3);
	return true;
}

#define MOD 1000000123

class StairsColoring
{
public:
	int coloringCount(int N, int K)
	{
		// #...*
		// ...*
		// ..*
		// .*
		// *

		// A rectangle of them must have the #. It will also have exactly one * (can be any one).
		// If we took the rectangle in line i, the number of possible arrangements will be f(i)*f(n-1-i)
		// So: f(n)=Sum f(i)*f(n-1-i) where i=0 to n-1 (Catalan numbers)
		// The closed formula for Cataln Numbers is 2nCn/(n+1) Let this value equal x

		// We need to compute k^x mod p=1000000123 (prime number) we know from fermat that k^(p-1) mod p=1
		// So, we need just to compute k^(x mod (p-1)) mod p
		// Now the only difficult part is: x mod (p-1). p-1=1000000122=2*3*11*2089*7253
		// Since there is easier way to compute factorials mod prime, we will calculate x%fi for fi=these factors
		//  then we will combine the results to get the x mod (p-1) using Chinese Remainder Theorem

		int i, factors[]={2,3,11,2089,7253}; int nf=sizeof(factors)/sizeof(int);

		int a=0, n=1;
		for(i=0;i<nf;i++)
		{
			int p=factors[i];
			int ca=0;

			if(MaxPowFactorial(2*N,p)==MaxPowFactorial(N,p)+MaxPowFactorial(N+1,p))
			{
				int v=FactMod(2*N,p), q=ModularInverse(FactMod(N,p),p),z=ModularInverse(FactMod(N+1,p),p);
				ca=(int)((LL)v*q%p*z%p);
			}

			ChineseRestore(a, n, ca, p, a, n);
		}

		a=PowerMod(K,a,MOD);
		//cout<<a<<endl;
		return a;
	}
};

/*
Examples 
----------------------------------------------------------
0) 
     
3 
2 
Returns: 32 
As shown in the picture above, there are exactly 5 different ways to build a staircase 
with 3 steps. Each staircase can be painted in one of 2 different colors, for a total of 
32 possible color combinations. 
----------------------------------------------------------
1) 
     
2 
2 
Returns: 4 
----------------------------------------------------------
2) 
     
1 
1 
Returns: 1 
Here, there is only one staircase and one color to paint it. 
----------------------------------------------------------
3) 
     
4 
5 
Returns: 103514887 
----------------------------------------------------------
4) 
     
7 
77 
Returns: 747707397 
*/

void AdditionalTests()
{
}

int TestIsEqual(double a, double b){
	if(a>-1e300 && b>-1e300 && a<1e300 && b<1e300 && fabs(a-b)<1e-5) return 1; return 0;
}

int main()
{
	int i=0;
	bool flag;
	cout.setf(ios::fixed|ios::showpoint);
	cout.precision(5);
	cases_cnt=-1;
	bool all_flag=true;

	{
	//Test case # 0:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(3, 2);
	delete var0;

	flag=true;
	if(var1!=32)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(2, 2);
	delete var0;

	flag=true;
	if(var1!=4)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(1, 1);
	delete var0;

	flag=true;
	if(var1!=1)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(4, 5);
	delete var0;

	flag=true;
	if(var1!=103514887)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(7, 77);
	delete var0;

	flag=true;
	if(var1!=747707397)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	StairsColoring* var0=new StairsColoring;
	int var1 = var0->coloringCount(1000000000, 123);
	delete var0;

	flag=true;
	if(var1!=1)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	if(all_flag==false) cout << "Some Cases FAILED." << endl;
	else cout << "All cases passed." << endl;

	AdditionalTests();

	return 0;
}

//////////////////////////////////////////////////////////////////////

