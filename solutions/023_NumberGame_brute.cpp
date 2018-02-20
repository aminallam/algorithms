// Problem: http://acm.tju.edu.cn/toj/showp1017.html
// Submit: As before.
// Problem Number: 1017

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
using namespace std;

// The complexity of this program is not large as we do not use all entries in this table
//  Most entries are not valis and so not used. We may use a map instead to save space,
//   but it will require more processing time

int T[1<<19];

#define BIT(i) (1<<((i)-2))

int Remove(int state, int i) // remove number i from state
{
	int j,k;

	int new_ind=state;

	for(j=i;j<=20;j+=i) // Iterate over multiples of removed number
	{
		if(!(new_ind & BIT(j)))
			continue;

		new_ind &= ~BIT(j);

		for(k=2;k<=20;k++) // Iterate over removed numbers (we do not need to iterate
		{					// on their multiples as they are also removed!)
			if(j+k>20)
				break;

			if(!(new_ind & BIT(k)))
				new_ind &= ~BIT(j+k);
		}
	}

	return new_ind;
}

int GetT(int ind) // Return 1 if the current state is a winning state, 0 otherwise
{
	if(ind==0) return 0;

	if(T[ind]!=-1) return T[ind];
	int& res=T[ind];

	res=0;

	int i;

	for(i=2;i<=20;i++) // Try to remove every available number
	{
		if(ind & BIT(i))
		{
			int new_ind=Remove(ind,i);

			int y=GetT(new_ind);
			
			if(y==0)
			{
				res=1;
				break;
			}
		}
	}

	return res;
}


int icase;

// start is a set containing available numbers at start of our case
//  but take care, it is not the start of the game, it is in the middle
//  so, every number not available is considered as removed

int start;

void Compute()
{
	int i;

	int res=GetT(start);

	cout<<"Scenario #"<<icase<<":\n";

	if(res==1)
	{
		cout<<"The winning moves are:";

		for(i=2;i<=20;i++) // Try every number (no break here) to see if it is a move
		{
			if(start & BIT(i))
			{
				int new_ind=Remove(start,i);

				int y=GetT(new_ind);

				if(y==0) cout<<" "<<i;
			}
		}

		cout<<".\n";
	}
	else
	{
		cout<<"There is no winning move."<<"\n";
	}

	cout<<"\n";
}

void Start()
{
	//freopen("in.txt", "r", stdin);

	int i;

	memset(T,-1,sizeof(T));

	int ncases;
	scanf("%d ", &ncases);

	for(icase=1;icase<=ncases;icase++)
	{
		// We do not need to initialize T again, to make use of previous results

		int n;
		scanf("%d ", &n);

		start=0;

		for(i=0;i<n;i++)
		{
			int num;
			scanf("%d ", &num);
			
			start|=BIT(num);
		}

		Compute();
	}
}

int main()
{
	// Do not put any code in main()
	// Please, beleive me, this is better
	// There is strange bugs that may occur if you put code in main()

	Start();
	return 0;
}
