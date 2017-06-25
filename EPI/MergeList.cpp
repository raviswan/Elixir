#include <iostream>
#include <memory>
using namespace std;

template<typename T>
struct Node{
	shared_ptr<Node<T>> next;
	T data;
};

void initializeLinkedList(int length) {
	static int val;
	auto n = make_shared<Node<int>>(new Node<int>());
	n->data = val++;
	int i =1;
	while (i<length){
		auto nPtr = make_shared<Node<int>>(new Node<int>);
		nPtr->data = val++;
		n->next = nPtr;
		n = nPtr;
		i++;
	}
}

void mergeSortedList(shared_ptr<Node<int>> head1, shared_ptr<Node<int>> head2){
	auto ptr1 = head1;
	auto ptr2 = head2;
	auto temp = shared_ptr<Node<int>>(new Node<int>);
	temp = ptr1;
	while(ptr1 != nullptr  && ptr2 != nullptr){
		if (ptr1 == head1 && ptr2 == head2){
			if(ptr1->data <= ptr2->data){
				temp = ptr1;
				ptr1 =   ptr1 -> next;
			}
			else{
				temp  = ptr2;
				ptr2 = ptr2 ->next;
			}
		}
		if(ptr1->data <= ptr2->data){
			temp->next  = ptr1;
			temp = ptr1;
			ptr1 =   ptr1 -> next;
		}
		else{
			temp->next  = ptr2;
			temp  = ptr2;
			ptr2 = ptr2 ->next;
		}		
	}
	if(ptr2 != nullptr){
		temp->next = ptr1;
	}
	else if (ptr1 != nullptr) {
		temp->next = ptr2;
	}
}

int main(int argc, char const *argv[])
{
	Node<int> n1[5];
	Node<int> n2[6];
	int a=1;
	initializeLinkedList(5);

	return 0;
}