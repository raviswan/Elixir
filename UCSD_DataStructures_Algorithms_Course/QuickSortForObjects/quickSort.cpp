#include <iostream>
#include <cstdlib>

void quickSort(int a[],int left, int right){
	int i = left;
	int j = right;
	int pivot = a[(left+right)/2];
	int temp;
	while(i<=j){
		while(a[i]<pivot)
			i++;
		while (a[j]>pivot)
			j--;
		if( i <= j){
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	}
	if(left < j)
			quickSort(a,left,j);
	if(i< right)
			quickSort(a,i,right);

}

