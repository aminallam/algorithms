// Problem: See comment at end of this file
// Submit: Not available now! But there are some test cases in main()

#pragma warning(disable:4786)
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////

class SwapSort
{
public:
	string swaps(string s)
	{
		int i, n=s.size();
		string r=s; sort(r.begin(),r.end());
		string res;

		// s is the string we are sorting
		// r is the sorted string

		bool sorted=false;

		while(!sorted)
		{
			sorted=true;

			for(i=0;i<n;i++) if(r[i]!=s[i])
			{
				sorted=false;

				// We are sure we will swap the element r[i]
				// Because it is the smallest element not in its place

				int from=s.find(r[i]);	// index of the element we need to swap

				// Now to should swap our element r[i] with the least element (other than it)
				//	occurring in its cycle of misplaced elements

				// In fact every swap in this cycle will be valid towards minimum total swaps
				//	because the cycle of misplaced elements will be divided into two cycles
				//	of misplaced elements, and number of edges of the two cycles will be smaller 
				//	by 1 from the large cycle for any such swap

				int to=s.find(r[from]);	// index of the element our element stay in its place
				int best=to;			// Good candidate for swap, but we should check
										//  other elements in this cycle

				while(true)
				{
					to=s.find(r[to]);
					if(to==from) break;
					if(s[to]<s[best]) best=to;
				}

				if(res.size()) res+=",";
				res+=s[from]; res+=s[best];

				swap(s[from],s[best]);

				break;
			}
		}

		return res;
	}
};

//////////////////////////////////////////////////////////////////////

int main()
{
	bool flag;
	int cases_cnt=-1;

	//Test case # 0:
	cases_cnt++;

	SwapSort var0;
	string var1 = var0.swaps("ABCED");

	flag=true;
	if (var1!="DE")
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 0 << endl; return 0;}
	else cout << "Test Case Succeeded " << 0 << endl;

	///////////////////////////////////////////////////////

	//Test case # 1:
	cases_cnt++;

	SwapSort var2;
	string var3 = var2.swaps("axrA");

	flag=true;
	if (var3!="Aa,ax")
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 1 << endl; return 0;}
	else cout << "Test Case Succeeded " << 1 << endl;

	///////////////////////////////////////////////////////

	//Test case # 2:
	cases_cnt++;

	SwapSort var4;
	string var5 = var4.swaps("problematic");

	flag=true;
	if (var5!="ac,ap,be,bi,br,co,il,pt")
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 2 << endl; return 0;}
	else cout << "Test Case Succeeded " << 2 << endl;

	///////////////////////////////////////////////////////

	//Test case # 3:
	cases_cnt++;

	SwapSort var6;
	string var7 = var6.swaps("abcdefABCDEF");

	flag=true;
	if (var7!="Aa,Bb,Cc,Dd,Ee,Ff")
		flag=false;
	if (flag==false) {cout << "Test Case FAILED " << 3 << endl; return 0;}
	else cout << "Test Case Succeeded " << 3 << endl;

	///////////////////////////////////////////////////////

	cout << "All cases passed." << endl;
	return 0;
}

//////////////////////////////////////////////////////////////////////

/*

Problem_Statement 
     
Given a string of distinct letters, sort them into ascending order by 
doing a sequence of swaps, where each swap can interchange any two of 
the letters. 
Create a class SwapSort that contains a method swaps that is given a 
string letters and that returns a string showing the shortest sequence 
of swaps which will sort letters. Each swap in the returned sequence 
should be shown as the two letters being swapped, and adjacent swaps 
should be separated by a single comma (','). 
If there is more than one minimal swap sequence, return the one that 
comes first lexicographically (in the ASCII ordering). 
Definition 
     
Class: 
SwapSort 
Method: 
swaps 
Parameters: 
string 
Returns: 
string 
Method signature: 
string swaps(string letters) 
(be sure your method is public) 
     

Constraints 
- 
letters will contain between 1 and 50 letters 'A'-'Z' or 'a'-'z', 
inclusive. 
- 
The characters in letters will be distinct. 
Examples 
0) 

     
"ABCED" 
Returns: "DE" 
This can be sorted with a single swap. Of course "ED" would be another 
way of expressing this swap, but "DE" comes earlier alphabetically. 
1) 

     
"axrA" 
Returns: "Aa,ax" 
We must sort these into "Aarx". After swapping 'A' and 'a', "axrA" has 
become "Axra" and we can complete the sort by then swapping the 'x' 
with the 'a'. 
2) 

     
"problematic" 
Returns: "ac,ap,be,bi,br,co,il,pt" 

3) 

     
"abcdefABCDEF" 
Returns: "Aa,Bb,Cc,Dd,Ee,Ff" 

This problem statement is the exclusive and proprietary property of 
TopCoder, Inc. Any unauthorized use or reproduction of this 
information without the prior written consent of TopCoder, Inc. is 
strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. 
*/
