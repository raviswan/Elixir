#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	unsigned int a[]={7,14,1024,8,1975,951,1024,1023,183,1775,848,3071};
	for(int i=0;i<sizeof(a)/sizeof(a[0]);i++){
		unsigned int num = a[i];
		unsigned int old=0;
		unsigned int new=0;
		unsigned int max = 0;
		unsigned int count = 0;
		unsigned int index=0;
		//Navigate upto first zero that is not followed by another zero, get the index.  
		//From that poitnon,we have to keep track of
		//next  zero occurence and all 1s in between. At the start of second zero,
		//we count all ones upto until that including the first zero, and store it
		//in old. The no of 1s between two spaced zeros is stored in new for subsequent iteration
		
		//first bit is 1
		if ((num&(1<<index))!=0 ){
			while(index<32 && ((num&(1<<index))!=0 ))
				index++;

			old = index;
			index++;
			max = index;
		}
		//first bit is 0
		else{
			index++;
		}
		//for all subsequent bits
		while(index<32){
			/*If zero is followed by zeros, keep moving forward until you hit a 1*/
			if((num&(1<<index))==0){
				//printf("Reached successive zeros\n");
				old = 0;
				index++;
				continue;
			}
			/*Count all ones until you hit a zero again*/
			while((num&(1<<index))!=0){
				index++;
				new++;
			}
			count = old+new+1;
			if(count>max)
				max=count;
			//printf("index for next zero is %d,old=%d new=%d max=%d\n",index,old,new,max);
			old = new;
			new = 0;
			index++;//Checking bit following zero 

		}
		printf("Output for %d is %d\n",a[i],max);
	}
	return 0;
}
