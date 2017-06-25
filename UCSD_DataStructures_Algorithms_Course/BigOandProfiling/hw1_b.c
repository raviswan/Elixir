#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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



int* insert(int *origArray, int length, int index, int value){
	if (length==0){													 /* c1 */
		int *newArray = (int*) Malloc(sizeof(int));					 /* c2 */
		*newArray = value;											/* c3 */
		return newArray;											/* c4 */
	}
	else if ((index<0) || (index>length)) {							/* c5 */
		printf("New value cannot be inserted at pos = %d. Index should be within range [0-%d]\n",index,length); /* c6 */
		return NULL;												/* c7 */
	}
	else{
		int *newArray = (int*) Malloc(sizeof(int)*(length+1));		/* c8 */
		for (int i=0;i<index;i++){									/* c9*m */
			newArray[i] = origArray[i];								/* c10 */
		}
		newArray[index] = value;									/* c11 */
		for (int j=index+1;j<=length;j++){							/* c12*(n-m) */	
			newArray[j] = origArray[j-1];							/* c13 */
		}
		if(origArray != NULL){										/* c14 */
			free(origArray);										/* c15 */
		}
		return newArray;											/* c16 */
	}

}


int main(){
	/* Setting to allow fine-tuning the granularity of the readings */
	unsigned int INSERTS_PER_READING = 1500;
	/* Start with an empty array */
	int *array = NULL;
	unsigned int length = 0;
	unsigned int value =  rand();
	unsigned int index = 0;
	unsigned long startTime,stopTime;
	double timePerInsert;
	printf("\nArray length 	Seconds per insert\n\n");
	/* Take 60 readings */
	for (int i=0;i<60;i++){	
		startTime = clock();
		for (int j=0;j<INSERTS_PER_READING;j++){
			array = insert(array,length,index,value);
			length += 1;
			index = rand() %length;
			value = rand();
		}
		stopTime = clock();
		timePerInsert = (double)(stopTime - startTime) / (CLOCKS_PER_SEC*INSERTS_PER_READING);
		printf("%5d  %25.10lf\n",length,timePerInsert);
	}
	if (array != NULL) {
		free(array);
	}

}



