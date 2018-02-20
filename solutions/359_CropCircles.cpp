#pragma warning(disable:4786)
#include <iostream>
#include <cmath>
#include <cstdio>
#include <conio.h>
using namespace std;

#define TEST_EPS (1e-9)
int dcomp(double a, double b) {if(fabs(a-b)<TEST_EPS) return 0; return (a>b)?1:-1;}

typedef __int64 LL;
ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
istream& operator>>(istream& in,LL& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

//////////////////////////////////////////////////////////////////////
//typedef long long LL;
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <deque>
using namespace std;

typedef LL Type;

LL gcd(LL a, LL b) {if(b==0)return a; return gcd(b,a%b);}

struct Frac {
	Type a,b;
	
	Frac(){} Frac(Type ia, Type ib) {Set(ia,ib);}
	void Set(Type ia, Type ib){a=ia; b=ib; if(b<0) {b=-b; a=-a;} Simplify();}
	void GetBounds(Type& v0, Type& v1){v0=a/b; v1=v0; if(a%b!=0){if(a>0) v1++; else v0--;}}
	void operator=(const Type& ia){a=ia; b=1;}
	void Simplify() {LL g=gcd(abs(a),b); a/=g; b/=g;}
};
Frac operator-(const Frac& f0){return Frac(-f0.a,f0.b);}
Frac operator+(const Frac& f0, const Frac& f1){return Frac(f0.a*f1.b+f1.a*f0.b,f0.b*f1.b);}
Frac operator-(const Frac& f0, const Frac& f1){return Frac(f0.a*f1.b-f1.a*f0.b,f0.b*f1.b);}
Frac operator*(const Type& ia, const Frac& f1){return Frac(ia*f1.a,f1.b);}
Frac operator*(const Frac& f0, const Frac& f1){return Frac(f0.a*f1.a,f0.b*f1.b);}
Frac operator/(const Frac& f0, const Frac& f1){return Frac(f0.a*f1.b,f0.b*f1.a);}

int Compare(const Frac& f0, const Frac& f1){
	Type v1=f0.a*f1.b, v2=f1.a*f0.b; if(v1>v2) return 1; if(v1<v2) return -1; return 0;
}

typedef Frac Cord;

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

#define Vect(a,b) ((b)-(a))						//               a
#define Perp(a) (Point(-((a).y), (a).x))			// <--Perp(a)--  |

Point InterPoint(Point p1, Point p2, Point q1, Point q2) // lines p1-p2,q1-q2
{
	Point vp=Vect(p1,p2);
	Point vq=Vect(q1,q2);
	Point w=Vect(q1,p1);
	Frac s = -((Perp(vq)*w)/(Perp(vq)*vp));
	return p1+(s*vp);
}

class CropCircles
{
public:

	struct Circle
	{
		Point c;
		Frac r;

		bool operator<(const Circle& cir) const
		{
			int val;
			val=Compare(c.x,cir.c.x); if(val!=0) return val<0;
			val=Compare(c.y,cir.c.y); if(val!=0) return val<0;
			val=Compare(r,cir.r); if(val!=0) return val<0;
			return false;
		}
	};

	int n;
	Point p[50];

	set<Circle> circles;

	int countCircles(vector<int> x, vector<int> y)
	{
		n=x.size();
		
		int i,j,k;
		for(i=0;i<n;i++)
		{
			p[i].x=x[i];
			p[i].y=y[i];
		}

		for(i=0;i<n;i++) for(j=i+1;j<n;j++) for(k=j+1;k<n;k++)
		{
			if((Vect(p[i],p[j])^Vect(p[j],p[k])).a==0)
				continue;

			Circle cir;

			Point a,ta,b,tb;
			
			a=Frac(1,2)*(p[i]+p[j]);
			ta=a+Perp(Vect(p[i],p[j]));
			
			b=Frac(1,2)*(p[j]+p[k]);
			tb=b+Perp(Vect(p[j],p[k]));

			cir.c=InterPoint(a,ta,b,tb);
			cir.r=Vect(cir.c,p[i])*Vect(cir.c,p[i]);
			
			circles.insert(cir);
		}

		//cout<<circles.size()<<endl;
		return circles.size();
	}
};

//////////////////////////////////////////////////////////////////////

int main()
{
	int i=0;
	bool flag;
	int cases_cnt=-1;
	bool all_flag=true;

	{
	//Test case # 0:
	cases_cnt++;

	vector<int> var2;
	int var3[]={1, 2, 1, 2, 8};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={2, 1, 8, 9, 9};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=1)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<int> var2;
	int var3[]={0, 4, 7};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={3, 3, 3};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=0)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<int> var2;
	int var3[]={0, 10, 10, 10, 20};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={10, 0, 10, 20, 10};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=5)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<int> var2;
	int var3[]={0, 10, 11, 10, 21};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={10, 0, 11, 20, 10};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=10)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<int> var2;
	int var3[]={0, 500, 249, 250, 251, 249, 250, 251, 249, 250, 1};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={500, 0, 249, 249, 249, 250, 250, 250, 251, 251, 1};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=114)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	vector<int> var2;
	int var3[]={441, 279, 1, 224, 354, 360, 37, 204, 446, 425, 308, 359, 37, 440, 104, 199, 161, 236, 288, 214, 181, 153, 19, 181, 478, 36, 65, 36, 209, 479, 300, 29, 238, 23, 69, 327, 456, 201, 87, 230, 216, 248, 487, 248, 161, 185, 55, 453, 74, 40};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={210, 255, 487, 394, 265, 443, 351, 79, 323, 238, 40, 141, 109, 37, 439, 342, 439, 59, 54, 169, 2, 183, 188, 397, 227, 377, 474, 20, 158, 174, 200, 84, 232, 42, 384, 342, 304, 78, 100, 146, 416, 381, 11, 425, 133, 76, 284, 51, 149, 418};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	CropCircles* var0=new CropCircles;
	int var1 = var0->countCircles(var2, var4);
	delete var0;

	flag=true;
	if(var1!=19600)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	if(all_flag==false) cout << "Some Cases FAILED." << endl;
	else cout << "All cases passed." << endl;
	return 0;
}

//////////////////////////////////////////////////////////////////////

/*

Problem Statement 
     
Making a crop circle is a difficult job because it is hard to see what 
one is doing. You have found a farm with boulders scattered around, 
and have realised that it would be easiest to use a circle that passes 
through three or more of the boulders. You have started wondering how 
many different circles you could produce in this way. Given vector 
<int> x and vector <int> y, return the number of distinct circles that 
can be made. The boulders are at (x[0], y[0]), (x[1], y[1]), etc. 
Definition 
     
Class: 
CropCircles 
Method: 
countCircles 
Parameters: 
vector <int>, vector <int> 
Returns: 
int 
Method signature: 
int countCircles(vector <int> x, vector <int> y) 
(be sure your method is public) 
     

Notes 
- 
The field is large enough that a circle can be made through any three 
boulders that do not lie in a straight line. 
- 
When four or more boulders lie on the same circle, this circle should 
still only be counted once. 
Constraints 
- 
x and y will each contain between 1 and 50 elements, inclusive. 
- 
x and y will contain the same number of elements. 
- 
Each element of x and y will be between 0 and 500, inclusive. 
- 
No two boulders will be in the same location. 
Examples 
0) 

     
{1, 2, 1, 2, 8} 
{2, 1, 8, 9, 9} 
Returns: 1 
The five points all lie on a common circle. 
1) 

     
{0, 4, 7} 
{3, 3, 3} 
Returns: 0 
The three points lie on a single line, so there is no circle that 
passes through them. 
2) 

     
{0, 10, 10, 10, 20} 
{10, 0, 10, 20, 10} 
Returns: 5 

3) 

     
{0, 10, 11, 10, 21} 
{10, 0, 11, 20, 10} 
Returns: 10 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
