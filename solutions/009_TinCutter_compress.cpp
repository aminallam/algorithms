// Problem: http://online-judge.uva.es/p/v3/308.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  308

#pragma warning(disable:4786)
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstdio>
using namespace std;

#define oo (0x7FFFFFFF)

//**************************************************************************
// Compress Grid /////////////////////////////////////////////////////////

struct Point{
	int x, y;
	Point() {}
	Point(int _x, int _y) {x=_x; y=_y;}
};
struct PairValues{
	int old_val, new_val;
	PairValues(int val){old_val = val;}
	bool operator < (const PairValues& p) const	{return (old_val<p.old_val);} //For set
	bool operator == (const PairValues& p) const {return (old_val==p.old_val);}//For find()
};
void CompressGrid(vector<Point>& points, int& w, int& h){
	set<PairValues> xs, ys;
	xs.insert(PairValues(oo));	xs.insert(PairValues(-oo));
	ys.insert(PairValues(oo));	ys.insert(PairValues(-oo));
	int i, cnt;
	for (i=0; i<points.size(); i++) {
		xs.insert(PairValues(points[i].x));
		ys.insert(PairValues(points[i].y));
	}
	set<PairValues>::iterator iter;
	cnt=1;
	for (iter=xs.begin(); iter!=xs.end(); iter++){
		((PairValues*) &(*iter))->new_val = cnt;
		cnt+=2;
	}
	w=cnt;
	cnt=1;
	for (iter=ys.begin(); iter!=ys.end(); iter++){
		((PairValues*) &(*iter))->new_val = cnt;
		cnt+=2;
	}
	h=cnt;
	for (i=0; i<points.size(); i++) {	// Convert All points
		Point& p=points[i];
		p.x = xs.find(PairValues(p.x))->new_val;
		p.y = ys.find(PairValues(p.y))->new_val;
	}
}

#define MAX_DIM (400+20)
char G[MAX_DIM][MAX_DIM];
int w,h;	// width, height of the grid, == rows, cols

void InitAssignGrid() {
	int x,y; for(x=0;x<w;x++) for(y=0;y<h;y++) G[x][y]=0;
	for(x=0;x<w;x++) G[x][0]=G[x][h-1]=1;	// Borders
	for(y=0;y<h;y++) G[0][y]=G[w-1][y]=1;	// Borders
}
void AssignPoint(Point p) {
	G[p.x][p.y]=1;
}
void AssignSegment(Point a, Point b) {
	int x, x1=a.x, x2=b.x;
	int y, y1=a.y, y2=b.y;
	if(y1>y2) {int t=y1;y1=y2;y2=t;}
	if(x1>x2) {int t=x1;x1=x2;x2=t;}
	if(x1==x2) for(y=y1;y<=y2;y++) G[x1][y]=1;
	if(y1==y2) for(x=x1;x<=x2;x++) G[x][y1]=1;
}

//**************************************************************************

vector<Point> points;	// The ith segment is points[2*i]-->points[2*i+1]
int n_seg;				// Number of segments (points.size()/2)

// This function uses BFS to fill either the paper, or a complete hole
// It will fill the paper only at the first pass (when num==0)
// Otherwise, it will fill a complete hole
void BFS(Point st, int num) 
{
	queue<Point> q;
	q.push(st);

	int x_diff[]={0,0,1,-1};
	int y_diff[]={1,-1,0,0};
	
	int i;
	
	while(!q.empty())
	{
		Point p=q.front();
		q.pop();

		for(i=0;i<4;i++)
		{
			Point new_p(p.x+x_diff[i], p.y+y_diff[i]);
			
			if(!G[new_p.x][new_p.y])
			{
				G[new_p.x][new_p.y]=1;
				q.push(new_p);
			}
			// This following code is not in ordinary BFS
			// It is specific to this problem (pass boundary)
			// It will look after the boundary line to see if there is a 0
			else if(num>0) // Note that when num=0 this is the pass filling the paper
			{
				Point new_p2(p.x+2*x_diff[i], p.y+2*y_diff[i]);
				
				if(!G[new_p2.x][new_p2.y])
				{
					G[new_p2.x][new_p2.y]=1;
					q.push(new_p2);
				}
			}
		}
	}
}

void GetNumHoles()
{
	int num=0;
	int x,y;

	// The first BFS will fale the paper outside the holes
	// Every other BFS will fill a complete hole

	for(x=0;x<w;x++) for(y=0;y<h;y++) if(!G[x][y])
	{
		G[x][y]=1;
		BFS(Point(x,y), num);
		num++; // Number of holes + 1 (for the first BFS of paper)
	}

	cout << (num-1) << endl;
}

void AssignSegments()
{
	// Initialize Grid to 0s and Make Borders of 1's (Sentinels)
	InitAssignGrid();

	// Put 1's corresponding to input segments
	int i;
	for(i=0;i<n_seg;i++)
		AssignSegment(points[i*2],points[i*2+1]);
}

void Compute()
{
	// Compress The grid. points will be updated to new compressed points
	// Note that while compression, a space is preserved between adjacent coords
	CompressGrid(points, w, h);

	// Put 1's in the grid G corresponding to the input segments
	AssignSegments();

	// Make BFSs to fill holes
	GetNumHoles();
}

int main()
{
	//freopen("Tin.in", "r", stdin);
	//freopen("Tin.out", "w", stdout);

	while(true)
	{
		scanf("%d ", &n_seg);
		if(n_seg==0) break;

		points.clear();

		int i;
		for(i=0;i<n_seg;i++)
		{
			Point p;
			scanf("%d %d ", &p.x, &p.y);
			points.push_back(p);
			scanf("%d %d ", &p.x, &p.y);
			points.push_back(p);
		}

		Compute();
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////
