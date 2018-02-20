/*
USER: aminall1
TASK: sort3
LANG: C++
*/

// Problem: http://ace.delos.com/usacoprob2?a=mQ9yV8V634y&S=sort3
// Submit:  As before
// Problem Number:  54

#include <cstring>	// for memset
#include <cstdio>	// for freopn and scanf
#include <iostream>	// for cout
using namespace std;

// Get minimum of any two things can be compared with <
#define min(x,y) (((x)<(y))?(x):(y))

int n;

int val[1000];

int num[4][4];	// num[a][b]=number of a's in b's part
				// Note that 0 is not used here. This is better for readability

int all[4];		// all[a]=total number of a's
int start[4];	// start[a]=start of a's part

int Part(int ind) // the Part which index ind belongs to
{
	int i;

	for(i=1;i<=3;i++)
	{
		if(ind>=start[i] && ind<start[i]+all[i])
			return i;
	}
	return -1; // we should not reach here
}

void Compute()
{
	// Note that we need to only count number of swaps
	// We do not need to make actual sorting!

	int i,j;

	memset(all,0,sizeof(all));
	memset(num,0,sizeof(num));

	for(i=0;i<n;i++)
		all[val[i]]++;

	start[1]=0;
	for(i=2;i<=3;i++) start[i]=start[i-1]+all[i-1];

	for(i=0;i<n;i++)
	{
		int v=val[i];
		num[v][Part(i)]++;
	}

	int swaps=0;

	// Each swap of these will move the two elements to correct places

	for(i=1;i<=3;i++) for(j=i+1;j<=3;j++)
	{
		int cur_num=min(num[i][j],num[j][i]);
		swaps+=cur_num;
		num[i][j]-=cur_num;
		num[j][i]-=cur_num;
	}

	// Remaining are 3-element cycles
	// Number of cycles = Number of Misplaced elements / 3
	// Each cycle needs two swaps to move the 3 elements to their correct places

	int num_rem_misplaced=0;

	for(i=1;i<=3;i++) for(j=1;j<=3;j++) if(i!=j)
	{
		num_rem_misplaced+=num[i][j];
	}

	swaps+=2*(num_rem_misplaced/3);

	cout<<swaps<<"\n";
}

int main()
{
	//freopen("ThreeVal.in", "r", stdin);
	
	// These lines are needed by usaco
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);

	scanf("%d ", &n);

	int i;
	for(i=0;i<n;i++)
		scanf("%d ", &val[i]);

	Compute();

	return 0;
}
