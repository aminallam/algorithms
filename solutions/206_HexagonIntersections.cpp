#pragma warning(disable:4786)
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace std;

#define TEST_EPS (1e-9)
int dcomp(double a, double b) {if(fabs(a-b)<TEST_EPS) return 0; return (a>b)?1:-1;}

#define LL __int64
ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
istream& operator>>(istream& in,LL& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

//////////////////////////////////////////////////////////////////////
#ifndef LL
typedef long long LL;
#endif
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

// The first important thing to realize is that you can convert the hexagonal grid so that
//	the corners lie on integer coordinates. An affine transformation (translation, scaling,
//	rotation, shearing, and reflection) applied to any two-dimensional figure will preserve
//	straight lines. 

struct Point {
	LL x, y;
	Point(){}
	Point(LL _x, LL _y):x(_x),y(_y){}
};

Point operator+(const Point& A,const Point& B) {return Point(A.x+B.x,A.y+B.y);}
Point operator-(const Point& A,const Point& B) {return Point(A.x-B.x,A.y-B.y);}
Point operator*(LL c, const Point& A) {return Point(c*A.x,c*A.y);}
LL operator*(const Point& A,const Point& B) {return A.x*B.x+A.y*B.y;} // Dot Prod
LL operator%(const Point& A,const Point& B) {return A.x*B.y-A.y*B.x;} // Cross Prod

bool operator==(const Point&a, const Point&b) 
{return a.x==b.x && a.y==b.y;}

#define Vect(a,b) ((b)-(a))

// IsLeft(): tests if a Point is Left|On|Right of an infinite line.
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2 on the line, // <0 for P2 right of the line
LL IsLeft(Point p0, Point p1, Point p2){return (Vect(p0, p1)%Vect(p0, p2));}

enum {SEG=1,RAY=2,LINE=4};
enum {CLOSED,EXCLUDE_START=8,EXCLUDE_END=16,OPEN=24}; // Exclude or include end Points

LL InterPoint(Point p1, Point p2, LL pType,
			   Point q1, Point q2, LL qType) // lines p1-p2,q1-q2
{
	Point vp=Vect(p1,p2);
	Point vq=Vect(q1,q2);

	LL cross=vp%vq;
	if(cross==0) return 0; // Parallel

	Point w=Vect(p1,q1);

	LL snum=w%vq, tnum=w%vp;
	if(cross<0) {cross=-cross;snum=-snum;tnum=-tnum;}

	if(!(pType & LINE) && (snum<0 || snum==0 && (pType & EXCLUDE_START))) return 0;
	if((pType & SEG) && (snum>cross || snum==cross && (pType & EXCLUDE_END))) return 0;

	if(!(qType & LINE) && (tnum<0 || tnum==0 && (qType & EXCLUDE_START))) return 0;
	if((qType & SEG) && (tnum>cross || tnum==cross && (qType & EXCLUDE_END))) return 0;

	return 1;
}

// Determine if the Point p0 is on the line/ray/segment p1-p2
LL PointOn(Point p1, Point q1, Point q2, LL type)
{
	Point vp1=Vect(q1,p1);
	Point vp2=Vect(q2,p1);
	Point vq=Vect(q1,q2);

	LL cross=vp1%vq;
	if(cross!=0) return 0;

	if(p1.x==q1.x && p1.y==q1.y){if(!(type & LINE) && EXCLUDE_START) return 0;return 1;}
	if(p1.x==q2.x && p1.y==q2.y){if((type & SEG) && EXCLUDE_END) return 0;return 1;}

	if(!(type & LINE)) {if(vp1*vq<0) return 0;}
	if((type & SEG)) {if(vp2*vq>0) return 0;}

	return 1;
}

// MIDDLE: Our line should pass betwen the two Points (exclusive)
// THROUGH: Our line should pass through the two Points
// LEFT: should pass throught the first Point and left to vector
// RIGHT: should pass throught the first Point and right to vector
enum {MIDDLE, THROUGH, LEFT, RIGHT};

struct Move
{
	LL		type;	// {MIDDLE, THROUGH, LEFT, RIGHT}
	Point	p1,p2;	// The two Points to test with (assuming prev cell center is 0,0)
	Point	np;		// The new cell center (assuming prev cell center is 0,0)
	Move(){}
	Move(LL _type, Point _p1, Point _p2, Point _np) {type=_type;p1=_p1;p2=_p2;np=_np;}
};

vector<Move> moves;

Point Rotate(Point p) // Rotate a point in our system
{
	return Point(p.y, -p.x+p.y);
}

void GenerateHexagonalMoves()
{
	int i,j;
	Move basic_moves[]=
	{
		Move(THROUGH, Point(0,1), Point(0,2), Point(0,3)),
		Move(MIDDLE, Point(1,1), Point(0,1), Point(1,2)),
		Move(LEFT, Point(1,1), Point(2,2), Point(1,2)),
		Move(RIGHT, Point(0,1), Point(0,2), Point(1,2))
	};

	for(i=0;i<4;i++)
	{
		Move m=basic_moves[i];
		moves.push_back(m);
		
		for(j=1;j<6;j++)
		{
			m.p1=Rotate(m.p1);
			m.p2=Rotate(m.p2);
			m.np=Rotate(m.np);
			moves.push_back(m);
		}
	}
}

// cur=center of current cell, <start,end> is the going ray
// prev is the previous cell which we do not want to go there again!
Point ApplyMove(Point prev, Point cur, Point start, Point end)
{
	int i, num_moves=moves.size();

	for(i=0;i<num_moves;i++)
	{
		Move m=moves[i];
		
		if(m.type==THROUGH)
		{
			if(PointOn(cur+m.p1, start, end, RAY) && PointOn(cur+m.p2, start, end, RAY))
				if(!(cur+m.np==prev)) return cur+m.np;
		}
		else if(m.type==MIDDLE)
		{
			if(InterPoint(cur+m.p1, cur+m.p2, SEG|OPEN, start, end, RAY))
				if(!(cur+m.np==prev)) return cur+m.np;
		}
		else if(m.type==LEFT)
		{
			if(PointOn(cur+m.p1, start, end, RAY) && IsLeft(end, cur+m.p1, cur+m.p2)>0)
				if(!(cur+m.np==prev)) return cur+m.np;
		}
		else if(m.type==RIGHT)
		{
			if(PointOn(cur+m.p1, start, end, RAY) && IsLeft(end, cur+m.p1, cur+m.p2)<0)
				if(!(cur+m.np==prev)) return cur+m.np;
		}
	}
	return cur;
}

Point Transform(Point p) // Transform point in problem input to our coordinate system
{
	return Point(p.x+p.y, -p.x+2*p.y);
}

Point UnTransform(Point p) // Reverse of previous
{
	return Point((p.y-2*p.x)/-3, (p.x+p.y)/3);
}

class HexagonIntersections
{
public:
	int count(int x0, int y0, int x1, int y1)
	{
		Point start=Transform(Point(x0,y0));
		Point end=Transform(Point(x1,y1));

		GenerateHexagonalMoves();

		Point prev=start;
		Point cur=start;
		int num=1;

		while(!(cur==end))
		{
			Point new_cur=ApplyMove(prev, cur, start, end);
			prev=cur;
			cur=new_cur;
			num++;
		}

		return num;
	}
};

//////////////////////////////////////////////////////////////////////

void AdditionalTests()
{
}

int main()
{
	int i=0;
	bool flag;
	int cases_cnt=-1;
	bool all_flag=true;

	{
	//Test case # 0:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(1, -2, 3, 1);
	delete var0;

	flag=true;
	if(var1!=4)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(-2004, -1002, -2000, -1000);
	delete var0;

	flag=true;
	if(var1!=3)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(54, 93, 64, 95);
	delete var0;

	flag=true;
	if(var1!=11)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(0, 0, 19, 20);
	delete var0;

	flag=true;
	if(var1!=26)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(0, 0, 19, -20);
	delete var0;

	flag=true;
	if(var1!=40)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	HexagonIntersections* var0=new HexagonIntersections;
	int var1 = var0->count(2,4,0,0);
	delete var0;

	flag=true;
	if(var1!=3)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	if(all_flag==false) cout << "Some Cases FAILED." << endl;
	else cout << "All cases passed." << endl;

	AdditionalTests();

	return 0;
}

//////////////////////////////////////////////////////////////////////

/*

Problem Statement 
     
A hexagonal grid is a tiling of the plane consisting solely of regular 
hexagons. You will be given two pairs of coordinates, identifying two 
hexagons in the grid. Consider a line segment connecting the centers 
of these two hexagons, and return the number of hexagons that this 
line segment intersects. 
Only count hexagons if the line passes through their interior. Do not 
count a hexagon if the line only intersects one of its corners or is 
coincident with one of its edges. 
Hexagons will be identified by a pair of coordinates, as shown in the 
following diagram. The first coordinate is proportional to the 
horizontal distance from the vertical axis. The second coordinate is 
proportional to the vertical distance from the diagonal axis. 

Definition 
     
Class: 
HexagonIntersections 
Method: 
count 
Parameters: 
int, int, int, int 
Returns: 
int 
Method signature: 
int count(int x0, int y0, int x1, int y1) 
(be sure your method is public) 
     

Constraints 
- 
x0, y0, x1, and y1 will be between -10000 and 10000, inclusive. 
- 
(x0,y0) and (x1,y1) will not be the same point. 
Examples 
0) 

     
1 
-2 
3 
1 
Returns: 4 
A line between the centers of hexagons (1,-2) and (3,1) intersects 4 
hexagons: 

1) 

     
-2004 
-1002 
-2000 
-1000 
Returns: 3 
This line is coincident with the edges of several hexagons, but it 
only intersects the interior of three: 

2) 

     
54 
93 
64 
95 
Returns: 11 

3) 

     
0 
0 
19 
20 
Returns: 26 

4) 

     
0 
0 
19 
-20 
Returns: 40 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
