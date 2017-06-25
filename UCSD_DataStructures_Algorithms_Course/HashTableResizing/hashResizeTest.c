	/*
 * hashResizeTest.c
 */

#include "chtbl.h"
#include <stdio.h>

#define MAX_LOAD_FACTOR 0.5
#define RESIZE_MULTIPLIER 2.0
/*Hashing function is same as key being passed for integers*/
int hashId(const void* key){
	int code = *((int*)key);
	return code;
}

/*Define the matching function for integers*/
int matchIntegers(const void *key1, const void* key2){
	if (*((int*)key1) == *((int*)key2) )
		return 1;
	else
		return 0;
}

int main(){
	int numbers[]={35,67,32,70,18,44,91};
	int i;
	int validNum = 67;
	int invalidNum = 117;
	int *vPtr = &validNum;
	int *invPtr = &invalidNum;

	CHTbl* hTable = (CHTbl*)malloc(sizeof(CHTbl));
	chtbl_init(hTable,5,MAX_LOAD_FACTOR,RESIZE_MULTIPLIER, hashId,matchIntegers,free);

	for (i=0;i<sizeof(numbers)/sizeof(*numbers);i++){
		if(chtbl_insert(&hTable,&numbers[i],1) != 0){
			printf("Hash Table insertion failed\n");
			exit(1);
		}
	}
	
	/*Look up a known value in the hash table*/
	if(chtbl_lookup(hTable,(void**)&vPtr) == 0){
		printf("YES, Hash table found %d\n",*vPtr);
	}
	else{
		printf("NO,Hash table  didn't find  %d\n",*vPtr);
	}
	/*Look up a non-existent value in the hash table*/
	if(chtbl_lookup(hTable,(void**)&invPtr) == 0)
		printf("YES, Hash table returned a value of %d\n",*invPtr);
	else
		printf("NO,Hash table  didn't find  %d\n",*invPtr);

	free(hTable);
	return 0;

}