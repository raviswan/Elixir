#include "list.h"
#include <cmath>

using namespace std;

ListElem::ListElem(double data){
	this->data = data;
}


ListElem::~ListElem(){
}


double ListElem::getData() const{
	return this->data;
}


ListElem* ListElem::getNextElem() const{
	return this->next;
}


void ListElem::setData(double data) {
	this->data = data;
}


void ListElem::setNextElem(ListElem *node){
		this->next = node;
}


List::List(){
	this->length = 0;
	this->head = NULL;
	this->tail =  NULL;
}


List::~List(){

}


int List::getListLength() const{
	return this->length;
}


ListElem* List::getListHead() const{
	return this->head;
}


ListElem* List::getListTail() const{
		return this->tail;
}


bool List::isHead(ListElem *node) const{
	return (node==this->head) ;
}


bool List::isTail(ListElem *node) const{
	return (node==this->tail) ;
}


int List::insertAfter(ListElem* node,double data){
	ListElem *newElem = new ListElem(data);
	/*Inserting as first element*/
	if (node == NULL){
		/*if no element in the list,head=tail=newElem*/
		if (this->length == 0){
			this->tail = newElem;
		}
		/*newElement's next points to old head*/
		newElem->setNextElem(this->head);
		/*assign new head*/
		this->head = newElem;
	}
	/*for all other cases*/
	else{
		/*if node is the last node of the list*/
		if (node->getNextElem() == NULL){
			this->tail = newElem;
		}
		/* inserted node's next = old node's next*/
		newElem->setNextElem(node->getNextElem());
		/* old node's next = inserted node*/
		node->setNextElem(newElem);
	}
	this->length++;
	return 0;
}


int List::removeAfter(ListElem* node, double *deletedData){
	ListElem* toRemove;
	/*if list is empty*/
	if(node == NULL && this->length ==0){
		return -1;
	}
	/*remove first element*/
	else if(node == NULL){
		toRemove = this->head;
		*deletedData = toRemove->getData();
		/*new head is one past current head*/
		this->head = toRemove->getNextElem();
		/*if only one element, tail becomes NULL*/
		if (this->length == 1){
			this->tail = NULL;
		}
	}
	/*all other scenarios*/
	else{
		toRemove = node->getNextElem();
		/*if node is the last element, nothing to remove*/
		if (toRemove==NULL){
				return -1;
		}
		/*if last element needs to be removed*/
		else if(toRemove->getNextElem()==NULL){
			this->tail = node;
		}
		*deletedData = toRemove->getData();
		node->setNextElem(toRemove->getNextElem());
	}
	delete(toRemove);
	this->length--;
	return 0;
}


void List::destroyList(){
	double *discardData;
	/*Call removeAfter() to destroy every element starting at head.
	But get the data out of every element,print it before destroying it here*/ 
	while (this->length >0){
		discardData = new double;
		if(removeAfter(NULL,discardData)==0){
				cout<<"Value being deleted is: "<<*discardData<<"\n";
				delete discardData;
		}
		else
			delete discardData;
	}
}


void List::printList(){
	int len = this->getListLength();
	ListElem *h = this->getListHead();
	cout<<"Printing List"<<endl;
	while(h!= NULL && len!=0){
		cout<<h->getData()<<endl;
		h=h->getNextElem();
		len--;
	}
	cout<<endl;
}

/*===============HOMEWORK 2========================================*/

void List::appendTerm(double constant){
	if (this->insertAfter(this->tail,constant) == -1){
		cout<<"Program failed"<<endl;
		exit(EXIT_FAILURE);
	}
}


void List::display(){
	int len = this->getListLength();
	int expTerm;
	double coeff;
	ListElem *h = this->getListHead();
	while(h!= NULL && len!=0){
		coeff = h->getData();
		if(coeff != 0.0){
			expTerm = len-1;
			/*print coefficient only when it is not 1 or exponent=0*/
			if(coeff!=1 || expTerm==0){
				/*Print the decimal for 1.0, 6.0 etc. Else use default*/
				if(!(coeff-long(coeff))){
					cout << std::fixed << std::setprecision(1) << coeff;
				}
				else{
					cout << std::defaultfloat<<std::setprecision(15) << coeff;
				}
			}
			/*print x for  all powers of x except 0 */
			if(expTerm){
				/*for x^1, print x*/
				if(expTerm==1)
					cout<<"x";
				else
					cout<<"x^"<<expTerm;
			}
			/*If it's not tail and next element is nonegative,  print "+"" */
			if( !this->isTail(h)){
				if (h->getNextElem()->getData()>0){
					cout<<" + ";
				}
				else{
					cout<<" ";
				}
			}
		}
		h=h->getNextElem();
		len--;
	}
}


double List::evaluate(double x){
	double value = 0.0;
	int len = this->getListLength();
	ListElem *h = this->getListHead();
	while(h!= NULL && len!=0){
		value += h->getData()*pow(x,len-1);
		h=h->getNextElem();
		len--;
	}
	return value;
}

