#include <iostream>
#include <vector>

/*Page 72*/
/*To do a dictionary ordering of array- you start from 2nd to last element.
Compare with its immediate right neighbor until you find element that is 
smaller than its right neihbor. This number needs to be swapped out
e.g. 615430.
You obtain descending pattern of 5430 when you walk from right to left. So, you
reach digit 1 which fails the above condition. Now  1 needs to be swapped out with 3.
Intermediate result after swap: 635410. Now what you do is reverse the descening pattern of "5410"
to get the next immediate dictionary number. i.e. 630145
*/

using namespace std;

vector<int> findDescending(vector<int> v){
	int k = v.size()-2;
	int i;
	while(k>=0 && v[k]>v[k+1]){
		k--;
	}
	if(k==-1)
		return {};

	for(i=v.size()-1;v[i]<v[k];i--);
	swap(v[k],v[i]);
	reverse(v.begin()+k+1,v.end());
	return v;

}



int main(){
	vector<int> v,res;
	//v.push_back(6);
	//v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	//sort(v.begin(),v.end());
	res = v ;
	while( !res.empty()){
		for(auto& j: res)
			cout<<j<<" ";
		res = findDescending(res);
		cout<<endl;
	}
	

}