#include <iostream>
#include <memory>

template<typename T>
struct BSTNode{
	T data;
	std::unique_ptr<BSTNode<T>> left,right;
};


/*recursive solution*/
BSTNode<int>* searchBST(std::unique_ptr<BSTNode<int>>& root,int key){
	if(root==nullptr)
		return nullptr;
	if(root->data == key){
		auto* node = searchBST(root->left,key);
		if(node == nullptr)
			return root.get();
		else 
			return node;		
	}
	return searchBST(root->data < key ? root->right : root->left, key);

}


/*iterative solution*/
BSTNode<int>*  searchBSTIter(std::unique_ptr<BSTNode<int>>& root, int key){
	BSTNode<int>* curr = root.get();
	BSTNode<int>* firstKeyMatch = nullptr;
	while(curr){
		if(curr->data < key)
			curr = curr->right.get();
		else if(curr->data > key)
			curr = curr->left.get();
		else{
			firstKeyMatch = curr;
			curr = curr->left.get();
		}
	}
	return firstKeyMatch;

}

int main(int argc, char **argv){

}