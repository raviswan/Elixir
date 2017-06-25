#include <iostream>
#include <vector>

using namespace std;
int deleteKeyFromArray(int key, vector<int>& v){
	int id=0;
	for(int i=0;i<v.size();i++){
		if( v[i] != key){
			v[id++] = v[i];
		}
	}
	return id;
}


int main(){
	std::vector<int> v = {1,2,3,4,5,6,3,4,5};
	for(int i=0;i<v.size();i++){
		printf("%d\n",v[i] );
	}
	int newCount =deleteKeyFromArray(3,v);
	printf("deleted array\n" );
	for(int i=0;i<newCount;i++){
		printf("%d\n",v[i] );
	}
}