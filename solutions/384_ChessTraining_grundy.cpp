#pragma warning(disable:4786)
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace std;

#define TEST_EPS (1e-9)
int dcomp(double a, double b) {if(fabs(a-b)<TEST_EPS) return 0; return (a>b)?1:-1;}

typedef __int64 LL;
ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
istream& operator>>(istream& in,LL& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

//////////////////////////////////////////////////////////////////////
//typedef long long LL;
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

class ChessTraining
{
public:

	bool win(int a,int b) // the < part is useful to avoid going out the board
	{
		return (a<=0 || b<=0 || a==b);
	}

	int g[100][100];

	string game(vector<int> x, vector<int> y)
	{
		// We need to set Grundy=0 for losing moves, not winning moves
		//  So, we ignore direct winning moves in our computations,
		//   and set all direct losing moves to 0, and take care that
		//   we will not try to go to the direct winning moves at all (as we will lose)

		memset(g,0,sizeof(g));

		int i,j,k;
		int n=x.size();

		for(i=0;i<100;i++) for(j=0;j<100;j++) if(!win(i,j))
		{
			int f[200]={0};
			
			for(k=1;k<200;k++)
			{
				if(!win(i-k,j)) f[g[i-k][j]]++;
				if(!win(i,j-k)) f[g[i][j-k]]++;
				if(!win(i-k,j-k)) f[g[i-k][j-k]]++;
			}

			for(k=0;k<200;k++) if(!f[k]) {g[i][j]=k;break;}
		}

		// Handle direct winning moves separately
		for(i=0;i<n;i++) if(win(x[i],y[i])) return "Alice will win";

		int res=0;
		for(i=0;i<n;i++) res^=g[x[i]][y[i]];
		
		if(res!=0) return "Alice will win";
		return "Bob will win";
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

	vector<int> var2;
	int var3[]={3,4};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={3,5};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Alice will win")
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<int> var2;
	int var3[]={1};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={2};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Bob will win")
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<int> var2;
	int var3[]={5,7,3,5};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={8,3,7,8};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Bob will win")
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<int> var2;
	int var3[]={3,3,18,6,0,14,1};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={4,4,11,9,9,9,9};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Alice will win")
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<int> var2;
	int var3[]={1,2};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={3,3};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Alice will win")
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 5:
	cases_cnt++;

	vector<int> var2;
	int var3[]={3,4,3};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	vector<int> var4;
	int var5[]={2,2,1};
	for (i=0; i<sizeof(var5)/sizeof(var5[0]); i++)
		var4.push_back(var5[i]);

	ChessTraining* var0=new ChessTraining;
	string var1 = var0->game(var2, var4);
	delete var0;

	flag=true;
	if(var1!="Bob will win")
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
     
Alice and Bob are hobby chess players. They would like to become the 
best in the world so they are training a lot. Today they are going to 
play the following game with queens on a 100 x 100 chessboard to 
improve their offensive skills. In each turn a player must choose one 
queen and move with it. From position (x, y) a queen can be moved to 
(x - k, y) or (x, y - k) or (x - k, y - k), where k > 0. (Queens can 
move through squares containing other queens, and multiple queens can 
coexist on a single square). The two players alternate turns, and 
Alice goes first. The first player who moves any queen to the position 
(0,0) will become the winner. You are given the initial positions of 
the queens in the vector <int>s x and y, where (x[i], y[i]) is the 
position of the i-th queen. Suppose Alice and Bob are playing 
optimally. Return "Alice will win" if Alice can win or "Bob will win" 
otherwise (all quotes for clarity). 
Definition 
     
Class: 
ChessTraining 
Method: 
game 
Parameters: 
vector <int>, vector <int> 
Returns: 
string 
Method signature: 
string game(vector <int> x, vector <int> y) 
(be sure your method is public) 
     

Constraints 
- 
x will contain between 1 and 50 elements, inclusive. 
- 
y will contain the same number of elements as x. 
- 
Each element of x and y will be between 0 and 99, inclusive. 
- 
No queen will be at position (0,0) at the beginning. 
Examples 
0) 

     
{3,4} 
{3,5} 
Returns: "Alice will win" 
Alice can move a queen from (3,3) to (0,0) to win in her first move. 
1) 

     
{1} 
{2} 
Returns: "Bob will win" 
No matter how Alice moves the queen, Bob can win in the next move. 
2) 

     
{5,7,3,5} 
{8,3,7,8} 
Returns: "Bob will win" 

3) 

     
{3,3,18,6,0,14,1} 
{4,4,11,9,9,9,9} 
Returns: "Alice will win" 

4) 

     
{1,2} 
{3,3} 
Returns: "Alice will win" 

5) 

     
{3,4,3} 
{2,2,1} 
Returns: "Bob will win" 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
