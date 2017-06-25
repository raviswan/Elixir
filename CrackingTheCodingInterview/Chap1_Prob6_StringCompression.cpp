	/*

 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "bitvector.h"

using namespace std;

string stringCompression(string str){
	int len = str.length();
	/*Use ostringstream to concatenate integer to C++ string*/
	std::ostringstream oss;
	oss << str[0];

	int count=1;

	for (size_t i=1;i<len;i++){
		cout<<str[i]<<endl;
		if(str[i]==str[i-1]){
			count =  count + 1;
			/*If last character is a repeat, add count before exiting loop */
			if(i==len-1)
				oss<<count;
			continue;
		}
		oss<<count<<str[i];
		count =1;

	}
	return (oss.str().length() < str.length())? oss.str():str;

}



int main(int argc, char** argv){
	string str(argv[1]);
	string s = stringCompression(str);
	cout<<"Value is "<<s<<endl;
	return 0;

}