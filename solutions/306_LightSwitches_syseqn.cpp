#pragma warning(disable:4786)
#include <iostream>
#include <cmath>
#define EPS (1e-12)
int dcomp(double a, double b) {if (fabs(a-b)<EPS) return 0; return (a>b)?1:-1;}
typedef __int64 LL;
int cases_cnt;

//typedef int LL;
//typedef long long LL;
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef vector<double> vd;
typedef vector<vd> vvd;

//a=n*(n+1) a[i]=ith equation, x[i]=sol of ith var (output), (a[i][n+1]=RHS of eqn i)
int SolveEquations(vvd& a, vd& x, bool bin=false) { 
	int i,j,k,last=0;
	int m=a[0].size()-1;
	int n=a.size();
	double t;
	for (j=0; j<m; j++) {	// eleminate this column
		for (i=last; i<n; i++) if (a[i][j]) {swap(a[last], a[i]);goto yes;}
		continue; yes:;
		for (i=last+1; i<n; i++) if (a[i][j]) {	//a[i] ^= a[last];
			t=a[i][j]/a[last][j];
			for(k=0;k<=m;k++) {a[i][k]-=a[last][k]*t; if(bin && a[i][k]<0) a[i][k]+=2;}
		}
		last++;
	}
	for(i=0;i<n;i++) if(a[i][i]) x[i]=a[i][m]/a[i][i];
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){if(a[i][j]!=0) goto good_row;}
		break; good_row:;
	}			// Note that all zero rows will be at end of matrix
	return i;	// return rank (# of non-zero rows)
}

class LightSwitches
{
public:
	LL countPossibleConfigurations(vector<string> sw)
	{
		int n=sw.size(), m=sw[0].size();

		vvd a(n, vd(m+1, 0));
		vd x(n);

		int i,j;
		for(i=0;i<n;i++) for(j=0;j<m;j++) if(sw[i][j]=='Y') a[i][j]=1;

		int res=SolveEquations(a, x, true);

		//cout << endl;
		//for(i=0;i<n;i++) {for(j=0;j<m;j++) cout << a[i][j]; cout << endl;} 
		//cout << endl;

		//int res=0;

		return (1i64<<res);
		//return (1ll<<res);
	}
};

//////////////////////////////////////////////////////////////////////

int main()
{
	int i; i=0;
	bool flag;
	cases_cnt=-1;

	{
	//Test case # 0:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"YYN",
 "NNY",
 "YYY",
 "NNN"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	LightSwitches var0;
	LL var1 = var0.countPossibleConfigurations(var2);

	flag=true;
	if (var1!=4)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 0 << endl; return 0;}
	else cout << "Test Case Succeeded " << 0 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"NNNNYYYNYYNYYYYYNYY"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	LightSwitches var0;
	LL var1 = var0.countPossibleConfigurations(var2);

	flag=true;
	if (var1!=2)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 1 << endl; return 0;}
	else cout << "Test Case Succeeded " << 1 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"NYNYNYN",
 "YNYNYNY",
 "YYNNNYN",
 "NNNYNYN",
 "YYYYYNN",
 "YNNNNYN"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	LightSwitches var0;
	LL var1 = var0.countPossibleConfigurations(var2);

	flag=true;
	if (var1!=32)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 2 << endl; return 0;}
	else cout << "Test Case Succeeded " << 2 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"YNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNN"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	LightSwitches var0;
	LL var1 = var0.countPossibleConfigurations(var2);

	flag=true;
	if (var1!=1073741824)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 3 << endl; return 0;}
	else cout << "Test Case Succeeded " << 3 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"NNNNNNNNNYNNNNNNNYNNNNNNNNNN",
				   "NNNNNNNNNYNNNNNNNNYNNNNNNNNN",
				   "NNNNNNNNNNNNNNNNNYYNNNNNNNNN"
	};
	
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	LightSwitches var0;
	LL var1 = var0.countPossibleConfigurations(var2);

	flag=true;
	if (var1!=4)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 4 << endl; return 0;}
	else cout << "Test Case Succeeded " << 4 << endl;
	}

	///////////////////////////////////////////////////////

	cout << "All cases passed." << endl;
	return 0;
}

//Failed system test 6 on the 500-point problem with args: 
//[{"NNNNNNNNNYNNNNNNNYNNNNNNNNNN", "NNNNNNNNNYNNNNNNNNYNNNNNNNNN", "NNNNNNNNNNNNNNNNNYYNNNNNNNNN"}]
  //  EXPECTED: 4
    //RECEIVED: 8
			  
//////////////////////////////////////////////////////////////////////

/*

Problem Statement 
     
In a ballroom, there are some light bulbs and some switches that 
control those bulbs. However, the switches and the bulbs are not 
related in a logical way. Each switch is connected to a subset of the 
bulbs, and when a switch is flipped, all the bulbs connected to that 
switch change state (the ones that were off are turned on, and the 
ones that were on are turned off). Bulbs that are not connected to the 
flipped switch remain as they were. 
The states of all the bulbs in the room can be described as a 
configuration of lights. If there are N bulbs, there are 2N possible 
configurations. Two configurations are distinct if a bulb in one 
configuration has a different state than that same bulb in the other 
configuration. 
You will be given the connections between the switches and bulbs as a 
vector <string> switches. The jth character of the ith element of 
switches is 'Y' if the ith switch is connected to the jth bulb, and 
'N' otherwise. All the bulbs are initially off. Return the number of 
distinct configurations of lights that can be achieved using this 
setup. 
Definition 
     
Class: 
LightSwitches 
Method: 
countPossibleConfigurations 
Parameters: 
vector <string> 
Returns: 
long long 
Method signature: 
long long countPossibleConfigurations(vector <string> switches) 
(be sure your method is public) 
     

Constraints 
- 
switches will have between 1 and 50 elements, inclusive. 
- 
Each element of switches will have exactly N characters, where N is 
between 1 and 50, inclusive. 
- 
Each character of each element of switches will be 'Y' or 'N'. 
Examples 
0) 

     
{"YYN", 
"NNY", 
"YYY", 
"NNN"} 
Returns: 4 
In this example, there are three bulbs and four switches. The first 
switch is connected to the first two lights, the second switch is 
connected to the third light, the third switch is connected to all 
three lights, and the fourth switch is connected to nothing. 
The possible configurations are (- for OFF and + for ON): - - - The 
initial configuration. + + - This can be achieved by flipping the 
first switch. - - + This can be achieved by flipping the second 
switch. + + + This can be achieved by flipping the first switch and 
then the second switch. 
1) 

     
{"NNNNYYYNYYNYYYYYNYY"} 
Returns: 2 
There are only two possible configurations here - the initial 
configuration where all the bulbs are off, and the configuration that 
results from flipping the switch once. 
2) 

     
{"NYNYNYN", 
"YNYNYNY", 
"YYNNNYN", 
"NNNYNYN", 
"YYYYYNN", 
"YNNNNYN"} 
Returns: 32 

3) 

     
{"YNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNN", 
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNN"} 
Returns: 1073741824 
Each of the first 30 bulbs can be turned on and off individually while 
the remaining 20 bulbs are impossible to turn on. Any combination of 
states among the first 30 bulbs is possible, so the number of 
configurations is 230. 
This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
