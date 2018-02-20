// Problem: http://www.ncst.ernet.in/education/courses/apgdst/pgpfac/assignments/cheese.html
// Submit: Not available, but you can test on cases in comment at end of file

#pragma warning(disable:4786)
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

#define min(x,y) (((x)<(y))?(x):(y))

int icase;
#define NUM_NODES 102

struct Hole
{
	double x, y, z;
	double r;
};

double Distance(Hole& a, Hole& b)
{
	double d=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
	d=sqrt(d);		// Distance between centers of holes
	d-=(a.r+b.r);	// Actual distance across cheese will decrease by the two radius
	if(d<0) d=0;	// Distance cannot be negative. This case happens for overlapping holes
	return d;
}

Hole	holes[NUM_NODES];
int		n;

double	d[NUM_NODES];
char	done[NUM_NODES];

double	g[NUM_NODES][NUM_NODES];

void Compute()
{
	int i, j;

	for(i=0;i<n;i++) for(j=0;j<n;j++) // Get all distances and save them in g
	{
		g[i][j]=Distance(holes[i], holes[j]);
	}

	// Simple Dijkstra (without priority queue) for fast coding

	for(i=0;i<n;i++)
	{
		d[i]=1e300;
		done[i]=0;
	}

	int st_pos=n-1; // Start index as  we set in input
	int end_pos=n-2; // End index as  we set in input

	d[st_pos]=0;

	while(true)
	{
		int cur=-1;

		for(i=0;i<n;i++) if(!done[i])
		{
			if(cur==-1 || d[i]<d[cur])
				cur=i;
		}

		if(cur==-1) break;	// We did not reach goal
		if(cur==end_pos) break;	// We have reached goal

		done[cur]=1;

		for(i=0;i<n;i++) if(i!=cur && !done[i])
		{
			d[i]=min(d[i], d[cur]+g[cur][i]);
		}
	}

	if(d[end_pos]>1e300-1){} // this will not happen (happens only if no path)
	
	double val=d[end_pos];
	val*=10;
	
	cout.setf(ios::fixed);
	cout.precision(0);
	
	cout << "Cheese " << icase << ": Travel time = " << val << " sec" << "\n";
}

int main()
{
	int i;
	icase=0;

	freopen("cheese.in", "r", stdin);
	//freopen("cheese.out", "w", stdout);

	while(true)
	{
		scanf("%d ", &n);
		if(n==-1) break;

		icase++;
		
		for(i=0;i<n;i++)
		{
			scanf("%lf %lf %lf %lf ", &holes[i].x, &holes[i].y, &holes[i].z, &holes[i].r);
		}

		n+=2;

		// Assume start and end locations are holes with radius=0

		// Start Node (index=n-1)
		scanf("%lf %lf %lf ", &holes[n-1].x, &holes[n-1].y, &holes[n-1].z); holes[n-1].r=0;
		
		// Goal Node (index=n-2)
		scanf("%lf %lf %lf ", &holes[n-2].x, &holes[n-2].y, &holes[n-2].z); holes[n-2].r=0;

		Compute();
	}

	return 0;
}

/////////////////////////////////////////////////////////
/*
Input File
----------
1
20 20 20 1
0 0 0
0 0 10
1
5 0 0 4
0 0 0
10 0 0
80
-220 -357 346 16
-90 -119 202 9
268 -239 54 17
393 276 310 17
-173 -241 -353 16
157 122 349 12
-237 -190 335 15
-232 -174 -311 6
482 -34 369 10
237 317 65 8
405 -399 439 5
312 -158 -163 1
0 -205 -18 14
13 -293 474 13
16 -46 -179 14
319 17 -256 14
-126 273 449 8
-157 200 420 10
-16 -211 -135 12
-31 -211 478 16
318 -180 280 18
58 -130 486 20
457 -227 382 10
257 -118 -356 19
-276 361 215 2
-196 85 462 17
471 -112 -340 8
-6 -293 -90 14
472 247 -182 11
-295 -39 -213 3
-339 283 -374 1
41 -178 232 4
275 367 196 19
-389 -178 436 7
30 -71 59 9
-290 -139 399 3
-337 335 270 18
-169 -198 162 9
151 142 -31 7
310 -193 -350 17
143 -137 123 13
-16 -134 179 1
345 7 231 20
223 380 47 12
93 -233 429 8
-362 334 -175 5
187 495 -25 15
-254 100 -347 19
-259 240 314 16
362 175 97 2
-279 431 363 15
172 428 -250 19
-296 343 -208 1
-31 103 83 10
-100 -83 495 15
95 -158 488 13
21 -11 37 9
-142 78 216 7
-168 377 177 5
-287 389 1 9
409 272 -248 17
409 -25 -166 7
295 287 -194 20
-116 -313 -204 3
-164 -397 384 3
366 204 219 12
432 -399 -89 17
-92 -223 417 4
27 -64 -300 17
173 335 67 5
166 224 228 5
-341 333 -57 8
211 -321 -353 17
356 40 -199 15
292 -186 -55 19
58 -393 -313 1
88 265 -142 12
38 353 -310 12
-209 -184 105 15
115 277 140 20
100 300 -234
-213 -127 22
-1

Output File
----------
Cheese 1: Travel time = 100 sec
Cheese 2: Travel time = 20 sec
Cheese 3: Travel time = 5881 sec
*/
