#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	unsigned int num1 = 7;
	unsigned int num2 = 8;
	unsigned int XORed = num1 ^ num2;
	unsigned int count = 0;
	while(XORed!=0){
		if(XORed & 1)
			count++;
		XORed = XORed>>1;
	}
	printf("Answer for %d and %d is %d\n",num1,num2,count);
	return 0;
}
