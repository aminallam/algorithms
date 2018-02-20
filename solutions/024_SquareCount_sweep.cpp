// Problem: http://online-judge.uva.es/p/v110/11016.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11016

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

////////////////////////////////////////////////////////////////////////////////

#define EPS (1e-12)
typedef double Cord;

#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))

struct Point {
	Cord x, y;
	Point(){}
	Point(Cord _x, Cord _y):x(_x),y(_y){}
};

Point operator+(const Point &A,const Point&B) {return Point(A.x+B.x,A.y+B.y);}
Point operator-(const Point &A,const Point&B) {return Point(A.x-B.x,A.y-B.y);}
Point operator*(Cord c, const Point &A) {return Point(c*A.x,c*A.y);}
Cord operator^(const Point&A,const Point&B) {return A.x*B.y-A.y*B.x;} // Cross Prod
Cord operator*(const Point&A,const Point&B) {return A.x*B.x+A.y*B.y;} // Dot Prod

Point Vect(Point a, Point b){return (b-a);}     //               a
Point Perp(Point a){return Point(-a.y, a.x);}   // <--Perp(a)--  |

int InterPoint(Point p1, Point p2, Point q1, Point q2, Point& r1)	// lines p1-p2,q1-q2
{
	Point vp=Vect(p1,p2);
	Point vq=Vect(q1,q2);
	if ((vp^vq)==0) return 0;
	Point w=Vect(q1,p1);
	double s = -(double)(Perp(vq)*w)/(Perp(vq)*vp);
	r1=p1+s*vp;
	return 1;
}

////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	Point p1, p2;	// p1 has min y, p2 has max y
	double xl, xr;	// xl = minx, xr = maxx, xs resulting from intersection of the edge
};						// with current horizontal line of the grid

enum {REMOVE, ADD};

struct Event
{
	int edge_id;	// id in edges
	int type;		// {REMOVE, ADD}
	int y;			// when to apply this event

	bool operator < (const Event& ev) const	// events will be sorted by y
	{								// in tie REMOVE before ADD, in tie, by index
		if(y!=ev.y) return y<ev.y;	// avoid equal events, as set<> will consider them one
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
	if(e.p1.y==e.p2.y)	return;
	if(e.p1.y>e.p2.y){Point t=e.p1; e.p1=e.p2; e.p2=t;}

	Event ev;
	ev.edge_id = edges.size();
	
	ev.type=ADD;
	ev.y=e.p1.y;
	events.push_back(ev);

	ev.type=REMOVE;
	ev.y=e.p2.y;
	events.push_back(ev);
	
	edges.push_back(e);
}

// Edges are sorted by xl, then by xr

struct EdgeCmp
{
bool operator() (const int& u, const int& v) const
{
	Edge& e1 = edges[u];
	Edge& e2 = edges[v];

	if(fabs(e1.xl-e2.xl)>EPS) return e1.xl<e2.xl;
	if(fabs(e1.xr-e2.xr)>EPS) return e1.xr<e2.xr;
	return u<v;
}
};

// Recompute intersectios of this edge with the curren horizontal gris line y
//  Note that we mean the horiziontal line of cells, it has a horizontal line above,
//   and a horizontal line under, we keep x's intersections

void UpdateXs(Edge& e, int y)
{
	Point inter;
	double x1, x2;
	
	InterPoint(e.p1, e.p2, Point(0,y), Point(10000,y), inter); x1=inter.x;
	InterPoint(e.p1, e.p2, Point(0,y+1), Point(10000,y+1), inter); x2=inter.x;
	
	e.xl = min(x1,x2);
	e.xr = max(x1,x2);
}

void Compute()
{
	int i;
	Edge e;

	edges.clear();
	events.clear();

	for(i=1;i<n;i++)
	{
		e.p1=poly[i-1];
		e.p2=poly[i];
		InsertEdge(e);
	}

	e.p1=poly[n-1];
	e.p2=poly[0];
	InsertEdge(e);

	// We will sort them only once, because they will keep thier relative ordering
	//  until end

	sort(events.begin(), events.end());

	///////////////////////////////////////////////////////////

	// The set contains indexes in edges vector, of active edges (added and not removed)

	set<int, EdgeCmp> cur_edges;

	int next_ev=0;
	int sum1=0, sum2=0;

	// Iterate on grid horizontal lines one by one

	int y;
	
	for(y=events[next_ev].y; y<10000; y++)
	{
		vector<int> added_edges;

		if (next_ev>=events.size())
			break;
		
		// Apply all events that should be applied now (add-or-remove new lines)

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

		// Compute Number of grid cells inside the polygon and within the
		//	current horizontal line
		
		int prev=-1;

		for(it=cur_edges.begin(); it!=cur_edges.end(); it++)
		{
			Edge& e1 = edges[*it]; it++;
			Edge& e2 = edges[*it];
			
			int num = max(0, floor(e2.xl)-ceil(e1.xr));
			sum1 += num/2;
			sum2 += num/2;
			
			if(num%2==1)
			{
				int poo = floor(e2.xl)+y;
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
	//freopen("sweep.in", "r", stdin);

	int i;

	while(true)
	{
		scanf("%d\n", &n);
		if (n==0) break;

		poly.clear();

		for (i=0; i<n; i++)
		{
			Point p;
			
			scanf("%lf %lf\n", &p.x, &p.y);
			poly.push_back(p);
		}

		Compute();
	}

	return 0;
}
