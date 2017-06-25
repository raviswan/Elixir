#include "stack.h"

/*This is a global function that takes two Stack objects s1 and s2
adds them up and stores the sum on stack object named result 
Since there's pop() operation inside this, we have to free
memory after extracting the values*/

void addTwoNumbersOnStack(Stack *s1, Stack *s2, Stack *result){
	char *op1,*op2;
	char *sum;
	int tot;
	int carry=0;
	int o1,o2;
	/*Pop each element of stack , conver char to int, do
	addition, and then store the result back as char on 
	the result stack object*/

	while(s1->getListLength() > 0 && s2->getListLength() > 0){
		sum = new char;
		s1->pop((void**)&op1);
		s2->pop((void**)&op2);
		tot = ((*op1)- '0') + ((*op2)-'0') + carry;
		if (tot>=10){
			carry = 1;
			tot %= 10; 
		}
		else
			carry=0;
		*sum = tot+'0';
		result->push(sum);
		printf("freeing %c and %c\n",*op1,*op2);
		delete op1;
		delete op2;
	}
	/*When s2 is empty, pop out remaining elements of s1 and add it result
	stack after taking carry into account*/

	while(s1->getListLength()> 0){
		sum = new char;
		s1->pop((void**)&op1);
		tot = ((*op1)- '0') + carry;
		if (tot>=10){
			carry = 1;
			tot %= 10;  
		}
		else
			carry=0;
		*sum = tot+'0';
		result->push(sum);
		printf("freeing %c\n",*op1);
		delete op1;
	}
	/*When s1 is empty, pop out remaining elements of s2 and add it result
	stack after taking carry into account*/
	while(s2->getListLength() > 0){
		sum = new char;
		s2->pop((void**)&op1);
		tot = ((*op1)- '0') + carry;
		if (tot>=10){
			carry = 1;
			tot %= 10;  
		}
		else
			carry=0;
		*sum = tot+'0';
		result->push(sum);
		printf("freeing %c\n",*op1);
		delete op1;
	}
	/*If MSB of the addition has a carry , store is separately in 
	result object*/
	if(carry==1){
		char* msb =  new char;
		*msb = '1';
		result->push(msb);
	}


}

void addLargeNumbers(const char *pNum1, const char *pNum2){
	/*Create a stack object for operand 1*/
	Stack *s1 =  new Stack();
	/*Create a stack object for operand 2*/
	Stack *s2 =  new Stack();
	/*Create a stack object to store the result of the addition*/
	Stack *result = new Stack();
	/*Push the numbers on their  stack*/
	s1->pushNumberOnStack(pNum1);
	s2->pushNumberOnStack(pNum2);
	addTwoNumbersOnStack(s1,s2,result);
	result->printResultOnStack();
	delete s1;
	delete s2;
	delete result;
}

int main(){
	addLargeNumbers("592", "3784"); 
	//addLargeNumbers("423929496729", "92496729567987"); 
	//addLargeNumbers("10101010101010101110", "99999999999999911199991"); 
	//addLargeNumbers("11111111111111111111111111", "222"); 
	return 0;

}