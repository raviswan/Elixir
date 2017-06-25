#include <iostream>
#include <memory>

template<typename T>
struct BSTNode{
	T data;
	std::unique_ptr<BSTNode<T>> left,right;
};


class BST{
private:
	std::unique_ptr<BSTNode<int>> root;
public:
	bool insertBST(int key){
		if (root==nullptr){
			std::unique_ptr<BSTNode<int>> newNode(new BSTNode<int>{key, nullptr,nullptr});
			return true;
		}
		else{
			BSTNode<int>* parent = nullptr;
			BSTNode<int>* curr = root.get();
			while(curr){
				if(key > curr->data){
					parent = curr;
					curr = curr->right.get();
				}
				else if (curr->data == key)
					return false;
				else{
					parent = curr;
					curr = curr->left.get();
				}
			}
			std::unique_ptr<BSTNode<int>> newNode(new BSTNode<int>{key, nullptr,nullptr});
			key > parent->data ? (parent->right = std::move(newNode)) : (parent->left = std::move(newNode));
		}
		return true;
	}

	bool deleteBST(int key){
		if (root==nullptr)
			return false;
		BSTNode<int>* curr = root.get();
		BSTNode<int>* parent = nullptr;
		while(curr != nullptr && curr->data != key){
			parent = curr;
			curr = key < curr->data ? curr->left.get() : curr->right.get() ;
		}
		if(!curr)
			return false;

		if(curr->right){
			BSTNode<int>* rParent = curr;
			BSTNode<int>* child = rParent->right.get();
			while(child->left){
				rParent = child;
				child = child->left.get();
			}	
			curr->data = child->data;
			if(rParent->left.get()_== child) {
				rParent->left.reset(child->right.release());
			}
			else{
				rParent->right.reset(child->right.release());
			}
		}
		//root is key
		else{
			if (curr == root.get()){
				root.reset(curr->left.release());
			}
			else {
				if(curr->data < parent->data)
					parent->left.reset(curr->left.release());
				else
					parent->right.reset(curr->left.release());
			}
			
		}
		return true;
	}
	

};

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}