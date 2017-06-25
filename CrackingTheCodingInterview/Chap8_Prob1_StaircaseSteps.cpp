#include <iostream>
using namespace std;

int countWays(int n,int* c){
	if(n<0)
		return 0;
	else if(n==0)
		return 1;
	else if (c[n])
		return c[n];
	else{
		c[n] = countWays(n-1,c)+countWays(n-2,c)+countWays(n-3,c);
		return c[n];
	}
}

int main(){
	int n;
	cin>>n;
	int* c = new int[n+1];
	//for(int i=0;i<n+1;i++)
	//	c[i] = -1;
	cout<<countWays(n,c)<<endl;

}