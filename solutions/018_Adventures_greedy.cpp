// Problem: http://acm.tju.edu.cn/toj/showp2240.html
// Submit: As before
// Problem Number: 2240

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct Station
{
	int d,p,m;
};

int c,d,n;

Station s[1000+1];

struct CompSta
{
bool operator()(const int& s1, const int& s2)
{
	return s[s1].p>s[s2].p;
}
};

int km[100000+1];	// km[i]=id of station at distance i, or -1 if none

int Compute()
{
	int i;

	// The queue will hold indexes in s[]

	priority_queue<int, vector<int>, CompSta> q;

	int pr=0;

	for(i=0;i<d;i++)
	{
		// If there is a station here, push it in queue

		if(km[i]!=-1)
			q.push(km[i]);

		// Choose the best station from which we can get out litre of gas for
		//	the current kilometer

		while(true)
		{
			int cs=q.top();

			Station& st=s[cs];

			// Make sure this station still has some gas, and within distance=c
			//	from current kilometer (so we can hold it in our tank all that distance).

			if(st.m>0 && i-st.d<c)
			{
				pr+=st.p;
				st.m--;
				break;
			}
			else if(q.empty())
			{
				// No station! we are lost in the desert

				return -1;
			}
			else
			{
				// This station is no more useful, try another one

				q.pop();
			}
		}
	}

	return pr;
}

int main()
{
	int i;

	//freopen("in.txt", "r", stdin);

	while(true)
	{
		scanf("%d %d ", &c, &d);
		if(c==0 && d==0) break;

		scanf("%d ", &n);

		memset(km,-1,sizeof(km));

		// Consider our initials state as a station at distance 0

		s[0].p=0; s[0].m=50; s[0].d=0;
		km[0]=0;

		n++;

		for(i=1;i<n;i++)
		{
			scanf("%d %d %d ", &s[i].d, &s[i].p, &s[i].m);
			km[s[i].d]=i;
		}

		int pr=Compute();

		if(pr==-1) cout<<"impossible"<<"\n";
		else cout<<pr<<"\n";
	}

	return 0;
}
