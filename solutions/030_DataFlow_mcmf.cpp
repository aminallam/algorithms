#define ON_MY_COMPUTER
#pragma warning(disable:4786)
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
typedef __int64 LL;
ostream& operator<<(ostream& out,const LL& num){char s[100];sprintf(s,"%I64d",num);out<<s;return out;}
istream& operator>>(istream& in,LL& num){char s[100];in>>s;sscanf(s,"%I64d",&num);return in;}

// 53430HJ 10594

#ifndef ON_MY_COMPUTER
typedef long long LL;
#endif

#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

#define oo (0x7FFFFFFF)
#define COST_INF ((0x3FFFFFFF<<32)|0xFFFFFFFF)
#define MAX_NODES (2*100+2) // Maximum possible number of nodes, (INPUT)

typedef LL Type;	// Cost Type
int gcap[MAX_NODES][MAX_NODES]; // gcap[i][j]=Capacity of edge from i to j, can be oo, (INPUT)
Type gcost[MAX_NODES][MAX_NODES]; // gcost[i][j]=Cost of edge from i to j, (INPUT)
int gflow[MAX_NODES][MAX_NODES]; // gflow[i][j]=Flow in edge from i,j, (OUTPUT)
int mc_v[MAX_NODES]; Type mc_d[MAX_NODES]; int mc_pi[MAX_NODES]; // visited, distance, prev
Type mc_pot[MAX_NODES]; // potentials

struct mc_Node{
	int v; Type d;
	mc_Node(int a, Type b):v(a),d(b){}
	bool operator<(const mc_Node& no)const {return d>no.d;}
};

int MinCostMaxFlow(int n, int s, int t, Type& fcost){ // n=numnodes, s=source, t=sink
	int i,j,a,b; if(s==t) return 0;
	for(i=0;i<n;i++) for(j=0;j<n;j++) gflow[i][j]=0;
	for(i=0;i<n;i++) mc_pot[i]=0;
	int flow=0; fcost=0;
	while(true){
		// Dijkstra from s in residual network
		for(i=0;i<n;i++){mc_v[i]=0;mc_d[i]=COST_INF;mc_pi[i]=-1;}
		mc_d[s]=0;
		priority_queue<mc_Node> q; q.push(mc_Node(s,0));
		while(q.size()){
			a=q.top().v; q.pop();
			if(mc_v[a]) continue;
			mc_v[a]=1;

			for(b=0;b<n;b++) if(!mc_v[b])
			{
				if(gflow[b][a]) // Try Undo this edge (Undoing is always better)
				{
					int new_cost=(mc_d[a]+mc_pot[a]-mc_pot[b])-gcost[b][a];
					if(new_cost<mc_d[b]) {
						mc_d[b]=new_cost; mc_pi[b]=a;
						q.push(mc_Node(b, new_cost));
					}
				}
				else if(gflow[a][b]<gcap[a][b])
				{
					int new_cost=(mc_d[a]+mc_pot[a]-mc_pot[b])+gcost[a][b];
					if(new_cost<mc_d[b]) {
						mc_d[b]=new_cost; mc_pi[b]=a;
						q.push(mc_Node(b, new_cost));
					}
				}
			}
		}
		for(i=0;i<n;i++) if(mc_pot[i]<COST_INF) mc_pot[i]+=mc_d[i];
		// End Dijkstra
		if(mc_d[t]==COST_INF) break;
		int cur=t; int cfp=oo; // cfp=current additional flow
		while(cur!=s){
			int pred=mc_pi[cur];
			int val;
			if(gflow[cur][pred]) val=gflow[cur][pred]; // It is always better to undo!
			else val=gcap[pred][cur]-gflow[pred][cur];
			if(cfp>val) cfp=val; cur=pred;
		}
		cur=t;
		while(cur!=s){
			int pred=mc_pi[cur];
			if(gflow[cur][pred]) {gflow[cur][pred]-=cfp; fcost-=cfp*gcost[cur][pred];}
			else {gflow[pred][cur]+=cfp; fcost+=cfp*gcost[pred][cur];}
			cur=pred;
		}
		flow+=cfp;
	}
	return flow;	// gflow contains the actual flow
}

int main()
{
	#ifdef ON_MY_COMPUTER
	freopen("DataFlow.in", "r", stdin);
	#endif
	
	int i, j;

	while(true)
	{
		int n, m;
		if(EOF==scanf("%d %d ", &n, &m)) break;

	    memset(gcap, 0, sizeof(gcap));

		for(i=0;i<m;i++)
		{
			int a, b; LL c;

			#ifndef ON_MY_COMPUTER
			scanf("%d %d %lld ", &a, &b, &c);
			#else
			scanf("%d %d %I64d ", &a, &b, &c);
			#endif

			a--;
			b--;
			
			gcap[a][b]=1;
			gcost[a][b]=c;

			gcap[b][a]=1;
			gcost[b][a]=c;
		}

		int k, d;
		scanf("%d %d ", &d, &k);

		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				gcap[i][j]*=k;

		gcap[n][0]=d;
		gcost[n][0]=0;

		gcap[n-1][n+1]=d;
		gcost[n-1][n+1]=0;

		LL fc=0;
		int f=MinCostMaxFlow(n+2, n, n+1, fc);
		
		if(f!=d) cout << "Impossible." << endl;	else cout << fc << endl;
	}

	return 0;
}

/*
80
140
Impossible.
*/
