#include <iostream>
#include <memory>

template<typename T>
struct Node{
	T data;
	std::shared_ptr<Node<T>> next;
};


bool checkListForPalindrome(std::shared_ptr<Node<int>> head){
	
	auto slow = head;
	auto fast = head;
	while(fast!= nullptr && fast->next != nullptr){
		slow=slow->next;
		fast = slow->next;
	}
	
	auto first_half= slow;
	auto second_half = reverseList(slow->next);
	while(second_half  && first_half){
		if(second_half->data != first_half->data)
			return false;
		}
		first_half=first_half->next;
		second_half=second_half->next;
	}
	return true;
}