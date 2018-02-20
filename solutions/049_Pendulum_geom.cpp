#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

#define EPS (1e-11)

#define MAX_HOOKS 500

typedef double Cord;

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
// Cross Prod Returns +ve if B is counter clockwise from A with respect to the origin
// Also, it is double the signed area of triangle formed by A, B
												//               ^
                                                //               |
#define Vect(a, b) (b-a)						//               a
#define Perp(a) (Point(-a.y, a.x))				// <--Perp(a)--  |

Cord LengthSqr(Point v) {return (v*v);}
Cord DistanceSqr(Point a, Point b){return LengthSqr(Vect(a,b));}

double Length(Point v){return sqrt(LengthSqr(v));}
double Distance(Point a, Point b){return sqrt(DistanceSqr(a,b));}
Point Normalize(Point a) {return (1.0/Length(a)) * a;}

double PI() {return atan(1)*4;}	// 3.14159265358979
						// Not defined only if v=(0,0)
double Angle(Point v){	// ret = +ve CCW angle between x-axis and v
	double res = atan2(v.y,v.x);
	if (res < 0-EPS) res = 2*PI()+res;
	return res;
}
double Angle(Point a, Point b){	// ret = +ve CCW angle from a to b
	double res = Angle(b)-Angle(a);
	if (res < 0-EPS) res = 2*PI()+res;
	return res;
}

double r;
int n;
Point Hooks[MAX_HOOKS+1];

ostream& operator<<(ostream& out,const Point& pp){cout<<"("<<pp.x<<","<<pp.y<<")";return out;}

void Compute()
{
	int i;

	double pi=PI();
	
	int org=n;
	Point cur(-r,0);
	double max_angle=pi;
	
	double path=0;

	while(true)
	{
		//cout<<Hooks[org]<<cur<<endl;

		double best_ang=2*pi;
		double best_dist=0;
		int best_org=-1;

		for(i=0;i<n;i++) if(i!=org && Hooks[i].y<0)
		{
			Point a=Vect(Hooks[org],cur);
			Point b=Vect(Hooks[org],Hooks[i]);

			double ang=Angle(a,b);
			double da=Length(a);
			double db=Length(b);

			if(ang<best_ang || ang==best_ang && db>best_dist)
			{
				if(da>=db)
				{
					best_org=i;
					best_dist=db;
					best_ang=ang;
				}
			}
		}

		double old_len=Distance(Hooks[org],cur);

		if(best_ang>max_angle)
		{
			path+=max_angle*old_len;
			path*=2; // to return
			printf("%.2lf\n",path);
			return;
		}

		if(best_org==-1)
		{
			printf("%.2lf\n",max_angle*old_len);
			return;
		}

		path+=best_ang*old_len;

		double new_len=old_len-Distance(Hooks[org],Hooks[best_org]);
		cur=Hooks[best_org]+new_len*Normalize(Vect(Hooks[org],Hooks[best_org]));
		org=best_org;

		if(-Hooks[org].y>=new_len)
		{
			max_angle=2*pi;
		}
		else
		{
			double len=sqrt(new_len*new_len-Hooks[org].y*Hooks[org].y);
			Point mp=Point(Hooks[org].x+len,0);

			Point a=Vect(Hooks[org],cur);
			Point b=Vect(Hooks[org],mp);
			max_angle=Angle(a,b);
		}
	}
}

int main()
{
	//freopen("orbit.in", "r", stdin);
	//freopen("orbit.out", "w", stdout);

	int ncase=0;

	while(true)
	{
		scanf("%d %lf ", &n, &r);
		if(r<EPS) break;

		int i;
		for(i=0;i<n;i++)
		{
			int x,y;
			scanf("%d %d ", &x, &y);
			Hooks[i].x=x; Hooks[i].y=y;
		}

		Hooks[n]=Point(0,0);

		printf("Pendulum #%d\nLength of periodic orbit = ",++ncase);
		Compute();
		printf("\n");
	}

	return 0;
}
