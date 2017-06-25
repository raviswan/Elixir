#include <iostream>
#include <string>

using namespace std;

bool isPalindromeString(string& s){
	int b = 0;
	for(char i:s){
		cout<<i<<"="<<i-'a'<<endl;
		if(isalnum(i))
			b=b^(1<<(i-'a'));
	}
	if( (b&(b-1)) ==0)
		return true;
	else
		return false;
}

int main(){
	string s("tact Coa");
	if(isPalindromeString(s))
		cout<<s<<"="<<"TRUE"<<endl;
	else
		cout<<"FALSE"<<endl;

}
