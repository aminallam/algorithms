// Problem: http://acm.uva.es/p/v1/193.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  193

//#pragma warning(disable:4786) // To ignore most Visual C++ 6 warnings concerning STL
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAXN 100

int G[MAXN][MAXN]; // G[i][j]=1 if connected
int n;

enum {BLACK, WHITE};

int col[MAXN];

int best_col[MAXN];	// best solution until now (Color of every node in the best coloring)
int best_numb;		// best number of blacks in complete until now

void BackTrack(int numb, int st)
{
	int i;

	// If even it happened that all uncolored nodes are black, this will not 
	//	be better than the current best solution (Simple branch and bound)

	if(numb+n-st<=best_numb)
		return;

	if(st==n)
	{
		// We are sure we have better coloring (because of previous check)

		best_numb=numb;
		for(i=0;i<n;i++) best_col[i]=col[i];
		return;
	}

	// Try White

	col[st]=WHITE;
	BackTrack(numb, st+1);

	// See If it can be black

	bool good=true;
	for(i=0;i<n;i++)
		if(G[st][i] && col[i]==BLACK)
			{good=false; break;}

	if(good) // It can be black
	{
		col[st]=BLACK;
		BackTrack(numb+1, st+1);
	}

	// Reset to original value

	col[st]=WHITE;
}

int main()
{
	//freopen("GraphColoring.in", "r", stdin);

	int i, j, m;
	scanf("%d ", &m);

	for(i=0;i<m;i++)
	{
		int k;
		scanf("%d %d ", &n, &k);

		int v;
		for(j=0;j<n;j++) for(v=0;v<n;v++) G[j][v]=0;

		for(j=0;j<k;j++)
		{
			int a, b;
			scanf("%d %d ", &a, &b);
			a--; b--;

			G[a][b]=1;
			G[b][a]=1;
		}

		for(j=0;j<n;j++)
			col[j]=WHITE;
		
		best_numb=0;
		BackTrack(0, 0);

		cout<<best_numb<<"\n";
		
		bool first=true;
		for(j=0;j<n;j++) if(best_col[j]==BLACK)
		{
			if(!first) cout<<" "; first=false;
			cout<<(j+1);
		}
		cout << "\n";
	}

	return 0;
}
