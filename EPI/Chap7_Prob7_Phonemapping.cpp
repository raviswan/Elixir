#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

array<string,10> P = {"0","1","abc","def","ghi","klm","nop","qrs","tuv","wxyz"};

void getPhoneLetters(size_t i, string& s,vector<string>* v, string& res){
	if(i==s.size()){
		v->push_back(res);
		return;
	}
	string phoneSet = P[s[i] - '0'];
	size_t index = i;
	
	for(char& c: phoneSet){
		i = index;
		res[i] = c;
		getPhoneLetters(++i,s,v,res);
	}
}

vector<string>  getPhoneNumbers(string s){
	vector<string> v;
	string res(s.size(),0);
	size_t i=0;
	getPhoneLetters(i,s,&v,res);
	return v;
	
}


int main(){
	for(string& s: getPhoneNumbers("23"))
		cout<<s<<endl;	
}