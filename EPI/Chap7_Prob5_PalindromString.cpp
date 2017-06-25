#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool checkPalindromeString(string s){
	int j=s.size()-1;
	int i=0;
	while(i<=j){
		if (isalnum(s[i])){
			if (isalnum(s[j])){
				if (tolower(s[i])==tolower(s[j])){
					i++;
					j--;
				}
				else
					return false;
			}
			else{
				j--;
			}
		}
		else{
			i++;
		}
	}
	return true;
}


int main(){
	vector<string> v;
	v.push_back(string("Ray a ray"));
	v.push_back("A man, a plan, a canal,Panama");
	v.push_back("Able was I, ere  i saw elba!");
	for(auto i:v)
		cout<<i<< " : "<<checkPalindromeString(i)<<endl;
}