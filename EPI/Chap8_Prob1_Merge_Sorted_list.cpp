#include <iostream>
#include <memory>

template<typename T>
struct Node{
	T data;
	std::shared_ptr<Node<T>> next;
};

void mergeNodes(std::shared_ptr<Node<int>> *node, std::shared_ptr<Node<int>> *tail){
	(*tail)->next = *node;
	*tail = *node;
	*node = (*node)->next;
}

std::shared_ptr<Node<int>> mergeList(std::shared_ptr<Node<int>> list1, std::shared_ptr<Node<int>> list2){
	
	//std::shared_ptr<Node<int>> dummy_head(new Node<int>);
	auto dummy_head(std::make_shared<Node<int>>());
	auto tail = dummy_head;

	while(list1 && list2){
		mergeNodes(list1->data <= list2->data ? &list1:&list2,&tail);
	}
	tail->next = (list1 ? list1 : list2);
	return dummy_head->next;

}


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
