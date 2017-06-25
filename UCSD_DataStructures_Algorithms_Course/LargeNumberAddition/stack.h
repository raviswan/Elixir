#ifndef STACK_H_
#define STACK_H_

#include "list.h"

class Stack: public List {
public:
	Stack();
	int push(const void *elem);
	int pop(void **elem);
	/*Read one char at a time from the string and store as char 
	by doing a calling push()*/
	void pushNumberOnStack(const char* pNum1);
	/*Print the operands stored on the stack*/
	void printNumberOnStack();
	/*Print the result stored on the stack*/
	void printResultOnStack();
	~Stack();
};

#endif