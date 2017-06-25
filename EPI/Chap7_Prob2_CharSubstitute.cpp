#include <iostream>
#include <string>
using namespace std;

void replaceString(string& s){
	int idx=0;
	int cnt = 0;
	for(char&c : s){
		if (c != 'b')
			s[idx++] = c;
		if (c == 'a')
			cnt++;
	}	
	s.resize(idx+cnt);
	int i = s.size()-1;
	int charIndex = i-cnt;
	while(i>=0){
		if(s[charIndex] == 'a'){
			s[i--] = 'd';
			s[i--] = 'd';
			charIndex--;
		}
		else{
			s[i--]=s[charIndex--];
		}
	}

}


int main(){
	string s("mia butt with ass");
	replaceString(s);
	cout<<s<<endl;
	return 1;

}	