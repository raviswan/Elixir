#include <iostream>
#include <vector>

using namespace std;

void doPascalTriangle(vector<vector<int>>& v, int n){
	if(n<=0)
		return;
	vector<int> first;
	vector<int> row;
	int term;
	first.push_back(1);
	v.push_back(first);
	for(int i=1;i<n;i++){
		row.push_back(1);
		for (int j=1;j<=i-1;j++){
			term = v[i-1][j-1]+ v[i-1][j];
			row.push_back(term);
		}
		row.push_back(1);
		v.push_back(row);
		row.clear();
	}
}

int main(void){
	vector<vector<int>> v;
	doPascalTriangle(v,6);
	for(auto i:v){
		for(auto j:i)
			cout<<j<<" ";
		cout<<endl;
	}
	
	return 0;
}
	