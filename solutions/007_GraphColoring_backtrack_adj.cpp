// Problem: http://acm.uva.es/p/v1/193.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  193

//#pragma warning(disable:4786) // To ignore most Visual C++ 6 warnings concerning STL
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// This is faster version

#define MAXN 100

int G[MAXN][MAXN];	// G[i][j]=is jth neighbor of i
int sz[MAXN];		// sz[i] is number of neighbors of i
int n;

// We introduced a color UNKNOWN that means a node is not yet colored
//  Read the program then answer: Do we really need it? can we avoid it?

enum {BLACK, WHITE, UNKNOWN};

int col[MAXN];

int best_col[MAXN];
int best_numb;

// numb=num blacks in until now, nrem=remaining un-colored nodes, st=current node

void BackTrack(int numb, int nrem, int st)
{
	int i;

	// Better Branch and bound using nrem

	if(numb+nrem<=best_numb)
		return;

	if(st==n)
	{
		best_numb=numb;
		for(i=0;i<n;i++) best_col[i]=col[i];
		return;
	}

	if(col[st]==UNKNOWN)
	{
		int f[MAXN];
		int s=0;

		// Try coloring current node black
		// So, we will color every adjacent node by white

		for(i=0;i<sz[st];i++)
		{
			if(col[G[st][i]]==UNKNOWN)
			{
				f[s++]=G[st][i];
				col[G[st][i]]=WHITE;
			}
		}

		// Color it Black

		col[st]=BLACK;
		BackTrack(numb+1, nrem-1-s, st+1);
		col[st]=UNKNOWN;

		// Undo coloring adjacent nodes by white

		for(i=0;i<s;i++)
			col[f[i]]=UNKNOWN;

		// Try coloring our node white

		col[st]=WHITE;
		BackTrack(numb, nrem-1, st+1);
		col[st]=UNKNOWN;
	}
	else
	{
		BackTrack(numb, nrem, st+1);
	}
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

		for(j=0;j<n;j++)
			sz[j]=0;

		for(j=0;j<k;j++)
		{
			int a, b;
			scanf("%d %d ", &a, &b);
			a--; b--;

			G[a][sz[a]++]=b;
			G[b][sz[b]++]=a;
		}

		for(j=0;j<n;j++)
			col[j]=UNKNOWN;

		best_numb=-1;
		BackTrack(0, n, 0);

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
