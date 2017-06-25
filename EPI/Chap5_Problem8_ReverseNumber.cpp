#include <iostream>
#include <string>
using namespace std;
int main(){
	string line;
	int number;
	getline(cin,line);
	number = stoi(line);
	cout<<number<<endl;
	bool sign = number>0;
	int res = 0;
	number = abs(number);
	while(number!=0){
		res = 10*res + number%10;
		number /= 10;
	}
	if (sign)
		cout<<res<<endl;
	else
		cout<<-res<<endl;
	return 0;

}