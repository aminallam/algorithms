// Problem: http://online-judge.uva.es/p/v110/11008.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11008

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;

int icase;

#define min(x,y) (((x)<(y))?(x):(y))

typedef int Cord;
struct Point {
	Cord x, y;
	Point(){}
	Point(Cord _x, Cord _y):x(_x),y(_y){}
};
Cord operator^(const Point&A,const Point&B) {return A.x*B.y-A.y*B.x;} // Cross Prod
Point operator-(const Point &A,const Point&B) {return Point(A.x-B.x,A.y-B.y);}
Point Vect(Point a, Point b){return (b-a);} // Vector a-->b

////////////////////////////////////////////////////////////////////////////////

// settr = set of trees. We use bitset<> instead of integer to make use of the 
//	fast count() in it which finds number of bits set to 1 in it (number of elements in set)
typedef bitset<16> settr;

int n, m;
Point trees[16];

vector<settr> lines; // all lines passing through 3 trees or more
					// We will backtrack to shoose a subset of them

void UpdateLines(settr line)
{
	int i;

	// Make sure trees of this line is not subset of trees of an existing line
	//  (we are sure that the reverse cannot happen -> why?)

	for (i=0; i<lines.size(); i++)
		if ((lines[i]|line)==lines[i])
			return;
	
	lines.push_back(line);
}

// ind=current line index, nshoted=number of shooted trees, shoted=set of shooted trees
// nshots=current number of shots made so far

int BackTrack(int ind, int nshoted, settr shoted, int nshots)
{
	if(nshoted==m) // All trees have been shoted
		return nshots;

	// Remaining trees can only be shotted 2 by 2, because we have no more lines that
	//	pass through 3 trees or more
	if(ind==lines.size())
		return nshots + (m-nshoted+1)/2;

	int a=1000,b=1000;

	// newshoted is set of shoted trees after we use this line (this shot)
	settr newshoted = shoted;
	newshoted |= lines[ind];
	int newnshoted = newshoted.count();
	
	if(newnshoted-nshoted>2) // We are concerned with lines that can shoot 3 or more trees
	{
		// Try using this line (this shot)
		a=BackTrack(ind+1, newnshoted, newshoted, nshots+1);
	}

	// Try skipping this line (this shot)
	b=BackTrack(ind+1, nshoted, shoted, nshots);

	return min(a,b);
}

void Compute()
{
	lines.clear();
	int i, j, k;

	for(i=0;i<n;i++) for(j=i+1;j<n;j++)
	{
		settr line=0;

		// Put trees i, j in this line
		line|=(1<<i); line|=(1<<j);
		int numtrees=2;
		
		for(k=j+1;k<n;k++)
		{
			// Check if the three points on the same line (Cross product of
			//	two vectors of them = 0)

			if((Vect(trees[i],trees[k])^Vect(trees[j],trees[k]))==0)
			{
				line|=(1<<k);
				numtrees++;
			}
		}

		// We are concerned only with lines passing through 3 trees or more
		if(numtrees>=3)
		{
			// Add this line to our lines
			UpdateLines(line);
		}
	}

	cout << "Case #" << icase << ":" << "\n";
	cout << BackTrack(0, 0, 0, 0) << "\n";
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("ShotLines.in", "r", stdin);

	int i, j, numc;
	scanf("%d ", &numc);

	icase=0;

	for(i=0;i<numc;i++)
	{
		scanf("%d %d ", &n, &m);
		icase++;

		for (j=0; j<n; j++)
		{
			int x,y;
			scanf("%d %d ", &x, &y);
			trees[j]=Point(x,y);
		}

		Compute();
		if(i<numc-1) cout<<"\n";
	}

	return 0;
}
