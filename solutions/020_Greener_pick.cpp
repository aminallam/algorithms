// Problem: http://online-judge.uva.es/p/v110/11017.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 11017

//#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int icase;

double pi;

//typedef __int64 LL;
//ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
//istream& operator>>(istream& in,LL& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

typedef long long LL;

#define EPS (1e-12)
double PI() {return atan(1)*4;}	// 3.14159265358979

struct Point{
	LL x, y;
	Point() {}
	Point(LL _x, LL _y) {x=_x; y=_y;}
};
LL operator^(const Point&A,const Point&B) {return A.x*B.y-A.y*B.x;} // Cross Prod

///////////////////////////////////////////////////////////////////////////////////

LL gcd(LL a, LL b) {if(b==0)return a; return gcd(b,a%b);}

LL PolygonAreaDbl(vector<Point>& polygon){
	int i, n=polygon.size();
	LL area=polygon[n-1]^polygon[0];
	for(i=0;i<n-1;i++) area+=polygon[i]^polygon[i+1];
	return area;
}

LL Abs(LL num){if(num<0)return -num;return num;}

int NumLatticeOnEdge(int m, int n) {return 1+gcd(m,n);}//edge(0,m)-(n,0),include end pts
LL PickNumLatticeInsidePoly(vector<Point>& poly){
	int i,n=poly.size(); LL area2=Abs(PolygonAreaDbl(poly));
	LL nponedge=NumLatticeOnEdge(Abs(poly[n-1].x-poly[0].x),Abs(poly[n-1].y-poly[0].y))-n;
	for(i=0;i<n-1;i++)
		nponedge+=NumLatticeOnEdge(Abs(poly[i].x-poly[i+1].x), Abs(poly[i].y-poly[i+1].y));
	return (area2+2-nponedge)/2; //area2=2*(poly area),nponedge=num lattices on poly edges
}

///////////////////////////////////////////////////////////////////////////////////

// Rotate by 90, then scale to make new valid grid (dist between grid points=1)
Point Adjust(Point v){
	return Point(v.x - v.y, v.x + v.y);
}

// poly= polygon in the old grid. Applying Pick on it will get number of green points only
// bigpoly= polygon in the new grid. Applying Pick on it will get number of all points

vector<Point> poly;
vector<Point> bigpoly;

int d, theta, n;

void Compute()
{
	if(n<3) {cout << "0 0\n"; return;}

	// We need number of red points in polygon
	//	(=Number of all points-Number of green points)

	LL nump=PickNumLatticeInsidePoly(bigpoly)-PickNumLatticeInsidePoly(poly);

	// Note that this is not good as area is computed twice, but
	//  we make it for clarity

	LL area2=Abs(PolygonAreaDbl(poly));

	// Multiply the area of polygon by the area of a small sheared square
	//  Note that we convert the theta to radians
	//	The area of the small sheared square = sin(theta*pi/180.0)*d*d
	
	double reqarea = (double) (area2/2.0)*sin(theta*pi/180.0)*d*d;

	cout.precision(0);
	cout.setf(ios::fixed);

	cout << nump << " " << reqarea << "\n";
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("RedGreen.in", "r", stdin);
	int i;

	pi=PI();

	while(true)
	{
		poly.clear();
		bigpoly.clear();

		scanf("%d %d %d ", &d, &theta, &n);
		if(d==0 && theta==0 && n==0) break;

		for(i=0;i<n;i++)
		{
			LL x,y;
			scanf("%I64d %I64d ", &x, &y);

			poly.push_back(Point(x,y));
			bigpoly.push_back(Adjust(Point(x,y)));
		}
		
		Compute();
	}

	return 0;
}
