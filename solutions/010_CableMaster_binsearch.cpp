// Problem: http://acm.tju.edu.cn/toj/showp2316.html
// Submit: As before
// Problem Number: 2316

//#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
using namespace std;

int n,k;
int cables[10000];

// F(val) will return true if val is not valid height (generates less than k pieces)
// Its behaviour=false false ... false true true .... true
// Note that we need the last false, not the first true
bool F(int val)
{
	if(val==0) return false;
	int i, num=0;
	for(i=0;i<n;i++) num+=cables[i]/val;
	if(num<k) return true;
	return false;
}

void Compute()
{
	// This binary search version works good on functions F():
	// false false ... false true true .... true
	int lo=0, hi=10000000+2;	// At start: lo=0; hi=max possible length+2
	while(lo<hi){
		int mid=lo+(hi-lo)/2;
		if(F(mid)) hi=mid;
		else lo=mid+1;
	}
	// lo is the least x for which p(x) is true (lo=first true)
	// So, lo=the first invalid height. We need the last valid height (last false)
	lo--;

	// Un-scale, then output "double" value!
	cout << lo/100 << "."; if(lo%100<10) cout<<"0"; cout << lo%100; 
	cout<<"\n";
}

int main()
{
	//freopen("Cable.in", "r", stdin);

	scanf("%d %d ", &n, &k);

	// We will get rid of doubles, and deal with integers, by scaling!
	// Integers are very safe
	// Doubles are dangerous. Precision is annoyning issue

	int i;
	for(i=0;i<n;i++)
	{
		double cab;
		scanf("%lf ", &cab);

		// 0.1 to be sure out double number is not something like 199.99999
		cables[i]=cab*100+0.1;
	}

	Compute();

	return 0;
}

//////////////////////////////////////////////////////////////////////
