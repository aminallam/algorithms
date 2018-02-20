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

// SRM 266
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

int max(int a,int b){if(a>b)return a;return b;}
int min(int a,int b){if(a<b)return a;return b;}

struct Pos
{
	int r,c;
	Pos(){}
	Pos(string s){r=s[1]-'1';c=s[0]-'a';}
};

int nw;
Pos w[8];
Pos b;
int taken;

int BlackQueenMin(int alpha, int beta);

int WhitePawnsMax(int alpha, int beta)
{
	if(taken>alpha) alpha=taken;
	if(alpha>=beta) return beta;

	int i;

	for(i=0;i<nw;i++)
	{
		if(b.r==w[i].r+1 && abs(b.c-w[i].c)==1)
			return alpha;
	}

	for(i=0;i<nw;i++)
	{
		if(w[i].r<7 && !(w[i].r==b.r-1 && w[i].c==b.c))
		{
			w[i].r++;
			
			alpha=BlackQueenMin(alpha,beta);

			if(alpha<beta && w[i].r==2 && !(w[i].r==b.r-1 && w[i].c==b.c))
			{
				w[i].r++;
				alpha=BlackQueenMin(alpha,beta);
				w[i].r--;
			}
			
			w[i].r--;

			if(alpha>=beta) return beta;
		}
	}

	return alpha;
}

int BlackQueenMin(int alpha, int beta)
{
	if(beta<=alpha) return alpha;

	bool can_move=false;

	int dc,dr,i;

	for(dc=-1;dc<=1;dc++) for(dr=-1;dr<=1;dr++) if(dc!=0||dr!=0)
	{ 
		int k=10000000;
		int ki=-1;

		for(i=0;i<nw;i++)
		{ 
			int r=w[i].r-b.r;
			int c=w[i].c-b.c;
			int ck;

			if(dr==0) ck=c/dc;
			else ck=r/dr;

			if(ck>0 && ck<k && c==ck*dc && r==ck*dr)
			{ 
				k=ck;
				ki=i;
			} 
		} 

		if(ki>=0)
		{
			can_move=true;

			i=ki;

			Pos t=b;

			b=w[i];
			swap(w[i],w[nw-1]);
			nw--;

			taken++;
			beta=WhitePawnsMax(alpha, beta);
			taken--;

			b=t;
			nw++;
			swap(w[i],w[nw-1]);

			if(beta<=alpha) return alpha;
		} 
	} 

	if(!can_move) return max(min(taken,beta),alpha);

	return beta;
}

class AntiChess
{
public:
	int sacrifice(vector<string> white, string black)
	{
		int i;
		nw=white.size();
		for(i=0;i<nw;i++) w[i]=Pos(white[i]);
		b=Pos(black);
		taken=0;
		
		int y=WhitePawnsMax(0, nw);

		cout<<y<<endl;
		return y;
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

	vector<string> var2;
	string var3[]={"a2","c2","d2","e3","h4"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	AntiChess* var0=new AntiChess;
	int var1 = var0->sacrifice(var2, "b6");
	delete var0;

	flag=true;
	if(var1!=5)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"a2","h2"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	AntiChess* var0=new AntiChess;
	int var1 = var0->sacrifice(var2, "g3");
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

	vector<string> var2;
	string var3[]={"a2","e2","h2"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	AntiChess* var0=new AntiChess;
	int var1 = var0->sacrifice(var2, "e6");
	delete var0;

	flag=true;
	if(var1!=3)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"a7","h7"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	AntiChess* var0=new AntiChess;
	int var1 = var0->sacrifice(var2, "a8");
	delete var0;

	flag=true;
	if(var1!=1)
		flag=false;
	if(flag==false) {cout << "Test Case FAILED " << cases_cnt << endl; all_flag=false;}
	else cout << "Test Case Succeeded " << cases_cnt << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 4:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"a3","b3","c3","d3","e3","f3","g3","h3"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	AntiChess* var0=new AntiChess;
	int var1 = var0->sacrifice(var2, "d8");
	delete var0;

	flag=true;
	if(var1!=7)
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
     
Antichess, also called Suicide Chess, is a chess variant in which the 
objective is to lose all of your pieces. The rules of the game are the 
same as those of chess, except that capturing is compulsory. In other 
words, when a player has the opportunity to capture an opponent's 
piece, he must do it. If the player has multiple choices for capturing 
during a single turn, he may choose any single one. The king plays no 
special role in the game; it can be captured like any other piece. 
Because of the forced capture rule, antichess games often have a long 
sequence of forced captures by one player. In this problem, we are 
given an end-game position - specifically, the case when a player has 
only pawns left and the other has a b. Considering we are the 
white player controlling the pawns and we always make the first move, 
we are interested in how many consecutive pawns we can force our 
opponent to capture. The game ends when either the b has been 
captured, the b can no longer capture, there are no pawns left, or 
there is a stalemate. A stalemate is produced if, on white's turn, 
there are no valid pawn moves. The b may move in any straight 
line, horizontally, vertically, or diagonally. The b may not jump 
over other pieces. In other words, all squares between the square 
where the b starts her move and where the b ends her move must 
be empty. When the square where the b ends her move contains a 
pawn of the opponent, then this piece is captured. A pawn can only 
move one row straight forward, to a higher row (rows are numbered from 
1 to 8 and columns from 'a' to 'h'). Pawns on row 2 can also move 2 
rows straight forward. Pawns on row 8 can no longer move. As in the 
case of the b, the pawn is not allowed to jump over other pieces. 
When capturing, the pawn goes one square diagonally forward onto the 
opponent's captured piece. You are given a String[] white, where each 
element contains 2 characters describing the position of a pawn: the 
first character is a lowercase letter between 'a' and 'h', and the 
second character is a digit between '2' and '7'. You are also given a 
String black that contains 2 characters describing the position of the 
b: the first character is a lowercase letter between 'a' and 'h', 
and the second character is a digit between '1' and '8'. Return the 
highest number of pawns you can force your opponent to capture, 
considering their play is optimal. 
Definition 
     
Class: 
AntiChess 
Method: 
sacrifice 
Parameters: 
vector <string>, string 
Returns: 
int 
Method signature: 
int sacrifice(vector <string> white, string black) 
(be sure your method is public) 
     

Notes 
- 
Both white and black sides must capture if they can. 
- 
If a pawn reaches the 8th row, instead of promoting, it just gets 
stuck. 
- 
Like in a normal chess game, a pawn on the 2th row can either move to 
the 3th row or to the 4th row on a single turn. In all the other 
cases, it can only advance a single row. 
Constraints 
- 
white contains between 1 and 8 elements, inclusive. 
- 
Each element of white contains exactly 2 characters. 
- 
The first character in each element of white is a lowercase letter 
between 'a' and 'h', inclusive. 
- 
The second character in each element of white is a digit between '2' 
and '7', inclusive. 
- 
No two pawns will share a column. 
- 
black contains exactly 2 characters. 
- 
The first character in black is a lowercase letter between 'a' and 
'h', inclusive. 
- 
The first character in black is a digit between '1' and '8', 
inclusive. 
- 
black is different than any element of white . 
Examples 
0) 

     
{"a2","c2","d2","e3","h4"} 
"b6" 
Returns: 5 
One possibility is to move the pawn from a2 to a4. The black is forced 
to take the pawn on e3, but then the white is forced to take the b 
on e3 with the pawn on d2. In this case, there is only one pawn 
sacrificed. A better play is the following: 1. Move the pawn from d2 
to d3. b captures the pawn on e3. 2. Move the pawn from c2 to c3. 
b captures the pawn on d3. 3. Move the pawn from a2 to a3. b 
captures the pawn on c3. 4. Move the pawn from h4 to h5. b 
captures the pawn on a3. 5. Move the pawn from h5 to h6. The black 
b cannot capture this pawn. Thus, we were able to sacrifice 4 
pawns. But there is an even better alternative: 1. Move the pawn from 
d2 to d3. b captures the pawn on e3. 2. Move the pawn from d3 to 
d4. b captures the pawn on d4. 3. Move the pawn from a2 to a3. 
b captures the pawn on h4. 4. Move the pawn from a3 to a4. b 
captures the pawn on a4. 5. Move the pawn from c2 to c4. b 
captures the pawn on c4. Now we managed to give away all the pawns, so 
the correct answer for this example is 5. 
1) 

     
{"a2","h2"} 
"g3" 
Returns: 0 
White is forced to capture the b on g3 with the pawn on h2, so no 
pawns are being captured. 
2) 

     
{"a2","e2","h2"} 
"e6" 
Returns: 3 

3) 

     
{"a7","h7"} 
"a8" 
Returns: 1 
We can only move the pawn from h7 to h8. If the black player captures 
this pawn, we can sacrifice the pawn on a7 as well. But since their 
play is optimal, the b would capture the pawn on a7 and the game 
ends. 
4) 

     
{"a3","b3","c3","d3","e3","f3","g3","h3"} 
"d8" 
Returns: 7 
An example with the maximum number of pawns on the board. 
This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
