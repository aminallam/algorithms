/////////////////////////////////////////////////////////////////////////////////
// Rhyme ////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
using namespace std;

typedef long double type;

int n;

type R[1000][1000];

type GetR(int n, int l)
{
	if (R[n][l]>-1) return R[n][l];
	if (n==1 && l==1) return 1;
	if (l>n || n<1 || l<1) return 0;
	
	type r = l*GetR(n-1,l)+GetR(n-1,l-1);
	R[n][l]=r;
	return r;	
}

void Compute()
{
	int i,j;
	
	for (i=0; i<=n; i++)
		for (j=0; j<=n; j++)
			R[i][j]=-2;
	
	type sum=0;
	
	for (i=1; i<=n; i++)
		sum+=GetR(n,i);
	
	cout << n << " " << setiosflags(ios::fixed) << 
			setprecision(0) << (sum+1e-11) << endl;
}

int main()
{
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
	
	while(true)
	{
		cin >> n;
		if (n==0) break;
		
		Compute();
	}
	
	return 0;
}
