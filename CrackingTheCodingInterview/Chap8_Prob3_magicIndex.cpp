#include <iostream>
using namespace std;

int checkMagicIndex(int a[], int start, int end){
	if(start>end)
		return -1;
	int mid = (start+end)/2;
	if(a[mid]== mid){
		cout<<"Found magic index"<<endl;
		return mid;
	}
		
	if(a[mid]<mid)
		return checkMagicIndex(a,mid+1,end);
	else
		return checkMagicIndex(a,start,mid-1);

}

int checkMagicIndexDistinct(int a[], int start, int end){
	if(start>end)
		return -1;
	int mid = (start+end)/2;
	if(a[mid]== mid){
		cout<<"Found magic index"<<endl;
		return mid;
	}
		
	int leftIndex = std::min(mid-1,a[mid]);
	int left = checkMagicIndexDistinct(a,start,leftIndex);
	if(left >=0)
		return left;

	int rightIndex = std::max(mid+1,a[mid]);
	int right = checkMagicIndexDistinct(a,rightIndex,end);
	return right;

}
int main(){
	int a[]={-1,0,2,5,7};
	checkMagicIndex(a,0,sizeof(a)/sizeof(*a));


}