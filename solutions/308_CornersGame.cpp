// Problem: http://www.topcoder.com/stat?c=problem_statement&pm=6475
// Submit: SRM 308 Div1 500, Pracice Room 327

#pragma warning(disable:4786)
#include <iostream>
int cases_cnt;

//typedef long long LL;
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

#define oo (0x7FFFFFFF)

// Convert an array to number
//	The array contains 'dims' elements, each element can have values
//	from 0 to 'size'-1
// This is called "Ranking": Mapping of arrays to numbers such that every array
//  having same size and dims has different number
int ArrToNum(int arr[], int size, int dims){
	int i, num=0;
	for(i=0;i<dims;i++) num=size*num+arr[i];
	return num;
}

// Inverse of previous function (Number to array)
void NumToArr(int num, int arr[], int size, int dims){
	int i;
	for(i=dims-1;i>=0;i--) {arr[i]=num%size; num/=size;}
}

#define DIM		6
#define DIM2	(DIM*DIM) // Range of possible integers representing points (see line below)

#define PT(i,j) ((i*DIM)+j)	// Simple Ranking for points (Convert point to number also)

#define MAX_LOC (DIM2*DIM2*DIM2*DIM2) // Number larger than max number representing an
										// array with dims=4, size=36. Each such array
										// represents a state in our solution space

char done[MAX_LOC]; // done[i]=1 if the state i seen before (char saves space than bool)
int	d[MAX_LOC];	// d[i] Distance from start state to state i

class CornersGame
{
public:
	int countMoves(vector<string> board)
	{
		int i,j,k;

		int arr[4];

		arr[0]=PT(4,4); arr[1]=PT(4,5); arr[2]=PT(5,5); arr[3]=PT(5,4);
		sort(arr,arr+4); // Try to think why we made this sort
		int src = ArrToNum(arr,DIM2,4); // Number representing start state
		
		arr[0]=PT(0,0); arr[1]=PT(0,1); arr[2]=PT(1,1); arr[3]=PT(1,0);
		sort(arr,arr+4);
		int dst = ArrToNum(arr,DIM2,4); // Number representing goal state

		for(i=0;i<MAX_LOC;i++) {d[i]=oo; done[i]=0;}
		d[src]=0;

		// BFS (Breadth first search). BFS can be done here because all arcs
		//	(transitions between states) have the same weight (1)

		queue<int> q;
		done[src]=1;
		q.push(src);

		while(!q.empty()) 
		{
			int cur_state=q.front(); q.pop();
			if(cur_state==dst) break;
			
			// Obtain corresponding array
			NumToArr(cur_state, arr, DIM2, 4);
			
			int shi[]={-1,1,0,0};
			int shj[]={0,0,1,-1};

			for(i=0;i<4;i++)
			{
				int ci, cj;
				ci=arr[i]/DIM; cj=arr[i]%DIM; // Get Point Corresponding to arr[i]

				for(j=0;j<4;j++) // Try moving draught in arr[i] to direction j
				{
					int ni=ci+shi[j]; // Get New location if we move in this direction
					int nj=cj+shj[j];

					if(ni<0 || nj<0 || ni>=DIM || nj>=DIM) continue;
					if(board[ni][nj]=='r') continue; // We cannot move

					// Detect if there is another draught in this direction
					// If so, step over. Also, if there is a stone, step over

					bool step_over=false;
					
					for(k=0;k<4;k++)
					{
						int oi,oj;
						if(k==i) continue;
						oi=arr[k]/DIM;
						oj=arr[k]%DIM;

						if(oi==ni&&oj==nj) step_over=true;
					}

					if(!step_over)
					{
						if(board[ni][nj]=='s') step_over=true;
					}

					// Adjust ni,nj after step over
					if(step_over) {ni+=shi[j]; nj+=shj[j];}
					if(ni<0 || nj<0 || ni>=DIM || nj>=DIM) continue;

					// There should be a space in the location our draught will stay in!
					if(board[ni][nj]!='.') continue;

					// Get Array corresponding to new state					
					int narr[4]; memcpy(narr, arr, sizeof(narr));
					narr[i]=PT(ni,nj);
					sort(narr,narr+4);

					// Get number corresponding to the new state
					int new_state=ArrToNum(narr, DIM2, 4);

					// Push the new state in the queue if it is not seen before
					if(!done[new_state])
					{
						done[new_state]=1;
						d[new_state]=d[cur_state]+1;
						q.push(new_state);
					}
				}
			}
		}
		
		if(d[dst]==oo) return -1; // We did not find path
		return d[dst];
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
	string var3[]={"......", 
 "......",
 "......",
 "......",
 "......",
 "......"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	CornersGame var0;
	int var1 = var0.countMoves(var2);

	flag=true;
	if (var1!=16)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 0 << endl; return 0;}
	else cout << "Test Case Succeeded " << 0 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 1:
	cases_cnt++;

	vector<string> var2;
	string var3[]={".....s",
 "..s.r.",
 "r.....",
 ".srs..",
 "..r...",
 "......"};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	CornersGame var0;
	int var1 = var0.countMoves(var2);

	flag=true;
	if (var1!=19)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 1 << endl; return 0;}
	else cout << "Test Case Succeeded " << 1 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 2:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"......",
 "......",
 "....ss",
 "....ss",
 "...r..",
 "...r.."};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	CornersGame var0;
	int var1 = var0.countMoves(var2);

	flag=true;
	if (var1!=-1)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 2 << endl; return 0;}
	else cout << "Test Case Succeeded " << 2 << endl;
	}

	///////////////////////////////////////////////////////

	{
	//Test case # 3:
	cases_cnt++;

	vector<string> var2;
	string var3[]={"...s.r",
 "..r.s.",
 "rr.s..",
 "..s.rr",
 "s.rr..",
 ".s.s.."};
	for (i=0; i<sizeof(var3)/sizeof(var3[0]); i++)
		var2.push_back(var3[i]);

	CornersGame var0;
	int var1 = var0.countMoves(var2);

	flag=true;
	if (var1!=54)
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 3 << endl; return 0;}
	else cout << "Test Case Succeeded " << 3 << endl;
	}

	///////////////////////////////////////////////////////

	cout << "All cases passed." << endl;
	return 0;
}

//////////////////////////////////////////////////////////////////////

/*

Problem Statement 
     
This problem contains an image that can be viewed in the applet. 
A player has four draughts which are placed in the bottom right corner 
of a 6 x 6 chessboard. The draughts are arranged in a square with 2 
rows and 2 columns (see picture below). Some cells on the board may 
contain red flags, and some may contain stones. 

The player's goal is to move all the draughts to the top left corner 
and arrange them in a square using a minimal number of moves. The 
draughts are indistinguishable, so their order in the final position 
doesn't matter. The target cells are guaranteed to be free. There are 
two kinds of moves that can be made by a draught. The first is to move 
to any vertically or horizontally adjacent free cell. The second is to 
jump over a single vertically or horizontally adjacent draught or 
stone into a free cell. The player can never move a draught into a 
cell that contains a flag, stone or other draught and he can never 
jump over a flag or an empty space. 
You will be given a vector <string> board where each element 
represents a single row of the chessboard. The rows are given from top 
to bottom, and each row is given from left to right. '.' represents a 
free cell, 'r' represents a cell with a red flag, and 's' represents a 
cell with a stone. Return the minimal number of moves necessary to 
reach the goal, or -1 if it is impossible. 
Definition 
     
Class: 
CornersGame 
Method: 
countMoves 
Parameters: 
vector <string> 
Returns: 
int 
Method signature: 
int countMoves(vector <string> board) 
(be sure your method is public) 
     

Constraints 
- 
board will contain exactly 6 elements. 
- 
Each element of board will contain exactly 6 characters. 
- 
Each element of board will contain only the characters 'r', 's', and 
'.'. 
- 
board will contain '.' characters at the initial and desired final 
positions of the draughts. 
Examples 
0) 

     
{"......", 
"......", 
"......", 
"......", 
"......", 
"......"} 
Returns: 16 

1) 

     
{".....s", 
"..s.r.", 
"r.....", 
".srs..", 
"..r...", 
"......"} 
Returns: 19 
The board shown on the picture above. 
2) 

     
{"......", 
"......", 
"....ss", 
"....ss", 
"...r..", 
"...r.."} 
Returns: -1 
We can not make any move. 
3) 

     
{"...s.r", 
"..r.s.", 
"rr.s..", 
"..s.rr", 
"s.rr..", 
".s.s.."} 
Returns: 54 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
