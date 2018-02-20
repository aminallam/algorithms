// Problem: http://acm.uva.es/p/v104/10443.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  10443

#include <cstdio>	// for freopn and scanf
#include <iostream>	// for cout
using namespace std;

// This version is faster because it uses real sentinels
// (A border of spaces surrounding the borad to avoid goind outside board)
// You can choose anything other than space, but also not R,P,S

#define MAX_R 100
#define MAX_C 100

int r, c;
int n;

char state[2][MAX_R+2][MAX_C+1+2]; // +1 for \0 at end of c strings
								   // Additional +2 For boarder of spaces

char beat[256]; // beat[a]=b --> a beats b, Initialized in main()
				// The maximum character has value(ascii) = 255
				// You may make a function beat() instead of that

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

		for(i=1;i<=r;i++) for(j=1;j<=c;j++) // Iterate on every cell
		{							      // See if it will be changed or not
			char here=state[s_cur][i][j];
			state[s_new][i][j]=here;	  // Initially, assume it will not be changed

			for(v=0;v<4;v++) // Check if there is adjacent cell that will change it
			{
				int ni=i+rsh[v], nj=j+csh[v]; 
				char adj=state[s_cur][ni][nj]; // Get adjacent char, do not care 
								// about going outside board, because of border of spaces

				// If adjacent char beats it change current cell
				if(beat[adj]==here) {state[s_new][i][j]=adj; break;}
			}
		}

		s_cur=s_new; // in the next iteration, we will deal with new state as old
	}

	// print the whole grid
	for(i=1;i<=r;i++)
	{
		state[s_cur][i][c+1]='\0'; // Put the \0 again so cout will work correctly
		cout<<(state[s_cur][i]+1)<<"\n";
	}
}

int main()
{
	// Comment the following two lines before submitting
	freopen("Rock.in", "r", stdin); // make cin and scanf take from file not from user
	//freopen("Rock.out", "w", stdout); // make cout print to file not screen

	int i, j, k;
	int num_cases;

	beat[' ']=' '; // ' ' cannot beat anything

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

		for(i=1;i<=r;i++)		// Note that the first row will contain spaces
			scanf("%[^\n] ", state[0][i]+1); // Take a complete line, then skip end of line
								// +1 to put it after one character of start

		// Put Sentinels (Take care of the \0 located at end of each row)
		// So, we did it after the scanf

		for(j=1;j<=c;j++)
		{
			state[0][0][j]=state[1][0][j]=' '; // First row will contain spaces
			state[0][r+1][j]=state[1][r+1][j]=' '; // Last row will contain spaces
		}

		for(i=1;i<=r;i++)
		{
			state[0][i][0]=state[1][i][0]=' '; // First col will contain spaces
			state[0][i][c+1]=state[1][i][c+1]=' '; // Last col will contain spaces
		}

		// For debugging
		//for(i=0;i<r+2;i++) {for(j=0;j<c+2;j++) cout<<state[0][i][j]; cout<<endl;}

		Compute();

		if(k<num_cases-1) cout<<"\n"; // Output "\n" only if this is not the last case
	}

	// endl = "\n" + flush ouutput
	// flush ouutput = force output to oppear on screen
	// endl is better while debugging
	// "\n" is faster, better for submitting

	return 0;
}
