#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int stringToInteger(string& s){
	int sum=0;
	int sign = (s[0] == '-') ? -1 : 1;
	int sLen = s.size()-1;
	int low = (sign == 1) ? 0 : 1;
	for (int i=sLen;i>=low;i--){
			sum += (s[i]-'0')* pow(10,sLen-i);
	}
	return sign*sum;
}


int convertToInteger(string s){
	int res = 0;
	int digit;
	for(int i=0;i<s.size();i++){
		digit = s[i] - 'A' + 1;
		res = res*26 + digit;
	}
	return res;

}
int main(){
	string c("-1220");
	cout<<stringToInteger(c)<<endl;
	cout<<convertToInteger("Y")<<endl;
}



