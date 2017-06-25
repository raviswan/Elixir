#include <iostream>
#include <cmath>

bool checkPalindromeInteger(int n){
	std::cout<<"number = "<<n<<std::endl;
	int lsb = n % 10;
	int num = n / 10;	
	if (num==0)
		return true;
	int msbDiv = pow(10,floor(log10(num)));
	int msb = num / msbDiv;
	std::cout<<"msb="<<msb<<" lsb="<<lsb<<std::endl;
	if( msb != lsb)
		return false;
	checkPalindromeInteger(num % msbDiv);
	return true;
}


int main(int argc, char* argv[]){
	int num = 4005004;
	checkPalindromeInteger(num) == true ? std::cout<<"true\n" : std::cout<<"false\n";
}