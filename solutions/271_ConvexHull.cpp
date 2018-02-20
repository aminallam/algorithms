#pragma warning(disable:4786)
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
using namespace std;
int cases_cnt;

/*
Problem Statement 
     
You have a rectangle with corners at (0, 0) and (m, n). You would like to place a convex 
polygon inside it such that the polygon's vertices are at integer coordinates. The 
vertices may lie anywhere inside the rectangle or on its boundary. You are given m and n, 
the dimensions of the rectangle. Return the maximal number of vertices contained by the 
convex polygon. 
----------------------------------------------------------
Constraints 
- 
m and n will be between 3 and 200, inclusive. 
*/

typedef long long LL;
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <complex>
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

struct Point{
	int x, y;
	Point() {}
	Point(int _x, int _y) {x=_x; y=_y;}
};

int max(int a,int b){if(a>b)return a;return b;}
int gcd(int a, int b) {if(b==0)return a; return gcd(b,a%b);}

class ConvexHull
{
public:
	int a[201][201]; // Best polyline in rect i,j
	int b[201][201];

	int intHull(int m, int n)
	{
		int i,j,k;
		int dim=m; if(n>dim) dim=n;
		
		// dps will contain the shift in x,y from a vertex to another
		vector<Point> dps;
		dps.push_back(Point(0,1)); // Take care we will not allow (1,0) as this will make problems on edges
									// Also, this will cause a[x][y]!=a[y][x]
		for(i=1;i<=25;i++) for(j=1;j<=i;j++) if(gcd(i,j)==1){
			dps.push_back(Point(i,j));
			if(i!=j) dps.push_back(Point(j,i));
		}

		int ndps=dps.size();

		// Sort the vectors according to their slope
		// We do not need it because we will use each just once, we can assume they will be sorted later on
		for(j=0;j<ndps;j++) for(i=0;i<j;i++) if(dps[i].x*dps[j].y>dps[j].x*dps[i].y) swap(dps[i],dps[j]);

		// Compute the best lengths of paths that use our vectors

		memset(a,0,sizeof(a));

		for(k=0;k<ndps;k++) for(i=dim;i>=0;i--) for(j=dim;j>=0;j--) // Reverse order to be sure we will use it once
		{
			if(i<dps[k].x || j<dps[k].y) continue;
			int q=a[i-dps[k].x][j-dps[k].y]+1;
			if(q>a[i][j]) a[i][j]=q;
		}

		for(i=1;i<=dim;i++) for(j=1;j<=dim;j++)
		{
			// Either we already have the optimal solution,
			// or we get it by extending some other optimal solution
			if(a[i-1][j]>a[i][j]) a[i][j]=a[i-1][j];
			if(a[i][j-1]>a[i][j]) a[i][j]=a[i][j-1];
		}

		memset(b,0,sizeof(b));

		// Get best two polylines from i to k and from k to j

		for(i=0;i<=m;i++) for(j=0;j<=m;j++) for(k=0;k<=n;k++) b[i][j]=max(b[i][j],a[i][k]+a[n-k][j]);

		// Get full convex polygon

		int val=0;
		for(i=0;i<=m;i++) for(j=0;j<=m;j++) val=max(val,b[i][j]+b[m-j][m-i]);

		//cout<<val<<endl;
		return val;
	}
};

/*
Examples 
----------------------------------------------------------
0) 
     
3 
3 
Returns: 8 

----------------------------------------------------------
1) 
     
3 
50 
Returns: 8 
----------------------------------------------------------
2) 
     
4 
4 
Returns: 9 
----------------------------------------------------------
3) 
     
4 
5 
Returns: 10 

----------------------------------------------------------
4) 
     
50 
200 
Returns: 74 
*/

void AdditionalTests()
{
}

int TestIsEqual(double a, double b){
	if(a>-1e300 && b>-1e300 && a<1e300 && b<1e300 && fabs(a-b)<1e-5) return 1; return 0;
}

int main()
{
	int i=0;
	bool flag;
	cout.setf(ios::fixed|ios::showpoint);
	cout.precision(5);
	cases_cnt=-1;
	bool all_flag=true;
	int time=clock();

	{
	//Test case # 0:
	cases_cnt++;

	ConvexHull* var0=new ConvexHull;
	int var1 = var0->intHull(3, 3);
	delete var0;

	flag=true;
	if(var1!=8)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	ConvexHull* var0=new ConvexHull;
	int var1 = var0->intHull(3, 50);
	delete var0;

	flag=true;
	if(var1!=8)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	ConvexHull* var0=new ConvexHull;
	int var1 = var0->intHull(4, 4);
	delete var0;

	flag=true;
	if(var1!=9)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	ConvexHull* var0=new ConvexHull;
	int var1 = var0->intHull(4, 5);
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

	ConvexHull* var0=new ConvexHull;
	int var1 = var0->intHull(50, 200);
	delete var0;

	flag=true;
	if(var1!=74)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	cout << "Time=" << (clock()-time) << endl;
	if(all_flag==false) cout << "Some Cases FAILED." << endl;
	else cout << "All cases passed." << endl;

	AdditionalTests();

	return 0;
}

//////////////////////////////////////////////////////////////////////

