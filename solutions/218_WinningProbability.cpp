#pragma warning(disable:4786)
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace std;

#define TEST_EPS (1e-3)
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

// Another fine solution by misof
// http://forums.topcoder.com/?module=Thread&threadID=619387&start=0

class WinningProbability
{
public:
	int num_games;
	int must_win;

	// Return probability that I will win the series, given:
	//	won=number of games I won, lost=number of games I lost
	//	(both won and lost not including known history)

	double Solve(int won, int lost)
	{
		if(won+lost==num_games)
			return (won>=must_win);

		// p is the probability that I will win the next game.
		
		// According to the problem statement, p is the weighted average of all possible
		//	probabilities according to the current state.

		// Let x be the probability that we win a single game, then the probability that
		//	we win exactly a out of (a+b) games is: Binomial(a+b,a,x)=nCk(a+b,a)*x^a*(1-x)^b

		// p = Integral(0,1){x*Binomial(a+b, a, x)dx} /
		//		Integral(0,1){Binomial(a+b, a, x)dx}

		// We need to integrate x^a*(1-x)^b wrt x in the interval 0->1
		//  this integration has the value: a!b!/(a+b+1)!

		// p = Integral(0,1){x^(a+1)*(1-x)^b} / Integral(0,1){x^a*(1-x)^b}
		// so: p = (a+1)/(a+b+2)

		double p=(1.0+won)/(2.0+won+lost);

		return p*Solve(won+1, lost)+(1-p)*Solve(won, lost+1);
	}

	double probability(int prevWins, int prevLosses, int gamesLeft, int mustWin)
	{
		num_games=gamesLeft+prevWins+prevLosses;
		must_win=mustWin+prevWins;

		double val=Solve(prevWins,prevLosses);
		//cout<<val<<endl;
		return val;
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

	WinningProbability* var0=new WinningProbability;
	double var1 = var0->probability(2, 0, 1, 1);
	delete var0;

	flag=true;
	if(dcomp(var1,0.75)!=0)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	WinningProbability* var0=new WinningProbability;
	double var1 = var0->probability(0, 3, 4, 4);
	delete var0;

	flag=true;
	if(dcomp(var1,0.0142857142857)!=0)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	WinningProbability* var0=new WinningProbability;
	double var1 = var0->probability(20, 3, 5, 1);
	delete var0;

	flag=true;
	if(dcomp(var1,0.9995284409077)!=0)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	WinningProbability* var0=new WinningProbability;
	double var1 = var0->probability(0, 20, 1, 1);
	delete var0;

	flag=true;
	if(dcomp(var1,0.0454545454545)!=0)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	WinningProbability* var0=new WinningProbability;
	double var1 = var0->probability(0, 0, 1, 1);
	delete var0;

	flag=true;
	if(dcomp(var1,0.5)!=0)
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
     
You favorite sports team is heading into a big playoff series against 
its big rival. They've gone head to head a number of times previously, 
and the inputs, prevWins and prevLosses, summarize the results. Now, 
there are gamesLeft games left in the series, and your team must win 
at least mustWin of them in order to win the series. You want to know 
what the probability is that they will accomplish this. To that end, 
you've come up with the following strategy. First, you will assume 
that there is some probability, p, that your team will win each game, 
and you will assume that each game is independent. For a given value 
of p, you can thus calculate the probability that your team won and 
lost as it did in the past. Now, let's say that for a given value of 
p, p1, the probability of the previous games turning out as they did 
is q1, and similarly for p2, the probability is q2. From this, you've 
decided that the true probability of your team winning a game is 
(q1/q2) times more likely to be p1 than it is to be p2. Considering 
all possible values of p, and taking into account the relative 
probabilities of each, determine the probability that your team will 
win the series. 
Definition 
     
Class: 
WinningProbability 
Method: 
probability 
Parameters: 
int, int, int, int 
Returns: 
double 
Method signature: 
double probability(int prevWins, int prevLosses, int gamesLeft, int 
mustWin) 
(be sure your method is public) 
     

Notes 
- 
Your return must have an error of less than 1e-9. 
Constraints 
- 
prevWins and prevLosses will each be between 0 and 100, inclusive. 
- 
gamesLeft will be between 1 and 15, inclusive. 
- 
mustWin will be between 1 and gamesLeft, inclusive. 
Examples 
0) 

     
2 
0 
1 
1 
Returns: 0.75 
Consider a few illustrative values of p: 
| prob of | prob of 
p | previous | winning series 
----+----------+--------------- 
0.0 | 0.0 | 0.0 
0.1 | 0.01 | 0.1 
0.2 | 0.04 | 0.2 
0.3 | 0.09 | 0.3 
0.4 | 0.16 | 0.4 
0.5 | 0.25 | 0.5 
0.6 | 0.36 | 0.6 
0.7 | 0.49 | 0.7 
0.8 | 0.64 | 0.8 
0.9 | 0.81 | 0.9 
1.0 | 1.0 | 1.0 
So, p is 4 times more likely to be 1.0 than it is to be 0.5, and is 
definitely not 0. Considering only these values of p, and taking a 
weighted average, we find that the probability of winning the series 
is 0.786. Clearly, considering only 11 values of p does not yield the 
required accuracy, but if you consider all possible values, you find 
that your team has a probability of 0.75 of winning the series. 
1) 

     
0 
3 
4 
4 
Returns: 0.0142857142857 
After losing the first 3 games of the ALCS, the Red Sox had a 
probability of less than 2% of winning the series, according to this 
model. 
2) 

     
20 
3 
5 
1 
Returns: 0.9995284409077 
Your team only needs to win 1 out of 5 games, and in the past it has 
won 20/23, so your odds are high. 
3) 

     
0 
20 
1 
1 
Returns: 0.0454545454545 
Your team has never won in the past, so its unlikely they will this 
time. 
4) 

     
0 
0 
1 
1 
Returns: 0.5 
With no previous games, all values of p are equally likely, and as you 
would expect, there is a 50% chance that your team will win. 
This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
