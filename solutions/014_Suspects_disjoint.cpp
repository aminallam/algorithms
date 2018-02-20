// Problem: http://acm.pku.edu.cn/JudgeOnline/problem?id=1611
// Submit:  As before
// Problem Number:  1611

#pragma warning(disable:4786)
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

///////////////////////////////////////////////////////////////////////////

struct disjoint_sets{
	vector<int> parent;
	disjoint_sets (int n):parent(n) {ReInitialize(n);}
	void ReInitialize(int n) {for(int i=0;i<n;i++) parent[i]=-1;}
	void Union(int, int);
	int  Find(int);
};
void disjoint_sets::Union(int i, int j){
	i=Find(i); j=Find(j);
	if(i==j) return;
	int temp=parent[i]+parent[j];
	if(parent[i]>parent[j]) {parent[i]=j; parent[j]=temp;}
	else {parent[j]=i; parent[i]=temp;}
}
int disjoint_sets::Find(int i) {
	for(int r=i; parent[r]>=0; r=parent[r]);
	while(i!=r) {int s=parent[i]; parent[i]=r; i=s;}
	return r;
}

///////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("Suspects.in", "r", stdin);
	//freopen("Suspects.out", "w", stdout);

	int i, j, n, m, k;
	
	// We put this line here to avoid constructing the vector every time
	disjoint_sets ss(30000);

	while(true)
	{
		scanf("%d %d ", &n, &m);
		
		if(n==0 && m==0)
			break;

		// Create n disjoint sets, each set contains one item
		ss.ReInitialize(n);
		
		for(i=0;i<m;i++)
		{
			scanf("%d ", &k);
			if(k==0) continue;

			int num1;
			scanf("%d ", &num1);

			for (j=1;j<k;j++)
			{
				int num2;
				scanf("%d ", &num2);

				// Union the set containing num1 with the set containing num2
				ss.Union(num1, num2);
			}
		}

		int count = 0;

		for(i=0;i<n;i++)
		{
			// Check if the set containing item i is the same set containing item 0
			if(ss.Find(i)==ss.Find(0))
				count++;
		}

		cout << count << "\n";
	}

	return 0;
}
