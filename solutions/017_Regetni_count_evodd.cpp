// Problem: http://acm.pku.edu.cn/JudgeOnline/problem?id=1809
// Submit:  As before
// Problem Number:  1809

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
using namespace std;

//typedef __int64 LL;
//ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}

typedef long long LL;

int icase;

struct Point
{
	int x,y;
};

int n;
Point pts[10000];

//    yx
// 0->00 EvenEven
// 1->01 EvenOdd
// 2->10 OddEven
// 2->11 OddOdd

LL EvenOddnum[4];		// EvenOddnum[i]=Number of points having case i (see table above)

int OddCase[4][4][4];	// OddCase[i][j][k]=true for j>=i, k>=j, if three points with
						//   Cases i, j, k will form a triangle with area*2 is odd

int Odd(int num)	// Return 1 if Odd, 0 if even
{
	if(num & 1) return 1;
	return 0;
}

int PointCase(int i) // Return case (see table) of this point
{
	return ((Odd(pts[i].y)<<1) | Odd(pts[i].x));
}

int xOdd(int icase)	// 0 if x is even in this case, 1 if odd
{
	if(icase & 1) return 1;
	return 0;
}

int yOdd(int icase)	// 0 if y is even in this case, 1 if odd
{
	if(icase & 2) return 1;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////

void Compute()
{
	int i, j, k;

	// x1y2 - y1x2 + x2y3 - y2x3 + x3y1 -y3x1

	for(i=0;i<4;i++) for(j=i;j<4;j++) for(k=j;k<4;k++)
	{
		int val = xOdd(i)*yOdd(j) - yOdd(i)*xOdd(j) +
			xOdd(j)*yOdd(k) - yOdd(j)*xOdd(k) + xOdd(k)*yOdd(i) - yOdd(k)*xOdd(i);
		
		OddCase[i][j][k]=Odd(val);
	}

	for(i=0;i<4;i++) EvenOddnum[i]=0;

	for(i=0;i<n;i++)
	{
		EvenOddnum[PointCase(i)]++;
	}

	// Now we have to compute cases

	LL iAllodds=0;

	for(i=0;i<4;i++) for(j=i;j<4;j++) for(k=j;k<4;k++)
	{
		if(!OddCase[i][j][k]) // The points with cases i,j,k will form triangle with
		{						// Area*2 is even, so, area will be integral, count them
			// Remember basics of counting
			//  The last case is the general, multiply possibilities
			//  Previous cases are particular because of repititions
			//    So, in them, -1 is provided to avoid using the same point
			
			if(i==j && j==k)
			{
				iAllodds+=EvenOddnum[i]*(EvenOddnum[i]-1)*(EvenOddnum[i]-2)/6;
			}
			else if(i==j)
			{
				iAllodds+=EvenOddnum[i]*(EvenOddnum[i]-1)/2*EvenOddnum[k];
			}
			else if(j==k)
			{
				iAllodds+=EvenOddnum[j]*(EvenOddnum[j]-1)/2*EvenOddnum[i];
			}
			else
			{
				iAllodds+=EvenOddnum[i]*EvenOddnum[j]*EvenOddnum[k];
			}
		}
	}

	cout << "Scenario #" << icase << ":" << "\n" << iAllodds << "\n" << "\n";
}

//////////////////////////////////////////////////////////////////////////////

int main()
{
	int i, num_cases;

	//freopen("regetni.in", "r", stdin);

	scanf("%d ", &num_cases);

	icase=0;

	while(num_cases--)
	{
		icase++;
		
		scanf("%d ", &n);

		for(i=0;i<n;i++)
		{
			scanf("%d %d ", &pts[i].x, &pts[i].y);
		}

		Compute();
	}

	return 0;
}
