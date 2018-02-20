// Problem: http://acm.uva.es/p/v104/10443.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  10443

#include <cstdio>	// for freopn and scanf
#include <iostream>	// for cout
using namespace std;

#define MAX_R 100
#define MAX_C 100

int r, c;
int n;

char state[2][MAX_R][MAX_C+1];	// +1 for the \0 at end of c strings
								// [2] because we have two states
char beat[256]; // beat[a]=b --> a beats b, Initialized in main()
				// The maximum character has value(ascii) = 255
				// You may make a function beat() instead of that

// This function handles access out the grid
// It is called "functional sentinel"
char Get(int st, int j, int k)
{
	if(j<r && k<c && j>=0 && k>=0)
		return state[st][j][k];
	return ' '; // Space cannot beat anything
}

void Compute()
{
	int i, j, k, v;
	
	// To easify the code to access adjacent cells
	int rsh[]={0,0,1,-1};
	int csh[]={1,-1,0,0};

	int	s_cur=0; // 0 or 1 for current state index

	for(k=0;k<n;k++) // Iterate over time units
	{
		int s_new=!s_cur; // if s_cur is 0, s_new is 1, and vice versa

		for(i=0;i<r;i++) for(j=0;j<c;j++) // Iterate on every cell
		{							      // See if it will be changed or not
			char here=state[s_cur][i][j];
			state[s_new][i][j]=here;	  // Initially, assume it will not be changed

			for(v=0;v<4;v++) // Check if there is adjacent cell that will change it
			{
				int ni=i+rsh[v], nj=j+csh[v]; 
				char adj=Get(s_cur, ni, nj); // Get adjacent char

				// If adjacent char beats it change current cell
				if(beat[adj]==here) {state[s_new][i][j]=adj; break;}
			}
		}

		s_cur=s_new; // in the next iteration, we will deal with new state as old
	}

	// print the whole grid
	for(i=0;i<r;i++) cout<<state[s_cur][i]<<"\n";
}

int main()
{
	// Comment the following two lines before submitting
	freopen("Rock.in", "r", stdin); // make cin and scanf take from file not from user
	//freopen("Rock.out", "w", stdout); // make cout print to file not screen

	int i, k;
	int num_cases;

	beat[' ']=' '; // ' ' cannot beat any thing

	beat['R']='S'; // R beats S
	beat['S']='P'; // S beats P
	beat['P']='R'; // P beats R

	// We will take the input using scanf() because it is much much much faster than cin
	// It is good practice to use it, even if most problems will pass with cin
	// So, you will not worry about that issue any more

	scanf("%d ", &num_cases); // "%d" = Get num_cases 
							  // " " = skip white spaces (including "\n") after it

	// It is better to keep i for iteraring obn rows, j for iterating on cols
	//   for the whole code

	for(k=0;k<num_cases;k++)
	{
		scanf("%d %d %d ", &r, &c, &n); // Get three integers and skip white spaces
										// between them and "\n" at end of line

		for(i=0;i<r;i++)
			scanf("%[^\n] ", state[0][i]); // Take a complete line, then skip end of line

		Compute();

		if(k<num_cases-1) cout<<"\n"; // Output "\n" only if this is not the last case
	}

	// endl = "\n" + flush output
	// flush ouutput = force output to oppear on screen
	// endl is better while debugging
	// "\n" is faster, better for submitting

	return 0;
}
