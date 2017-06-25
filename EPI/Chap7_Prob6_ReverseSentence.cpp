#include <iostream>
#include <string>
#include <vector>

using namespace std;

void reverseSentence(string& s){
	size_t end,start;
	reverse(s.begin(),s.end());
	start=0;
	while( (end = s.find(' ',start)) != string::npos){
		reverse(s.begin()+start,s.begin()+end);
		start = end+1;
	}
	reverse(s.begin()+start,s.end());

}

int main(){
	string s("what a ;; s&^&* this fucking mess");
	cout<<s<<endl;
	//v.push_back(string("A man, a plan, a canal,Panama"));
	//v.push_back(string("Able was I, ere  i saw elba!"));
	reverseSentence(s);
	cout<<s<<endl;

}




