// Problem: http://online-judge.uva.es/p/v110/11018.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11018

#pragma warning(disable:4786)
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
#include <cstdio>
using namespace std;

#define EPS (1e-12)
#define oo 0x7FFFFFFF

////////////////////////////////////////////////////////////////////////////////

// The following function computes the distance between two points on earth
//  (or a planet) if we consider earth as a sphere

// p_long = longitude (angle from +pi (east of gw) to -pi (west)), gw=0
// p_lat = latitude (angle from +pi/2 (north of equator) to -pi/2)
// r = planet radius

double SphericalDist(double p_long,double p_lat,double q_long,double q_lat,double r) {
	double a=(1.0-cos(q_lat-p_lat))/2,b=cos(p_lat)*cos(q_lat)*(1.0-cos(q_long-p_long))/2;
	double c=2*atan2(sqrt(a+b),sqrt(1-a-b)); return r*c;
}

////////////////////////////////////////////////////////////////////////////////

int icase;
#define MAX_LOC 100

// This array will contain all names of places
string names[MAX_LOC];

// Number of places
int n;

// Get the index in names[] that corresponds to place with name str
int GetIndex(string& str){int i; for(i=0;i<n;i++) if(names[i]==str) return i; return -1;}

// Input coordinates of places
double lat[MAX_LOC];
double lon[MAX_LOC];

// Graph contains distances between all places
int g[MAX_LOC][MAX_LOC];

/////////////////////////////////////////////////////////////////////////////

void Initialize()
{
	// Get all distances between all places and save them in g[]
	//  so, we are not obligated to compute them every time

	int i, j;
	for(i=0;i<n;i++) for(j=i+1;j<n;j++)
	{
		g[i][j]=g[j][i]=
			SphericalDist(lon[i], lat[i], lon[j], lat[j], 3390.0)+0.5+EPS;
	}

	if (icase>1) cout << "\n";
	cout << "Scenario " << icase << ":\n";
	cout << "------------------------------\n";
}

/////////////////////////////////////////////////////////////////////////////

struct Node
{
	int dist;
	int ind;
	bool operator<(const Node& n) const{return dist>n.dist;}
};

/////////////////////////////////////////////////////////////////////////////

// It is good to put large arrays outside the functions (global)

bool done[MAX_LOC];	// done[i]=true if we processed this node before (poped from queue)
int d[MAX_LOC];	// d[i]=distance from start to i
int pi[MAX_LOC]; // pi[i]=previous node to i in the path from start to i

// Get the distance between src and dst, if we can move directly between any
//	two nodes with direct distance <= range

bool Dijkstra(int src, int dst, int range, bool disp=false)
{
	int i;
	
	Node node;
	node.dist=0;
	node.ind=src;
	
	for(i=0;i<n;i++) {d[i]=oo; pi[i]=-1; done[i]=false;}
	d[src]=0;

	priority_queue<Node, vector<Node> > q;
	q.push(node);

	while(!q.empty())
	{
		node = q.top(); q.pop();
		
		if(node.ind == dst) break;
		if(done[node.ind]) continue;

		done[node.ind]=true;

		for(i=0;i<n;i++)
		{
			// We can reach node i directly only if distance is less than range
			if(g[node.ind][i]<=range && !done[i])
			{
				Node new_node;
				new_node.ind=i;
				new_node.dist=node.dist+g[node.ind][i];

				// We reached node i for the first time, or in less distance than before
				if(new_node.dist<d[new_node.ind])
				{
					d[new_node.ind] = new_node.dist;
					pi[new_node.ind] = node.ind;
					q.push(new_node);
				}
			}
		}
	}
	
	if(d[dst]==oo) return false;
	
	// Get the actual path from the pi[] array
	if(disp) // disp is true if we need to output the actual path
	{
		vector<int> path;
		int cur_node = dst;

		while(true)
		{
			path.push_back(cur_node);
			if(cur_node==src) break;
			cur_node = pi[cur_node];
		}

		// The path is reversed, so, adjust it
		reverse(path.begin(), path.end());
		
		for(i=0;i<path.size();i++)
		{
			cout << names[path[i]] << " at " << d[path[i]] << " km.\n";
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////

void Compute(int src, int dst, int range)
{	
	cout << "From " << names[src] << " to " << names[dst] << " with range " << range << " km:\n";
	
	// Check if the current range is sufficient for a path to exist
	
	if(Dijkstra(src, dst, range, true))
	{
		cout << "------------------------------\n";
		return;
	}

	// Use binary search to determine minimum required range
	
	int lo=range+1, hi=1000000000;
	
	while(lo<hi)
	{
		int mid=lo+(hi-lo)/2;
		if(Dijkstra(src, dst, mid)) hi=mid;
		else lo=mid+1;
	}

	// Now, lo is the minimum range for a path to exist

	cout << "No route for this range, minimum required range is " << lo << " km.\n";
	cout << "------------------------------\n";
}

/////////////////////////////////////////////////////////////////////////////

// Temporary buffers for input
char buffer1[100000];
char buffer2[100000];

int main()
{
	//freopen("MarsBuggy.in", "r", stdin);

	int i;
	icase=0;
	
	while(true)
	{
		scanf("%d\n", &n);
		if (n==0) break;

		icase++;

		for (i=0; i<n; i++)
		{
			scanf("%s %lf %lf\n", buffer1, &lat[i], &lon[i]);
			names[i]=buffer1;
		}

		// This is called only one time for each complete test case
		//  As distances will not change
		Initialize();
		
		int q;
		scanf("%d\n", &q);
		
		for (i=0; i<q; i++)
		{
			string s1, s2; int range;
			scanf("%s %s %d\n", buffer1, buffer2, &range);
			s1=buffer1; s2=buffer2;

			// This line will compute distance from s1 to s2 using Dijkstra
			//	with priority queue (uniform cost search)

			Compute(GetIndex(s1), GetIndex(s2), range);
		}
	}

	return 0;
}
