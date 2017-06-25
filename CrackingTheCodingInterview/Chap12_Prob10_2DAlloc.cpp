#include <stdio.h>
#include <stdlib.h>

void** TwoDimMalloc(int rows,int col){
	size_t offset = (sizeof(int*)*rows);
	size_t data = (rows*col*sizeof(int));
	void** rowptr = (void**) malloc(offset+data);
	int* buf = (int*)(rowptr+rows);
	for(int i=0;i<rows;i++){
		rowptr[i] = buf + i*col;
	}
	return rowptr;



}