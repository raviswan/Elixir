#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <iomanip>

class ListElem
{
public:
	ListElem(double data);
	~ListElem();
	/*test whether the current node is tail or not*/
	bool isTail() const;
	/*return data element of the node*/
	double getData() const;
	/*return pointer to next element in the list*/
	ListElem* getNextElem() const;
	/*set data in the current node*/
	void setData(double data);
	/*Link the current node with the next node in the list by setting pointer*/
	void setNextElem(ListElem *e);

private:
	double data;
	ListElem* next;
};

class List
{
public:	
	List();
	~List();
	/*return number of nodes in the list*/
	int getListLength() const;
	/*return head of the list*/
	ListElem* getListHead() const;
	/*return tail of the list*/
	ListElem* getListTail() const;
	/*test whether current node is head of the list*/
	bool isHead(ListElem*) const;
	/*test whether current node is tail of the list*/
	bool isTail(ListElem*) const;
	/*insert element into list following the given node */
	int insertAfter(ListElem* node,double data);
	/*remove element after the given node from the list */
	int removeAfter(ListElem* node,double *deletedData);
	/*print the data elements in list */
	void printList(void);
	/*destroy the list by calling removeAfter() for each element */
	void destroyList();


	/*-----------Polynomial APIs--------------------*/
	/*append polynomial term to the end of the list*/ 
	void appendTerm(double constant); 
	/*display the polynomial*/
	void display(); 
	/*evaluate the polynomial for x*/
	double evaluate(double x); 
	
private:
	int length;
	ListElem* head;
	ListElem* tail;

};

#endif