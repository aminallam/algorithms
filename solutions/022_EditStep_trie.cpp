// Problem: http://acm.uva.es/p/v100/10029.html
// Submit: http://acm.uva.es/problemset/submit.php
// Problem Number: 10029

#pragma warning(disable:4786)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

// You should study the Trie data structure before reading this solution

char dic[25000][17];
short P[25000];
vector<short> adj[25000];

// Insert adjacent word and avoid repetition

void InsertAdj(int a, int b)
{
	int i;
	for(i=0;i<adj[a].size();i++) if(adj[a][i]==b) return;
	adj[a].push_back(b);
}

#define NUM_CHARS 26

struct Node
{
	short ind;
	Node* next[NUM_CHARS];

	Node() {Init();}
	~Node() {Delete();}

	void Init()
	{
		ind=-1;
		memset(next,0,sizeof(next));
	}

	void Delete()
	{
		int i;
		for(i=0;i<NUM_CHARS;i++) if(next[i]){
			delete next[i];
		}
	}

	void Insert(char* str, short index)
	{
		if(*str==0) ind=index;
		else{
			int ch=(*str)-'a';
			if(!next[ch]) next[ch]=new Node;
			next[ch]->Insert(str+1, index);
		}
	}

	// done = 1 if we have already made a change (delete, or change char)
	// We do not consider Adding a character, because it is equivalent
	//  to delete from another word!

	void GetAdj(char* str, short index, int done)
	{
		if(*str==0)
		{
			if(done) // We have reached end of our word
			{
				if(ind!=-1) // There is really a word here
				{
					// Insert the larger word as adjacent of smaller

					if(index<ind) InsertAdj(index,ind);
					else if(ind<index) InsertAdj(ind,index);
				}
			}
		}
		else
		{
			if(done) // You can only traverse ordinarily
			{
				int ch=(*str)-'a';
				if(next[ch]) next[ch]->GetAdj(str+1, index, done);
			}
			else
			{
				// Nothing: Try traverse ordinarily

				int ch=(*str)-'a';
				if(next[ch]) next[ch]->GetAdj(str+1, index, done);

				// Change: change this character by another 'possible' character

				// If the line: for(i=0;i<ch;i++) if(next[i])
				//  is changed with: for(i=ch+1;i<NUM_CHARS;i++) if(next[i]):
				//  Runtime Error (Signal 11): Invalid Memory Access
				//  Please help me in this (I do not know why)

				int i;
				for(i=0;i<ch;i++) if(next[i]){
					next[i]->GetAdj(str+1, index, 1);
				}

				// Delete: delete this character

				GetAdj(str+1, index, 1);
			}
		}
	}
};

///////////////////////////////////////////////////////////////////////

int n;

int PathDag(int st)
{
	if(P[st]!=-1) return P[st];
	short& len=P[st];

	len=1;

	int i;
	for(i=0;i<adj[st].size();i++) // Try continuing path at every possible adjacent word
	{
		short cur_len=1+PathDag(adj[st][i]);
		if(cur_len>len) len=cur_len;
	}

	return len;
}

void Compute()
{
	int i;

	Node* trie=new Node;

	// Insert All words in Trie

	for(i=0;i<n;i++) trie->Insert(dic[i], i);

	// Get adjacent words for each word

	for(i=0;i<n;i++) trie->GetAdj(dic[i], i, 0);

	delete trie;

	memset(P,-1,n*sizeof(short));

	// Get the longest path in DAG using memoization
	//  Try every starting word
	
	int max_len=0;

	for(i=0;i<n;i++)
	{
		int len=PathDag(i);
		if(len>max_len) max_len=len;
	}

	cout<<max_len<<"\n";
}

///////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("in.txt", "r", stdin);

	n=0;

	while(true)
	{
		scanf("%s ", dic[n]);
		if(dic[n][0]==0) break;
		n++;
	}

	Compute();

	return 0;
}
