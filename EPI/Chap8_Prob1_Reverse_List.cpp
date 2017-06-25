#include <iostream>
#include <memory>


void initializeList(const std::array<int,5> &arr){
	std::array<int*,arr.size()> pointers;
	while(count>0){
		auto ptr = make_shared<Node<int>>(new Node<int>())
	}
	
}
template<typename T>
struct Node{
	T data;
	std::shared_ptr<T> next;
}


reverseList(std::shared_ptr<Node<int>> list){
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
	
	std::array<int,5> a = {1,3,5,7,8};
	initializeList(a);
}