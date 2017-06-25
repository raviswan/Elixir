#include <iostream>
#include <algorithm>
#include <stack>
#include <array>
/*

To move N discs from A to B (using C):

1)if (N > 1) move N-1 discs from A to C (using B)
2)move one disc from A to B
3) if (N > 1) move N-1 discs from C to B (using A)

*/

const int NUM_PEGS = 3;
const int NUM_DISCS = 4;
using namespace std;

void computeTowersOfHanoi(array<stack<int>,NUM_PEGS>&pegs,int num_discs,int from_peg,int to_peg,int use_peg, int& moves){
	if(num_discs >0 ){
		moves++;
		computeTowersOfHanoi(pegs,num_discs-1,from_peg,use_peg,to_peg,moves);
		pegs[to_peg].push(pegs[from_peg].top());
		pegs[from_peg].pop();
		computeTowersOfHanoi(pegs,num_discs-1,use_peg,to_peg,from_peg,moves);
	}

		

}
int setupTowersOfHanoi(int num_discs){
	array<stack<int>,NUM_PEGS> pegs;
	int moves = 0;
	for(int i=num_discs;i>0;i--)
		pegs[0].push(i);

	computeTowersOfHanoi(pegs,num_discs,0,1,2,moves);
	return moves;

	
}

int main(){
	cout<<"number of moves ="<<setupTowersOfHanoi(NUM_DISCS)<<endl;
}