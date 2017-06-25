#include <iostream>
#include <string>
using namespace std;

/*Problem 7.3. Spreadsheet conversion*/
int spreadsheetConv(const string& s){
	int res=0;
	for(const char&c : s){
		res = res*26 + c-'A'+1;
	}
	return res;
}


bool palindromeSentence(const string& s){
	int i =0;
	int j = s.size()-1;
	while(i<j){
		while (!isalnum(s[i]) && i<j)
			i++;
		while(!isalnum(s[j]) && i<j)
			j--;
		if(tolower(s[i])!= tolower(s[j]))
			return false;
		i++;
		j--;
	}
	return true;
}
int main(){
	string s("D");
	int res = spreadsheetConv(s);
	cout<<s<<" = "<<res<<endl;

}

