/*
PROBLEM:
To find a subset  in a given array of numbers that has the maximum value. Return the indices

SOLUTION:
Starting from first element, add each element to its immediate successor. 
- If the value of newSum > highestSum, store the highestSum and corresponding index
- If not, set newSum to currently pointed value, and move the start index to current loop index
- If value at current Index > highestSum, store this value and change start index to current .
 Repeat above the length of the loop
*/

#include <iostream>
#include <vector>
#include <array>

using namespace std;

pair <int,int> getMaxSubArray(const vector<int>& A){
	pair<int, int> p = make_pair(0, 0);
	int highestSum = A[0];
	int newSum = 0;
	int index = 0;
	int *indexPtr = &index;
	for(int i = 0 ; i< A.size(); ++i){
		newSum  +=  A[i];
		//cout<<" newSum = "<<newSum;
		if (newSum > highestSum){
				highestSum = newSum;
				p = make_pair(index, i);
		}
		else{
			newSum = A[i];
			*indexPtr = i;
			//for last element returning the highest sum
			if(i == A.size()-1 && newSum > highestSum){
				highestSum = newSum;
				p = make_pair(index,i);
			}
		}
		if (A[i] > highestSum) {
			highestSum = A[i];
			newSum = highestSum;
			*indexPtr = i;	
			p = make_pair(index, i);
		}
			
	}
	cout<<"highestSum = "<<highestSum<<endl;
	return p;
}


int main(){
	vector<int> a {-10,2,2,4,-44,-55,-56};
	vector<int> b {-1,2,3,-1,-9,-9};
	vector<int> c {-1,2,2,5,-96,24};
	vector<int> d {-23,-1,21,2,5,-96,-24};
	vector<int> e {120,-2,-2,-5,96,25};
	vector<int> f {120,-2,-2,-5,-96,-25};
	vector<int> g {-1,2,2,5,-96,24,48};
	vector<int> h {-96,2,2,5,-96};
	vector<int> i {-1,-12,-3,-4};
	vector<int> j {-11,-3,-4,-1};
	vector<int> k {1,2,3,4,-5};
	vector< vector<int> > v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	v.push_back(f);
	v.push_back(g);
	v.push_back(h);
	v.push_back(i);
	v.push_back(j);
	v.push_back(k);
	for(auto& e : v){
		pair<int, int> p = getMaxSubArray(e);
		cout<<"Input vector :"<<endl;
		for(auto elem: e)
			cout<<elem<<" ";
		cout<<"\nOutput ="<<p.first<<" "<<p.second<<endl;
		cout<<"\n\n";
	}
	cout<<"\n\n";
	return 0;
	
}

// endianCheck(){
// 	unsigned int i = 1;
// 	char *c = (char*)&i;
// 	if(*c)
// 		printf("little endian\n");
// 	else
// 		printf("big endian\n")
// }