/*
Apple Interview 
given input:
alt lat dog god tab bat,
print output of anagrams each on one line:
alt lat
dog god
bat tab
 */

#include <iostream>
#include <cstring>
#include "bitvector.h"
using namespace std;

int isAnagram(char* str1, char*str2){
	BitVector bv1(68), bv2(68);
	if(strlen(str1) != strlen(str2))
		return -1;
	unsigned char i=0;
	while(i < strlen(str1)){
		bv1.setBit(*(str1+i) - 'A');
		bv2.setBit(*(str2+i) - 'A');
		++i;
	}
	if(memcmp(bv1.getByteArray(),bv2.getByteArray(),bv1.getBitVectorLength()) == 0)
		cout<<str1<<" and "<<str2<<" are anagrams"<<endl;
	else
		cout<<str1<<" and "<<str2<<" are not anagrams"<<endl;
	return 0;

}

int main(int argc, char** argv){
		isAnagram(argc,argv);
		return 0;

}