#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 5

void printArray(int *arr, int len){
	printf("\n---Array elements: --\n");
	for (int i=0;i<len;i++){
		printf("%d\n",arr[i]);
	}
	printf("---------------\n");
}
void* Malloc(int size){
	void *p = malloc(size);
	if (p==NULL){
		printf("malloc failed\n");
		return NULL;
	}
	else 
		return p;
}

int* insert(int *origArray, int length, int index, int value){
	if (length==0){
		int *newArray = (int*) Malloc(sizeof(int));
		*newArray = value;
		return newArray;
	}
	else if ((index<0) || (index>length)) {
		printf("New value cannot be inserted at pos = %d. Index should be within range [0-%d]\n",index,length);
		return NULL;
	}
	else{
		int temp;
		int *newArray = (int*) Malloc(sizeof(int)*(length+1));
		for (int i=0;i<index;i++){
			newArray[i] = origArray[i];
		}
		newArray[index] = value;
		for (int j=index+1;j<=length;j++){
			newArray[j] = origArray[j-1];
		}
		if(origArray != NULL){
			free(origArray);
		}
		return newArray;
	}

}


int main(int argc, char **argv){
	int *origArray = (int*)Malloc(sizeof(int) * ARRAY_LENGTH);
	int *n;
	printf("Input elements of array (one per line)\n");
	for (int i=0;i<ARRAY_LENGTH;i++){
		scanf("\n%d",origArray+i);
	}
	n = insert(origArray,ARRAY_LENGTH,5,74);
	if(n != NULL){
		printArray(n,ARRAY_LENGTH+1);
		free(n);
	}
	
	return EXIT_SUCCESS;
	
}