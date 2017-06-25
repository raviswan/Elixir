#include <iostream>
#include <memory>


template<typename T>
struct Node{
	T data;
	std::shared_ptr<T> next;
};


std::shared_ptr<Node<int>> reverseList(std::shared_ptr<Node<int>>& list){
	std::shared_ptr<Node<int>> prev = nullptr;
	std::shared_ptr<Node<int>> curr = list;
	while(curr){
		auto one_ahead = curr->next;
		curr->next = prev;
		prev = curr;
		curr = one_ahead;
	}
	return prev;

}

int main(int argc, char** argv){
	
}