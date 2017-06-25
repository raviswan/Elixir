#include "stack.h"
#include <cstdlib>
using namespace std;

Stack::Stack(){
}

Stack::~Stack(){
	this->destroyList();
}

int Stack::push(const void* elem){
		return(this->insertAfter(NULL,elem));
}

int Stack::pop(void** elem){
	return (this->removeAfter(NULL,elem));
}

void Stack::pushNumberOnStack(const char* pNum1){
	char *charPtr = (char*)pNum1;
	char *c;
	while(*charPtr != '\0'){
		c= new char;
		*c= *charPtr;
		this->push(c);
		charPtr++;
	}

}
/*If you call this, then you have to free the memory created by push() */
void Stack::printNumberOnStack(){
	char str[STRING_LEN];
	char *c;
	int i;
	i=this->getListLength();
	str[i--]='\0';
	while(this->getListLength()>0){
		 this->pop((void**)&c);
		 str[i] = *c;
		 --i;
		 printf("freeing %c\n",*c);
		 delete c;
	}
	printf("The number is %s\n",str);
}

/*If you call this, then you have to free the memory created by push()*/
void Stack::printResultOnStack(){
	char str[STRING_LEN];
	char *c;
	int i=0;
	while(this->getListLength()>0){
		 this->pop((void**)&c);
		 str[i] = *c;
		 i++;
		 printf("freeing %c\n",*c);
		 delete c;
	}
	str[i]='\0';
	printf("The number is %s\n",str);

}
