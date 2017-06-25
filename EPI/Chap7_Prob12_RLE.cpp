#include <iostream>
#include <string>
using namespace std;

string runLengthEncoding(const string& s){
	int i=0;
	int count=1;
	string result;
	size_t pos;
	size_t rCount=0;
	while(i < s.size()){
		count = 1;
		if(s[i] != s[i+1]){
			cout<<s[i]<<" "<<s[i+1]<<endl;
			result += std::to_string(count);
			result += s[i];
			++i;
		}
		else{
			while(s[i] ==s[i+1]){
				++count;
				++i;
			}
			result += std::to_string(count);
			result += s[i];
			++i;
		}
	}
	return result;
	
}


int main(){
	string s("aabbccdddddefg");
	cout<<s<<"after encoding : "<<runLengthEncoding(s)<<endl;
}