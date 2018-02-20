// Problem: http://acm.uva.es/p/v6/645.html
// Submit:  http://acm.uva.es/problemset/submit.php
// Problem Number:  645

#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

struct Node
{
	string		name;
	vector<int> children;	// vector[i] is the index of ith child in seq_entries
};
// Tree: The entry name and the indexes of the children
vector<Node> seq_entries;	

// Indexes in seq_entries
stack<int> stk_indexes;

struct CompareNode
{
	bool operator() (const int n1, const int n2)
	{
		char a=seq_entries[n1].name[0], b=seq_entries[n2].name[0];
		
		// treat Root as any directory here
		if(a=='R') a='d'; if(b=='R') b='d';
		
		if(a=='f' && b=='f')
			return (seq_entries[n1].name < seq_entries[n2].name);

		// If the two elements are different, prefer directories
		if(a!=b) {
			if(a=='d') return true;
			if(b=='d') return false;
		}

		// Here, The two elements are directories, so they are equal
		//  Remember that this function returns true only if <
		//  They are equal, and stable_sort will prefer the first in original ordering
		return false;
	}
};

void Compute(int current, int depth)
{
	int i;
	
	Node& node = seq_entries[current];

	for (i=0; i<depth; i++)
		cout << "|     ";
	cout << node.name << "\n";

	// The usage of stable_sort allows equal items to preserve their relative ordering
	//	(Directories names in our problem should be ordered according to their 
	//		original ordering appearing in input data)
	
	stable_sort(node.children.begin(), node.children.end(), CompareNode());

	for (i=0; i<node.children.size(); i++)
	{
		int n = node.children[i];

		// Process child nodes in Depth first. Adjust depth if it is directory
		if(seq_entries[n].name[0]=='d') Compute(n, depth+1);
		else Compute(n, depth);
	}
}

int main()
{
	//freopen("filemapping.in", "r", stdin);

	// we used cin for input in this problem because max sizes are not determined

	int casenum=0;

	while(true)
	{
		casenum++;
		
		// Clear Old variables

		seq_entries.clear();
		while (stk_indexes.size()>0) stk_indexes.pop();

		// The idea: Put the root directory on stack
		// Then for each new directory, put it on stack, and process the following entries as 
		//	its children until you encounter ] then pop this directory
		
		Node node;
		node.name = "ROOT";
		
		seq_entries.push_back(node);
		stk_indexes.push(0);			// Now the root is on the stack

		while(true)
		{
			string current;
			cin >> current;

			if(current=="*") break;			// Goto next test case
			if(current=="#") goto end_prog; // This was the last test case

			if (current=="]")
			{
				stk_indexes.pop();
			}
			else
			{
				int iIndex = seq_entries.size();

				Node node1;
				node1.name = current;

				// This item is a child of the directory on top of stack
				seq_entries.push_back(node1);
				seq_entries[stk_indexes.top()].children.push_back(iIndex);

				// If this item is directory, push it in stack of directories
				if(current[0]=='d') stk_indexes.push(iIndex);
			}
		}

		if (casenum>1) cout<<"\n";

		cout<<"DATA SET "<< casenum <<":\n";

		Compute(0,0);
	}
	
	end_prog:

	return 0;
}
