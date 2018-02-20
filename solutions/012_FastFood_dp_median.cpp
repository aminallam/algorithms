// Problem: http://acm.uva.es/p/v6/662.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 662

#pragma warning(disable:4786)
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int Abs(int a)
{
	if(a<0) return -a;
	return a;
}

int icase;

int n,k;
int d[200];

int W[200][200];	// W[i][j]=cost to serve from i-->j

int L[200][31];
int Dec[200][31];	// D[i][j]=Decision taken when computing L[i][j] (Second restaurant)

int GetL(int ind, int ck)	// we have ck depots, and we need to serve from ind-->n-1
{
	if(ind==n) return 0;
	if(ck==0) return -2;	// -2 means not possible (some places are not served)

	int& ret=L[ind][ck];
	if(ret!=-1) return ret;

	ret=-2;
	int i;

	for(i=ind;i<n;i++)	// The first restaurant is ind. Choose second restaurant i
	{					// All restaurants from ind-->i will be served by the same depot
		int cost=GetL(i+1, ck-1);	// Get cost of serving remaining restaurants

		if(cost!=-2)	// It is possible to serve them
		{
			cost+=W[ind][i];	// Put depot at median of (i->ind) and get cost of this
			
			if(ret==-2 || cost<ret)	// Better second restaurant
			{
				Dec[ind][ck]=i;	// Save this decision
				ret=cost;
			}
		}
	}

	return ret;
}

int Median(int i, int j)
{
	return i+(j-i+1)/2;
}

void Compute()
{
	int i,j,v;

	// Fill in the table W[i][j]
	// It is better to do this here, not in GetL() to save time

	for(i=0;i<n;i++) for(j=i;j<n;j++)
	{
		int median=Median(i,j);

		W[i][j]=0;
		for(v=i;v<=j;v++)
			W[i][j]+=Abs(d[v]-d[median]);
	}

	memset(L,-1,sizeof(L));

	int cost=GetL(0,k);

	cout << "Chain " << icase << "\n";

	int fir=0;
	int ck=k;
	int cur_dep=0;

	// Get our best solution using Dec[][]

	while(fir<n)
	{
		int sec=Dec[fir][ck];

		if(fir==sec){
			cout << "Depot " << cur_dep+1 << " at restaurant " << Median(fir,sec)+1 <<
					" serves restaurant " << fir+1 << "\n";
		}else{
			cout << "Depot " << cur_dep+1 << " at restaurant " << Median(fir,sec)+1 <<
					" serves restaurants " << fir+1 << " to " << sec+1 << "\n";
		}

		fir=sec+1;
		ck--;
		cur_dep++;
	}

	cout << "Total distance sum = " << cost << "\n";
	cout << "\n";
}

int main()
{
	int i;
	icase=0;

	//freopen("fastfood.in", "r", stdin);
	//freopen("a.in", "r", stdin);
	//freopen("b.txt", "w", stdout);

	while(true)
	{
		scanf("%d %d ", &n, &k);
		if(n==0) break;

		icase++;

		for(i=0;i<n;i++)
			scanf("%d ", &d[i]);
		
		Compute();
	}

	return 0;
}
