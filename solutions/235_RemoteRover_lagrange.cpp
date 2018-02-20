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

double PI() {return atan(1)*4;}

class RemoteRover
{
public:

	// Apply lagrange multipliers, where the variables are the angles
	//	between every two levels.

	double optimalTravel(vector<int> width, vector<int> speed, int offset)
	{
		int i,n=width.size(),cnt=0;

		// Search on first theta itself causes precision errors
		// So, Make binary search on cos(first theta)
		// This is better than sorting (see below) to avoid precision errors

		double lo=cos(PI()/2), hi=cos(0);
		
		while(lo<hi && cnt++<100)
		{
			double mid=(lo+hi)/2;
			double lamda=mid/speed[0];

			double val=0;
			for(i=0;i<n;i++)
			{
				double cos_theta=lamda*speed[i];
				double sin_theta=sqrt(1-cos_theta*cos_theta);

				if(cos_theta>1) {val=1e300; break;}

				val+=width[i]*cos_theta/sin_theta;
			}

			if(val>offset) hi=mid;
			else lo=mid;
		}

		double lamda=((lo+hi)/2)/speed[0];

		double val=0;
		for(i=0;i<n;i++)
		{
			double cos_theta=lamda*speed[i];
			double sin_theta=sqrt(1-cos_theta*cos_theta);

			val+=width[i]/(speed[i]*sin_theta);
		}

		//cout<<val<<endl;
		return val;
	}
};

/*
// Looks correct but numerically un-stable (Case 5 fails by small margin)

	// This sorting will avoid precision errors!

	for(i=0;i<n;i++) for(j=i+1;j<n;j++)
	{
		if(width[j]<width[i])
		{
			swap(width[i], width[j]);
			swap(speed[i], speed[j]);
		}
	}

	double optimalTravel(vector<int> width, vector<int> speed, int offset)
	{
		int i,n=width.size(),cnt=0;

		// Make binary search on the first theta

		double lo=0, hi=PI()/2;
		
		while(lo<hi && cnt++<1000) // 100 is not good
		{
			double mid=(lo+hi)/2;
			double lamda=cos(mid)/speed[0];

			double val=0;
			for(i=0;i<n;i++)
			{
				double cos_theta=lamda*speed[i];
				double sin_theta=sqrt(1-cos_theta*cos_theta);

				val+=width[i]*cos_theta/sin_theta;
			}

			if(val<offset) hi=mid;
			else lo=mid;
		}

		double lamda=cos((lo+hi)/2)/speed[0];

		double val=0;
		for(i=0;i<n;i++)
		{
			double cos_theta=lamda*speed[i];
			double sin_theta=sqrt(1-cos_theta*cos_theta);

			val+=width[i]/(speed[i]*sin_theta);
		}

		cout<<val<<endl;
		return val;
	}

	double optimalTravel(vector<int> width, vector<int> speed, int offset)
	{
		int i,n=width.size(),cnt=0;

		// Make binary search on the first theta

		double lo=0, hi=PI()/2;
		
		while(lo<hi && cnt++<1000) // 100 is not good
		{
			double mid=lo+(hi-lo)/2;

			double lamda=cos(mid)/speed[0];

			double val=0;
			for(i=0;i<n;i++) val+=width[i]/tan(acos(lamda*speed[i]));

			if(val<offset) hi=mid;
			else lo=mid;
		}

		double lamda=cos((lo+hi)/2)/speed[0];

		double val=0;
		for(i=0;i<n;i++) val+=width[i]/(speed[i]*sin(acos(lamda*speed[i])));

		cout<<val<<endl;
		return val;
	}
*/
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

	vector<int> var2;
	int var3[]={100, 300, 200};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={100, 50, 75};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 1000);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,17.042083785318038))
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<int> var2;
	int var3[]={1155, 6184, 2783, 7540, 8156};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={570, 810, 875, 172, 642};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 0);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,69.38271426584203))
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<int> var2;
	int var3[]={5000};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={50};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 10000);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,223.60679774997894))
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<int> var2;
	int var3[]={9033, 8232, 8842, 6518, 2358, 1115, 941, 928, 220, 8460};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 10000);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,954.1368054948935))
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<int> var2;
	int var3[]={9236, 7065, 2283, 506, 6432, 9812, 3133, 1397, 7052, 3729,
2556, 9954, 1367, 6440, 5141, 3091, 2879, 1346, 7080, 1036,
7503, 7775, 433, 7579, 6520, 2287, 1971, 3879, 1725, 8200,
1830, 2774, 3850, 7509, 8531, 7493, 1511, 9399, 9679, 2124,
791, 3432};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={956, 799, 481, 194, 993, 444, 571, 986, 815, 910,
98, 847, 650, 487, 419, 434, 410, 812, 374, 751,
307, 134, 134, 955, 758, 73, 932, 360, 135, 588,
218, 936, 674, 494, 157, 556, 881, 292, 851, 890,
886, 912};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 9756);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,501.6129192127166))
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	vector<int> var2;
	int var3[]={10000, 1};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={1, 1000};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	RemoteRover* var0=new RemoteRover;
	double var1 = var0->optimalTravel(var2, var4, 10000);
	delete var0;

	flag=true;
	if(!TestIsEqual(var1,10009.994999966919))
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
     
This problem statement contains an image. 
You are responsible for planning the operation of a remote control 
rover that is exploring a distant planet. Your team of scientists has 
identified a target of interest, and they want the rover to reach it 
as soon as possible. The rover can change directions in a negligible 
amount of time, but its maximum speed is dependent on the terrain it 
is traversing. Consider a rectangle with the rover's initial position 
and the target at opposite corners (the target is close enough that 
the curvature of the planet's surface can be neglected), as displayed 
in the example below. The rectangle is divided into parallel strips of 
terrain with different widths, and each strip has its own limit on the 
maximum speed of the rover. Your goal is to find the route that will 
minimize the travel time to the target. 
Example 0: The rover starts in the lower left corner and the target is 
in the upper right. Covering more horizontal distance in the thin 
strip where the maximum speed is high yields a shorter total travel 
time compared to the shortest-path time. 
Write a class RemoteRover with a method optimalTravel that takes a 
vector <int> width containing the widths of each strip, a vector <int> 
speed containing the maximum speeds of the rover in each strip, and an 
int offset that is the distance parallel to the strips the target is 
offset from the rover's initial position, and returns the minimum 
amount of time it will take for the rover to reach the target. 
Definition 
     
Class: 
RemoteRover 
Method: 
optimalTravel 
Parameters: 
vector <int>, vector <int>, int 
Returns: 
double 
Method signature: 
double optimalTravel(vector <int> width, vector <int> speed, int 
offset) 
(be sure your method is public) 
     

Notes 
- 
A return value with either an absolute or relative error of less than 
1e-9 is considered correct. 
Constraints 
- 
width will contain between 1 and 50 elements, inclusive. 
- 
speed will contain between 1 and 50 elements, inclusive. 
- 
width and speed will contain the same number of elements. 
- 
Each element of width will be between 1 and 10000, inclusive. 
- 
Each element of speed will be between 1 and 1000, inclusive. 
- 
offset will be between 0 and 10000, inclusive. 
Examples 
0) 

     
{100, 300, 200} 
{100, 50, 75} 
1000 
Returns: 17.042083785318038 
The example from the problem statement. 
1) 

     
{1155, 6184, 2783, 7540, 8156} 
{570, 810, 875, 172, 642} 
0 
Returns: 69.38271426584203 
An offset of 0 means the target is directly across the strips from the 
initial position, so there is no reason to deviate from a straight 
path. 
2) 

     
{5000} 
{50} 
10000 
Returns: 223.60679774997894 
The shortest and quickest path here is a straight line to the target. 
3) 

     
{9033, 8232, 8842, 6518, 2358, 1115, 941, 928, 220, 8460} 
{50, 50, 50, 50, 50, 50, 50, 50, 50, 50} 
10000 
Returns: 954.1368054948935 
The speed limits in each of the strips are identical, so they might as 
well be a single wide strip. 
4) 

     
{9236, 7065, 2283, 506, 6432, 9812, 3133, 1397, 7052, 3729, 
2556, 9954, 1367, 6440, 5141, 3091, 2879, 1346, 7080, 1036, 
7503, 7775, 433, 7579, 6520, 2287, 1971, 3879, 1725, 8200, 
1830, 2774, 3850, 7509, 8531, 7493, 1511, 9399, 9679, 2124, 
791, 3432} 
{956, 799, 481, 194, 993, 444, 571, 986, 815, 910, 
98, 847, 650, 487, 419, 434, 410, 812, 374, 751, 
307, 134, 134, 955, 758, 73, 932, 360, 135, 588, 
218, 936, 674, 494, 157, 556, 881, 292, 851, 890, 
886, 912} 
9756 
Returns: 501.6129192127166 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
