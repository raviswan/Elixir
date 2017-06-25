#include <iostream>
#include <memory>
#include <vector>

using namespace std;


void ComputeSubsetHelper(int n, int k, vector<vector<int>>* v, vector<int>* selected_set, int index ){
	if(selected_set->size() == k){
		v->push_back(*selected_set);
		return;
	}
	for(int i=index;i<=n;i++){
		selected_set->push_back(i);
		ComputeSubsetHelper(n,k,v,selected_set,i+1);
		cout<<"Temp set ";
		for (auto j: *selected_set)
				cout<<j<< " ";
		cout<<endl;
		selected_set->pop_back();
		cout<<"after pop: ";
		for (auto j: *selected_set)
				cout<<j<< " ";
		cout<<endl;

	}
}

void ComputeSubset(vector<vector<int>>* v, vector<int>* selected_set, int n, int k){
	ComputeSubsetHelper(n,k,v,selected_set,1);

}

int main(int argc, char** argv){
	vector<vector<int>> v;
	vector<int> s;
	ComputeSubset(&v,&s,5,3);
	for (auto i : v){
		for(auto j: i)
			cout<<j<<" ";
		cout<<endl;
	}
	return 0;
}