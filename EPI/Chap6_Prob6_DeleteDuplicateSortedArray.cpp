#include <iostream>
#include <vector>

using namespace std;
int deleteDuplicatesFromArray(vector<int>& v){
	int id=1;
	for(int i=1;i<v.size();i++){
		if( v[i] != v[i-1]){
			v[id++] = v[i];
		}
	}
	return id;
}


int main(){
	std::vector<int> v = {1,2,3,3,5,6,6,7,8,9};
	for(int i=0;i<v.size();i++){
		printf("%d\n",v[i] );
	}
	int newCount =deleteDuplicatesFromArray(v);
	printf("deleted array\n" );
	for(int i=0;i<newCount;i++){
		printf("%d\n",v[i] );
	}
}