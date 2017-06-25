/*Problem 1.1*/

#include "bitvector.h"

int main(){
	char str[]="ramvishyudtbcelzqnfgh";
	char *c = str;
	BitVector bv(256);
	bv.unsetBit();
	while(*c != '\0'){
		printf("%d\n",*c-'\0');
		if(bv.isBitSet(*c  - '\0')){
			printf("string is not unique\n");
			return 0;
		}
		else{
			bv.setBit(*c  - '\0');
		}
		c++;
	}
	bv.printByteArray();
	printf("string is unique\n");
	return 0;
}