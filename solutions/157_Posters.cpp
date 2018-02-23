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

struct Pic
{
	int w,h;
	int Area() {return w*h;}
};

int w,h;

int n;
Pic pic[5];

struct Pos
{
	int x,y;
};

Pos pos[5];

int perm[5];

int Area(int n)
{
	int i, j;
	int area=0;

	// Inclusion exclusion:
	// Sum of Areas of rectangles
	//  - Sum of binary intersections
	//  + Sum of ternary intersections ... etc

	for(i=1;i<(1<<n);i++)
	{
		int xst=0, yst=0, xen=w, yen=h; // Intersection of these rectangles
		int num=0;

		for(j=0;j<n;j++)
		{
			if(!(i&(1<<j))) continue;

			int ind=perm[j];
			
			int nxst=pos[ind].x; if(nxst>xst) xst=nxst;
			int nyst=pos[ind].y; if(nyst>yst) yst=nyst;
			int nxen=pos[ind].x+pic[ind].w; if(nxen<xen) xen=nxen;
			int nyen=pos[ind].y+pic[ind].h; if(nyen<yen) yen=nyen;
			num++;
		}

		int sign=1; if(num%2==0) sign=-1;
		
		if(xen>xst && yen>yst)
			area+=sign*(xen-xst)*(yen-yst);
	}

	return area;
}

int best_area;

int max_area;

void Go(int ord, vector<int> cx, vector<int> cy)
{
	if(best_area==max_area)
		return;

	int ind=perm[ord];

	if(ord==n)
	{
		int area=Area(n);
		if(area>best_area) best_area=area;
		return;
	}

	if(ord==0)
	{
		pos[ind].x=0; pos[ind].y=0;
		cx.push_back(pic[ind].w); cy.push_back(pic[ind].h);
		Go(ord+1, cx, cy);
		cx.pop_back(); cy.pop_back();
		return;
	}

	if(ord==1)
	{
		pos[ind].x=w-pic[ind].w; pos[ind].y=h-pic[ind].h;
		cx.push_back(-pos[ind].x); cy.push_back(-pos[ind].y);
		Go(ord+1, cx, cy);
		cx.pop_back(); cy.pop_back();
		return;
	}

	int i,j;

	// Check if there is hope to get bigger area

	int max_rem_area=0;
	for(i=ord;i<n;i++) max_rem_area+=pic[perm[i]].Area();

	if(Area(ord)+max_rem_area<=best_area)
		return;

	int cxs=cx.size(), cys=cy.size();
	int x,y,pw=pic[ind].w,ph=pic[ind].h;

	cx.push_back(0); cy.push_back(0);

	for(i=0;i<cxs;i++) for(j=0;j<cys;j++)
	{
		x=cx[i]; y=cy[j];

		int nx,ny;
		nx=x+pw;
		ny=y+ph;

		cx[cxs]=nx;
		cy[cys]=ny;
		
		bool valid=true;

		if(x<0)	{x=-x; nx=-nx;}
		
		if(x<nx)
		{
			if(nx>w) valid=false; // take care, this case is not important Because global
			pos[ind].x=x;			// corners exist (hmmm may be false)
		}
		else
		{
			if(nx<0) valid=false;
			pos[ind].x=nx;
		}

		if(y<0)
		{
			y=-y; ny=-ny;
		}

		if(y<ny)
		{
			if(ny>h) valid=false;
			pos[ind].y=y;
		}
		else
		{
			if(ny<0) valid=false;
			pos[ind].y=ny;
		}

		if(valid) Go(ord+1,cx,cy);
	}

	cx.pop_back(); cy.pop_back();
}

int Compute()
{
	int i;
	for(i=0;i<n;i++) perm[i]=i;

	max_area=0;
	for(i=0;i<n;i++) max_area+=pic[i].Area();

	best_area=0;

	if(n<=2)
	{
		vector<int> cx, cy;
		cx.push_back(0); cx.push_back(-w); // -ve means we can put on left, +ve on right
		cy.push_back(0); cy.push_back(-h);
		Go(0, cx, cy);
	}
	else
	{
		do
		{
			if(perm[0]<perm[1]) // there is some symmetry here
			{
				vector<int> cx, cy;
				cx.push_back(0); cx.push_back(-w);
				cy.push_back(0); cy.push_back(-h);

				Go(0, cx, cy);

				if(best_area==max_area)
					break;
			}
		}
		while(next_permutation(perm, perm+n));
	}

	return best_area;
}

class Posters
{
public:
	int maxCover(int width, int height, vector<int> pWidth, vector<int> pHeight)
	{
		n=pHeight.size();
		w=width; h=height;

		int i;
		for(i=0;i<n;i++)
		{
			pos[i].x=0; pos[i].y=0;
			pic[i].w=pWidth[i];
			pic[i].h=pHeight[i];
		}

		int val=Compute();
		//cout<<n<<" "<<val<<endl;
		return val;
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
	int var3[]={7,4,1,8};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={3,5,3,4};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(10, 10, var2, var4);

	flag=true;
	if(var1!=74)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<int> var2;
	int var3[]={64,51};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={42,51};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(90, 80, var2, var4);

	flag=true;
	if(var1!=4964)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<int> var2;
	int var3[]={6,6,2,4,2};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={2,2,4,2,4};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(8, 6, var2, var4);

	flag=true;
	if(var1!=48)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<int> var2;
	int var3[]={68,50,18,52,62};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={27,15,37,45,50};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(100, 93, var2, var4);

	flag=true;
	if(var1!=8256)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<int> var2;
	int var3[]={1,2,4,8,16};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={1,2,4,8,16};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(19, 20, var2, var4);

	flag=true;
	if(var1!=321)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	vector<int> var2;
	int var3[]={35};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={25};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(40, 30, var2, var4);

	flag=true;
	if(var1!=875)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 6:
	cases_cnt++;

	vector<int> var2;
	int var3[]={49, 49, 48, 48, 50};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={49, 48, 49, 48, 50};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	Posters var0;
	int var1 = var0.maxCover(100, 100, var2, var4);

	flag=true;
	if(var1!=9884)
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
     
Yarin likes to decorate his walls with posters. Lately, he has had 
some trouble deciding where on the wall to put the posters so the 
total area of the wall that is covered with posters is maximized. The 
posters can of course not be cut into pieces, nor rotated, nor placed 
so they don't fit completely on the wall. They may overlap however 
(see example 0). 
Create a class Posters containing the method maxCover which takes as 
input an int width and an int height, the width and height of the 
wall, and a vector <int> pWidth and a vector <int> pHeight, the width 
and height of each poster. Elements i in pWidth and pHeight are the 
width and height, respectively, of poster i. The method should return 
an int, the maximum area of the wall that can be covered with posters. 
Definition 
     
Class: 
Posters 
Method: 
maxCover 
Parameters: 
int, int, vector <int>, vector <int> 
Returns: 
int 
Method signature: 
int maxCover(int width, int height, vector <int> pWidth, vector <int> 
pHeight) 
(be sure your method is public) 
     

Constraints 
- 
width will be between 1 and 100, inclusive. 
- 
height will be between 1 and 100, inclusive. 
- 
pWidth will contain between 1 and 5 elements, inclusive. 
- 
pHeight will contain between 1 and 5 elements, inclusive. 
- 
pWidth and pHeight will contain the same number of elements. 
- 
Each element in pWidth will be between 1 and width, inclusive. 
- 
Each element in pHeight will be between 1 and height, inclusive. 
Examples 
0) 

     
10 
10 
{7,4,1,8} 
{3,5,3,4} 
Returns: 74 
The posters can be placed like this: 
AAAAAAA... 
AAAAAAABBB 
AAAAAAABBB 
......BBBB 
......BBBB 
......BBBB 
DDDDDDDD.. 
DDDDDDDD.C 
DDDDDDDD.C 
DDDDDDDD.C 
1) 

     
90 
80 
{64,51} 
{42,51} 
Returns: 4964 
With only two posters, the optimal result is always reached by putting 
the posters in opposite corners of the wall. 
2) 

     
8 
6 
{6,6,2,4,2} 
{2,2,4,2,4} 
Returns: 48 
Here one poster must be surrounded by the other posters in order to 
get the best result. 
3) 

     
100 
93 
{68,50,18,52,62} 
{27,15,37,45,50} 
Returns: 8256 

4) 

     
19 
20 
{1,2,4,8,16} 
{1,2,4,8,16} 
Returns: 321 

5) 

     
40 
30 
{35} 
{25} 
Returns: 875 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
