#pragma warning(disable:4786)
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

int cases_cnt;
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

class BoxUnion
{
public:
	enum{MAX_RECTS=3, MAX_Y=20000+1};
	enum{RECT_START, RECT_END};

	int n;
	int x1[MAX_RECTS], x2[MAX_RECTS], y1[MAX_RECTS], y2[MAX_RECTS];

	// Event occurs when a seep line meets the left or right edge of a rectangle
	struct Event
	{
		int x, y1, y2, type;
		bool operator<(const Event& ev)const{return x<ev.x;}
	};

	int Sweep()
	{
		// Active set[y]=number of rectangles containing this y
		int active_set[MAX_Y];
		memset(active_set, 0, sizeof(active_set));

		int i,y;
		vector<Event> events;

		for(i=0;i<n;i++)
		{
			Event rec_start; rec_start.type=RECT_START;
			rec_start.x=x1[i]; rec_start.y1=y1[i]; rec_start.y2=y2[i];

			Event rec_end; rec_end.type=RECT_END;
			rec_end.x=x2[i]; rec_end.y1=y1[i]; rec_end.y2=y2[i];

			events.push_back(rec_start);
			events.push_back(rec_end);
		}

		sort(events.begin(), events.end());

		// Move sweep line on x values of events

		int area=0, prev_x=-1;

		for(i=0;i<events.size();i++)
		{
			Event ev=events[i];

			// Add area before x

			int cur_area=0;
			for(y=0;y<MAX_Y;y++) if(active_set[y]>0) cur_area++;

			if(prev_x!=-1) area+=(ev.x-prev_x)*cur_area;

			prev_x=ev.x;

			for(y=ev.y1;y<ev.y2;y++)
			{
				if(ev.type==RECT_START) active_set[y]++;
				else active_set[y]--;
			}
		}

		return area;
	}

	int area(vector<string> rectangles)
	{
		int i;
		n=rectangles.size();

		for(i=0;i<n;i++)
		{
			istringstream istr(rectangles[i]);
			istr>>x1[i]>>y1[i]>>x2[i]>>y2[i];
		}

		int val=Sweep();
		//cout<<val<<endl;
		return val;
	}
};

//////////////////////////////////////////////////////////////////////

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

	{
	//Test case # 0:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"200 300 203 304" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=12)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"0 0 10 10",
  "20 20 30 30" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=200)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"0 500 20000 501",
  "500 0 501 20000" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=39999)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"4 6 18 24",
  "7 2 12 19",
  "0 0 100 100" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=10000)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"1 3 5 6",
  "3 1 7 5",
  "4 4 9 7" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=35)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"0 0 20000 20000",
  "0 0 20000 20000",
  "0 0 20000 20000" };
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	BoxUnion* var0=new BoxUnion;
	int var1 = var0->area(var2);
	delete var0;

	flag=true;
	if(var1!=400000000)
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
     
NOTE: This problem statement contains an image that may not display 
properly if viewed outside of the applet. 
Given a list of two-dimensional rectangles, compute the area of their 
union. For example, the union of the three rectangles shown in the 
figure below: 

cover an area of 35 units. 
The list of rectangles will be given as a vector <string>, where each 
element describes one rectangle. Each string will be formatted as 4 
space-separated integers with no leading zeros, giving the coordinates 
of the left, bottom, right, and top of the rectangle (in that order). 
The three rectangles shown above would be given as: 
{ "1 3 5 6", 
"3 1 7 5", 
"4 4 9 7" } 
Definition 
     
Class: 
BoxUnion 
Method: 
area 
Parameters: 
vector <string> 
Returns: 
int 
Method signature: 
int area(vector <string> rectangles) 
(be sure your method is public) 
     

Constraints 
- 
rectangles will contain between 1 and 3 elements, inclusive. 
- 
Each element of rectangles will be formatted as described in the 
problem statement. 
- 
For each rectangle, the left coordinate will be less than the right 
coordinate and the bottom coordinate will be less than the top 
coordinate. 
- 
All coordinates will be between 0 and 20000, inclusive. 
Examples 
0) 

     
{ "200 300 203 304" } 
Returns: 12 
A single rectangle with area 12. 
1) 

     
{ "0 0 10 10", 
"20 20 30 30" } 
Returns: 200 
Two disjoint rectangles, each of area 100. 
2) 

     
{ "0 500 20000 501", 
"500 0 501 20000" } 
Returns: 39999 
These two rectangles intersect at a single point. 
3) 

     
{ "4 6 18 24", 
"7 2 12 19", 
"0 0 100 100" } 
Returns: 10000 
The third rectangle completely overlaps the first two. 
4) 

     
{ "1 3 5 6", 
"3 1 7 5", 
"4 4 9 7" } 
Returns: 35 
This is the example from the problem statement. 
5) 

     
{ "0 0 20000 20000", 
"0 0 20000 20000", 
"0 0 20000 20000" } 
Returns: 400000000 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
