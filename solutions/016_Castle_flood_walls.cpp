/*
USER: aminall1
TASK: castle
LANG: C++
*/

// Problem: http://ace.delos.com/usacoprob2?a=PTPUp595geF&S=castle
// Submit:  As before

#include <iostream>
#include <cstdio>
using namespace std;

// 1 (1<<0): wall to the west 
// 2 (1<<1): wall to the north
// 4 (1<<2): wall to the east 
// 8 (1<<3): wall to the south

// ch_dirs[i] = character corresponds to wall i
char* ch_dirs="WNES";

// Dir[i]=(x,y) shifts needed to pass wall i
int Dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};

// (y,x)
enum {Y,X};

int m, n;
int Grid[50][50]; // Grid[y][x]: Input, each integer describes walls around cell (x,y)

// Color[i][j]=room id (color) of the room containing this cell
int Color[50][50]; // Color[y][x]

// Sizes[i]=size of room having id (or color) = i
int Sizes[50*50];

void FloodFill(int y, int x, int c)
{
	int i;
	
	for(i=0;i<4;i++)
	{
		int newx, newy;
		newx=x+Dir[i][X];
		newy=y+Dir[i][Y];

		// Color[newy][newx]==-1: The adjecnt cell is empty
		// ((Grid[y][x]>>i)&1)==0 OR (Grid[y][x]&(1<<i))==0 :
		//We can reach the adjacent cell (no wall between us)

		if(Color[newy][newx]==-1 && (Grid[y][x]&(1<<i))==0)
		{
			// In BFS and Floodfill, it is better to set visited immediately
			Color[newy][newx]=c;
			FloodFill(newy, newx, c);
		}
	}
}

int main()
{
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	
	scanf("%d %d ", &m, &n);
	
	int i,j;
	
	for(i=0;i<n;i++) for(j=0;j<m;j++)
		scanf("%d ", &Grid[i][j]);
			
	int x, y;

	int fc=0; // current color

	// Every cell is not filled yet
	memset(Color, -1, sizeof(Color));
	
	for(y=0;y<n;y++) for(x=0;x<m;x++)
	{
		if(Color[y][x]==-1) // Empty
		{
			// Make flood fill for this room using color=fc
			// Room i will have color i
			Color[y][x]=fc;
			FloodFill(y, x, fc);
			fc++;
		}
	}
	
	int maxsize=0;
	
	// Determine the size of each room, and the maximium room size
	// Initially, size of each room is 0, then if we encounter a cell with thid room id
	//  we increase the size of the corresponding room by 1
	
	memset(Sizes, 0, sizeof(Sizes));

	for(y=0;y<n;y++) for(x=0;x<m;x++)
	{
		Sizes[Color[y][x]]++;
		if (Sizes[Color[y][x]]>maxsize)
			maxsize=Sizes[Color[y][x]];
	}

	// Determine what wall to remove to obtain a room with maximum size
	
	// These fields are required in output in problem statement
	int maxsize2=0;
	int cx,cy;
	char dir;

	// We iterate on grid on specific order, such that in case of tie, we will prefer
	//  the first encountered room, and this will be valid according to problem statement
	
	for(x=0;x<m;x++) for(y=n-1;y>=0;y--)
	{
		for(i=1;i<=2;i++) // Try removing north and east walls only
		{					// This also helps for the previous issue of tie
			int newx, newy;
			newx=x+Dir[i][X];
			newy=y+Dir[i][Y];
			
			if(newx>=0 && newx<m && newy>=0 && newy<n)
			{
				// There is a wall between here and adjacent cell
				if(Color[y][x]!=Color[newy][newx])
				{
					// Compute size of room if we remove this wall
					int newsize=Sizes[Color[y][x]]+Sizes[Color[newy][newx]];

					if(newsize>maxsize2)
					{
						maxsize2=newsize;
						cx=x; cy=y;
						dir=ch_dirs[i];
					}					
				}
			}
		}
	}
	
	cout << fc << "\n";
	cout << maxsize << "\n";
	cout << maxsize2 << "\n";
	cout << (cy+1) << " " << (cx+1) << " " << dir << "\n";

	return 0;
}
