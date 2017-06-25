#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct TreeNode{
	T data;
	std::unique_ptr<TreeNode<T>> left,right;
};

/*You keep moving left or right until  based on key. If the tree node is higher than key, the you save
the parent, else you don't. Because we are looking for next largest value. 
*/

int nodeLargeThanValue(std::unique_ptr<TreeNode<int>> root, int key){
	if (root == nullptr)
		return false;
	TreeNode<int>* curr = root.get();
	TreeNode<int>* parent = nullptr;
	while(curr){
		if (curr->data > key) {
			parent = curr;
			curr = curr->left.get();
		}
		else{
			curr=curr->right.get();	
		}	
	}
	return  parent->data;

}

