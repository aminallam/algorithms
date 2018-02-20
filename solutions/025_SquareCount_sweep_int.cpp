// Problem: http://online-judge.uva.es/p/v110/11016.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11016

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// This version uses integer only, no doubles
// This is:
//	1) Safer, we are not worry of precision error, like, a line passing throw
//		a corner of cell, but we consider it passing through the cell itself because
//		of rounding issues, or vice versa
//  2) Faster
////////////////////////////////////////////////////////////////////////////////

//typedef __int64 LL;
//ostream& operator<<(ostream& out,const int& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
//istream& operator>>(istream& in,int& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

typedef long long LL;

#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))

struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):x(_x),y(_y){}
};

struct Fraction{
	int a,b;	// a/b, b>0, not simplified
	int v0,v1;	// v0=lower bound integer, v1=upper bound integer

	Fraction(){}
	Fraction(int ia, int ib) {Set(ia,ib);}
	void Set(int ia, int ib){
		a=ia; b=ib; if(b<0) {b=-b; a=-a;} v0=a/b; v1=v0;
		if(a%b!=0){if(a>0) v1++; else v0--;}
	}
};
int Compare(const Fraction& f0, const Fraction& f1){
	LL v1=(LL)f0.a*f1.b, v2=(LL)f1.a*f0.b; // LL to avoid overflow
	if(v1>v2) return 1; if(v1<v2) return -1; return 0;
}

struct Line { // Every thing here in integers: ax+by+c=0 (NOT TESTED)
	int a, b, c;

	void Set(Point p0, Point p1){
		a=p1.y-p0.y; b=p0.x-p1.x;
		c=-(a*p0.x+b*p0.y);
	}
	Fraction XionHorz(int y){ // Intersection with horizontal line: Y=y
		return Fraction(-b*y-c, a);
	}
};

////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	Line line; // Line representing edge
	int y0, y1; // y0=edge start, y1=edge end
	Fraction xL, xR; // xion with current y during sweeping

	void SetEdge(Point p0, Point p1)
	{
		line.Set(p0, p1);
		y0=min(p0.y,p1.y); y1=max(p0.y,p1.y);
	}
};
						
enum {REMOVE, ADD};

struct Event
{
	int edge_id;	// id in edges
	int type;		// {REMOVE, ADD}
	int y;			// when to apply this event

	bool operator < (const Event& ev) const	// events wiint be sorted by y
	{								// in tie REMOVE before ADD, in tie, by index
		if(y!=ev.y) return y<ev.y;	// avoid equal events, as set<> wiint consider them one
		if(type!=ev.type) return type<ev.type;
		return edge_id<ev.edge_id;
	}
};

int n;

vector<Point> poly;
vector<Edge> edges;
vector<Event> events;

// Insert edge and insert two events associated with it (ad, remove)

void InsertEdge(Edge e)
{
	if(e.y0==e.y1) return;

	Event ev;
	ev.edge_id = edges.size();
	
	ev.type=ADD;
	ev.y=e.y0;
	events.push_back(ev);

	ev.type=REMOVE;
	ev.y=e.y1;
	events.push_back(ev);
	
	edges.push_back(e);
}

// Edges are sorted by xl, then by xr

struct EdgeCmp
{
bool operator() (const int& u, const int& v) const
{
	Edge& e0 = edges[u];
	Edge& e1 = edges[v];

	int comp;
	comp=Compare(e0.xL, e1.xL); if(comp!=0) return comp<0;
	comp=Compare(e0.xR, e1.xR); if(comp!=0) return comp<0;
	return u<v;
}
};

// Recompute intersectios of this edge with the curren horizontal gris line y
//  Note that we mean the horiziontal line of ceints, it has a horizontal line above,
//   and a horizontal line under, we keep x's intersections

void UpdateXs(Edge& e, int y)
{
	Point inter;
	
	Fraction f0 = e.line.XionHorz(y);
	Fraction f1 = e.line.XionHorz(y+1);
	
	int comp;
	comp=Compare(f0, f1);

	if(comp<=0) {e.xL=f0; e.xR=f1;}
	else  {e.xL=f1; e.xR=f0;}
}

void Compute()
{
	int i;
	Edge e;

	edges.clear();
	events.clear();

	for(i=1;i<n;i++)
	{
		e.SetEdge(poly[i-1],poly[i]);
		InsertEdge(e);
	}

	e.SetEdge(poly[n-1],poly[0]);
	InsertEdge(e);

	sort(events.begin(), events.end());

	// The set contains indexes in edges vector, of active edges (added and not removed)

	set<int, EdgeCmp> cur_edges;

	int next_ev=0;
	int sum1=0, sum2=0;

	// Iterate on grid horizontal lines one by one

	int y;
	
	for(y=events[next_ev].y; y<10000; y++)
	{
		vector<int> added_edges;

		if(next_ev>=events.size())
			break;
		
		// Apply aint events that should be applied now (add-or-remove new lines)

		while(events[next_ev].y==y)
		{
			if(events[next_ev].type==REMOVE) cur_edges.erase(events[next_ev].edge_id);
			else added_edges.push_back(events[next_ev].edge_id);
			next_ev++;
		}

		// Recompute intersections
		
		set<int, EdgeCmp>::iterator it;
		for(it=cur_edges.begin(); it!=cur_edges.end(); it++) 
			UpdateXs(edges[*it], y);
		
		// Insert new edges in our active set of edges
		
		for(i=0;i<added_edges.size();i++) 
		{
			UpdateXs(edges[added_edges[i]], y);
			cur_edges.insert(added_edges[i]);
		}

		// Compute Number of grid ceints inside the polygon and within the
		//	current horizontal line
		
		int prev=-1;

		for(it=cur_edges.begin(); it!=cur_edges.end(); it++)
		{
			Edge& e0 = edges[*it]; it++;
			Edge& e1 = edges[*it];
			
			int num=max(0,e1.xL.v0-e0.xR.v1);
			sum1 += num/2;
			sum2 += num/2;

			if(num%2==1)
			{
				int poo = e1.xL.v0+y;
				if(poo%2) sum1++; else sum2++;
			}
		}
	}

	if(sum1<sum2) {int t=sum1;sum1=sum2;sum2=t;}
	cout << sum1 << " " << sum2 << "\n";
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("in.txt", "r", stdin);

	int i;

	while(true)
	{
		scanf("%d ", &n);
		if(n==0) break;

		poly.clear();

		for(i=0;i<n;i++)
		{
			Point p;
			scanf("%d %d ", &p.x, &p.y);
			poly.push_back(p);
		}

		Compute();
	}

	return 0;
}
