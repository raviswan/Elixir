#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string& s,int start, int end){
	cout<<"start="<<start<<"end="<<end<<endl;
	if(start>=end)
		return false;
	while(start<=end){
		if(s[start]!=s[end])
			return false;
		start++;
		--end;
	}
	return true;
		
}
int main(int argc, char** argv){
	cout<<"Enter input string\n"<<endl;
	cin>>argv[0];
	string s(argv[0]);
	cout<<s<<endl;
	isPalindrome(s,0,s.size()-1)==true ? cout<<"true\n":cout<<"false\n";
}

